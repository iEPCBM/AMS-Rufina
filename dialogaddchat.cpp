#include "dialogaddchat.h"
#include "ui_dialogaddchat.h"

DialogAddChat::DialogAddChat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddChat)
{
    ui->setupUi(this);
    qDebug()<<"Well";
}

DialogAddChat::~DialogAddChat()
{
    delete ui;
}

void DialogAddChat::onChatGot(VkChat chat)
{
    qDebug()<<"got";
    //m_listChats.append(chat);
}

void DialogAddChat::onAddChat(VkChat *chat)
{
    if (chat->getTitle().isEmpty()||chat->getOwnerId()==0) {
        QMessageBox::StandardButtons btClicked = QMessageBox::warning(this, "Предупреждение",
                             "Информация о данной беседе неполная. Вероятно, это вызвано отсутствием флага администратора у бота. Чтобы добавить эту беседу, необходимо ее подтвердить.", QMessageBox::Ok|QMessageBox::Cancel);
        if (btClicked==QMessageBox::Ok) {

        }
    }
}


void DialogAddChat::on_btStartStopFind_clicked()
{
    if (!m_isSearching) {
        startSearching();
    } else {
        stopSearching();
    }

}

void DialogAddChat::findChats()
{
    uint32_t id=1;
    while (m_isSearching) {
        VkChatHandler chatHandler(this, "");
        VkUserHandler usrHandler(this, "");
        connect(&chatHandler,SIGNAL(dataWasGot(VkChat)),this, SLOT(onChatGot(VkChat)));
        chatHandler.getConversationData(id);
        VkChat chat = chatHandler.getChat();
        QList<VkUser> admins;
        if (!chat.getAdministratorsIds().isEmpty()) {
            usrHandler.sendRequest(
                    filterUserIds(chat.getAdministratorsIds()));
            admins = usrHandler.getUsers();
        }
        usrHandler.clear();
        VkUser owner;
        if (chat.hasOwner()) {
            usrHandler.sendRequest(chat.getOwnerId());
            owner = usrHandler.getUsers().at(0);
        }

        if (chatHandler.hasError()) {
            stopSearching();
            break;
        }
        id++;
        m_listChats.append(chat);
        addChatToTable(chatHandler.getChat(), owner, admins, m_listChats.length()-1);
        chatHandler.clear();
    }
}

void DialogAddChat::addChatToTable(VkChat chat, VkUser owner, QList<VkUser> admins, uint32_t actionId)
{
    ui->tableChats->insertRow ( ui->tableChats->rowCount() );
    int lastRow = ui->tableChats->rowCount()-1;
    ui->tableChats->setItem
            (lastRow,
             0,
             new QTableWidgetItem(QString::number(chat.getId())));
    if (chat.hasTitle()) {
        ui->tableChats->setItem
                (lastRow,
                 1,
                 new QTableWidgetItem(chat.getTitle()));
    } else {
        ui->tableChats->setItem
                (lastRow,
                 1,
                 new QTableWidgetItem(STR_UNKNOWN));
    }
    QString strAdmList = "";
    if (chat.hasOwner()) {
        strAdmList = "<p><a href=\"https://vk.com/id"+QString::number(owner.getId())+"\">" +owner.getAssembledName().trimmed() + "</a>";
        strAdmList += QString(" ")+STR_OWNER_MARKER+"\n";
        strAdmList += "</p>\n";
    }
    else {
        strAdmList = STR_UNKNOWN;
    }
    if (chat.hasAdmins()) {
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


    ChatActionButton *btAddChat = new ChatActionButton("Добавить", &m_listChats[actionId], ui->tableChats);
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

    connect(btAddChat, SIGNAL(cabtClicked(VkChat*)), this, SLOT(onAddChat(VkChat*)));

    lbAdmins         = NULL;
    btAddChat        = NULL;
    widgetWrapper    = NULL;
    layoutBt         = NULL;
    vertSpacerHeader = NULL;
    vertSpacerFooter = NULL;
}

void DialogAddChat::startSearching()
{
    m_isSearching = true;
    ui->btStartStopFind->setText("Завершить поиск");
    ui->progressBar->setMaximum(0);
    ui->tableChats->setRowCount(0);
    findChats();
}

void DialogAddChat::stopSearching()
{
    m_isSearching = false;
    ui->btStartStopFind->setText("Начать поиск");
    ui->progressBar->setMaximum(1);
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
