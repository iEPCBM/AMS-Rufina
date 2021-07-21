#include "dialogaddchat.h"
#include "ui_dialogaddchat.h"

DialogAddChat::DialogAddChat(QString token, bool isEncrypted, QString iv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddChat)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->tableChats->resizeColumnsToContents();
    ui->tableChats->setFocusPolicy(Qt::NoFocus);

    ui->lbChatsNotFound->setVisible(false);
    m_isEncryptedToken = isEncrypted;
    m_IV = iv;
    if (m_isEncryptedToken) {
        m_encryptedToken = token;
    } else {
        m_decryptedToken = token;
    }
}

DialogAddChat::~DialogAddChat()
{
    delete ui;
}

void DialogAddChat::onAddChat(uint row, VkChat chat)
{
    if (!chat.hasTitle()||!chat.hasOwner()) {
        QMessageBox::StandardButtons btClicked = QMessageBox::warning(this, "Предупреждение",
                             "Информации о данной беседе недостаточно. Вероятно, это вызвано отсутствием флага администратора у бота или же тем, что бота исключили из беседы. Если бот состоит в беседе, то для того, чтобы добавить эту беседу в систему, необходимо ее подтвердить.", QMessageBox::Ok|QMessageBox::Cancel);
        if (btClicked==QMessageBox::Ok) {
            DialogChatConfirmation dlgConfirmation(chat, m_decryptedToken, this);
            dlgConfirmation.exec();
            if (!dlgConfirmation.isConfirmated()) {
                return;
            }
        } else return;
    }

    DialogChatSettings dlgChatStg(chat, m_savedChats, this);
    int resultDlg = dlgChatStg.exec();
    if (resultDlg == QDialog::Accepted) {
        chat = dlgChatStg.chat();
        uint8_t floor = dlgChatStg.floor();
        if (m_savedChats.contains(floor)) {
            int32_t oldRow = findRowByChatId(m_savedChats[floor].getId());
            if (oldRow >= 0) {
                setChatAddedState(oldRow, false);
            }
        }
        updateChatTitleInRow(row, chat.getTitle());
        m_savedChats[floor]=chat;
        setChatAddedState(row, true);
    }
}


void DialogAddChat::on_btStartStopFind_clicked()
{
    ui->lbChatsNotFound->setVisible(false);
    if (!m_isSearching) {
        startSearching();
    } else {
        stopSearching();
    }
}

void DialogAddChat::findChats()
{
    uint32_t id = 1;
    bool isSuccessful = true;
    VkChatHandler chatHandler(this, m_decryptedToken);
    VkUserHandler usrHandler(this, m_decryptedToken);
    while (m_isSearching) {
        if (!hasSavedChat(id)) {
            chatHandler.getConversationData(id);
            if (chatHandler.hasError()) {
                stopSearching();
                VkError vkErr = chatHandler.getVkError();
                isSuccessful = false;
                if (vkErr.hasError()) {
                    if (vkErr.code()!=927) {
                        ErrorMessages::errorVkApi(this, vkErr.code(), vkErr.description());
                    }
                    else {
                        isSuccessful = true;
                    }
                }
                break;
            }
            VkChat chat = chatHandler.getChat();
            QList<VkUser> admins;
            QList<uint32_t> usersAdmIds = filterUserIds(chat.getAdministratorsIds());
            if (!usersAdmIds.isEmpty()) {
                usrHandler.sendRequest(usersAdmIds);
                if (usrHandler.hasError()) {
                    VkError vkErr = usrHandler.getVkError();
                    if (vkErr.hasError()) {
                        ErrorMessages::errorVkApi(this, vkErr.code(), vkErr.description() + "\n\nЭта ошибка некритична. После закрытия окна поиск продолжится.");
                    }
                }
                admins = usrHandler.getUsers();
            }
            usrHandler.clear();
            VkUser owner;
            if (chat.hasOwner()) {
                usrHandler.sendRequest(chat.getOwnerId());
                owner = usrHandler.getUsers().at(0);
                usrHandler.clear();
            }
            m_listDetectedChats.append(chat);
            addChatToTable(chatHandler.getChat(), owner, admins, m_listDetectedChats.length()-1);
            chatHandler.clear();
        }
        id++;
    }
    if (m_listDetectedChats.isEmpty()&&isSuccessful) {
        ui->lbChatsNotFound->setVisible(true);
    }
}

void DialogAddChat::addChatToTable(VkChat chat, VkUser owner, QList<VkUser> admins, uint32_t actionId)
{
    ui->tableChats->insertRow (ui->tableChats->rowCount());
    int lastRow = ui->tableChats->rowCount()-1;

    QTableWidgetItem *cellItem = new QTableWidgetItem(QString::number(chat.getId()));
    cellItem->setFlags(cellItem->flags()^Qt::ItemIsEditable);
    ui->tableChats->setItem (lastRow, 0, cellItem);

    if (chat.hasTitle()) {
        cellItem = new QTableWidgetItem(chat.getTitle());
    } else {
        cellItem = new QTableWidgetItem(STR_UNKNOWN);
    }
    cellItem->setFlags(cellItem->flags()^Qt::ItemIsEditable);
    ui->tableChats->setItem (lastRow, 1, cellItem);

    QString strAdmList = "";
    if (chat.hasOwner()) {
        strAdmList = "<p><a href=\"https://vk.com/id"+QString::number(owner.getId())+"\">" +owner.getAssembledName().trimmed() + "</a> " +
                        QString(STR_OWNER_MARKER)+"\n"
                        "</p>\n";
    }
    else {
        strAdmList = STR_UNKNOWN;
    }
    if (!admins.isEmpty()) {
        foreach (VkUser user, admins) {
            strAdmList += "<p><a href=\"https://vk.com/id"+QString::number(user.getId())+"\">" + user.getAssembledName() + "</a></p>\n";
        }
    }
    QLabel *lbAdmins = new QLabel(strAdmList.trimmed(), ui->tableChats);
    lbAdmins->setTextFormat(Qt::RichText);
    lbAdmins->setOpenExternalLinks(true);
    lbAdmins->setMargin(5);
    ui->tableChats->setCellWidget(
             lastRow,
             2,
             lbAdmins);


    ChatActionButton *btAddChat = new ChatActionButton("Добавить", m_listDetectedChats[actionId], ui->tableChats);
    btAddChat->setRow(lastRow);
    QIcon iconAdd;
    iconAdd.addFile(QString::fromUtf8(FILEPATH_ICON_ADD), QSize(), QIcon::Normal, QIcon::Off);
    btAddChat->setIcon(iconAdd);

    QWidget *widgetWrapper = new QWidget();
    QVBoxLayout *layoutBt = new QVBoxLayout(widgetWrapper);
    QSpacerItem *vertSpacerHeader = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *vertSpacerFooter= new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layoutBt->addItem(vertSpacerHeader);
    layoutBt->addWidget(btAddChat);
    layoutBt->addItem(vertSpacerFooter);
    ui->tableChats->setCellWidget(
             lastRow,
             3,
             widgetWrapper);

    ui->tableChats->resizeRowToContents(lastRow);
    ui->tableChats->resizeColumnsToContents();

    connect(btAddChat, SIGNAL(cabtClicked(uint, VkChat)), this, SLOT(onAddChat(uint, VkChat)));

    cellItem = new QTableWidgetItem("");
    cellItem->setFlags(cellItem->flags()^Qt::ItemIsEditable);
    ui->tableChats->setItem(
             lastRow,
             4,
             cellItem);

    lbAdmins         = NULL;
    btAddChat        = NULL;
    widgetWrapper    = NULL;
    layoutBt         = NULL;
    vertSpacerHeader = NULL;
    vertSpacerFooter = NULL;
    cellItem         = NULL;
}

int32_t DialogAddChat::findRowByChatId(uint chatId)
{
    for (auto i=0; i<ui->tableChats->rowCount(); i++) {
        if (chatId==ui->tableChats->item(i, 0)->text().toUInt()) {
            return i;
        }
    }
    return -1;
}

void DialogAddChat::updateChatTitleInRow(int row, QString title)
{
    ui->tableChats->item(row, 1)->setText(title);
}

void DialogAddChat::startSearching()
{
    m_isSearching = true;
    ui->btStartStopFind->setText("Завершить поиск");
    ui->progressBar->setMaximum(0);
    ui->tableChats->setRowCount(0);
    if (decryptToken()) {
        findChats();
    } else {
        stopSearching();
    }
}

void DialogAddChat::stopSearching()
{
    m_isSearching = false;
    ui->btStartStopFind->setText("Начать поиск");
    ui->progressBar->setMaximum(1);
}

bool DialogAddChat::hasSavedChat(VkChat chat)
{
    return hasSavedChat(chat.getId());
}

bool DialogAddChat::hasSavedChat(uint chatId)
{
    QList<VkChat> chats = m_savedChats.values();
    foreach (VkChat s_chat, chats) {
        if (s_chat.getId()==chatId) {
            return true;
        }
    }
    return false;
}

QList<uint32_t> DialogAddChat::filterUserIds(QList<int> usrIds)
{
    QList<uint32_t> retList;
    foreach (int id, usrIds) {
        if (isUserId(id)) {
            retList.append(id);
        }
    }
    return retList;
}

inline bool DialogAddChat::isUserId(int id)
{
    if (id>0) {
        return true;
    }
    return false;
}

void DialogAddChat::setChatAddedState(uint row, bool state)
{
    ui->tableChats->cellWidget(row, 3)->setEnabled(!state);
    ui->tableChats->item(row, 4)->setText(state?"Добавлено":"");
    ui->tableChats->resizeColumnsToContents();
}

bool DialogAddChat::decryptToken()
{
    if (m_isEncryptedToken&&m_decryptedToken.isEmpty()) {
        DialogPasswordEnter dlgPasswEnter(QByteArray::fromBase64(m_encryptedToken.toUtf8()), QByteArray::fromHex(m_IV.toUtf8()), this);
        dlgPasswEnter.exec();
        if (dlgPasswEnter.isSuccessful()) {
            m_decryptedToken = QString::fromUtf8(dlgPasswEnter.getDecryptedData());
        } else {
            return false;
        }
    }
    return true;
}

QHash<uint8_t, VkChat> DialogAddChat::getAddedChats() const
{
    return m_savedChats;
}

void DialogAddChat::setAddedChats(const QHash<uint8_t, VkChat> &addedChats)
{
    m_savedChats = addedChats;
}
