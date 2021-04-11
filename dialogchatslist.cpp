#include "dialogchatslist.h"
#include "ui_dialogchatslist.h"

DialogChatsList::DialogChatsList(QHash<uint8_t, VkChat> chats, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChatsList)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setChats(chats);
}

DialogChatsList::~DialogChatsList()
{
    delete ui;
}

QHash<uint8_t, VkChat> DialogChatsList::getChats()
{
    return m_chats;
}

void DialogChatsList::setChats(QHash<uint8_t, VkChat> chats)
{
    m_chats = chats;
    updateChatsTable();
}

void DialogChatsList::on_btnAddChat_clicked()
{
    DialogAddChat dlgAddChat(this);
    dlgAddChat.setAddedChats(getChats());
    int resultDlg = dlgAddChat.exec();
    if (resultDlg == QDialog::Accepted) {
        ui->tableChats->setRowCount(0);
        setChats(dlgAddChat.getAddedChats());
    }
}

void DialogChatsList::onEditChat(uint8_t floor, VkChat chat)
{
    DialogChatSettings dlgChatSettings(floor, chat, this);
    int resultDlg = dlgChatSettings.exec();
    if (resultDlg == QDialog::Accepted) {
        uint8_t n_floor = dlgChatSettings.floor();
        VkChat n_chat = dlgChatSettings.chat();
        if (floor==n_floor) {
            m_chats[floor] = n_chat;
        }
        else if (m_chats.contains(n_floor)) {
            QMessageBox::StandardButton btClicked =
                    QMessageBox::question(this, "Поменять беседы местами?", "Для " + QString::number(n_floor) +
                                  " этажа уже существует беседа \"" + m_chats[n_floor].getTitle() +
                                  "\". Поменять беседы \"" + n_chat.getTitle() + "\" и \"" +
                                  m_chats[n_floor].getTitle() + "\" местами?");

            if (btClicked == QMessageBox::Yes) {
                VkChat t_chat = m_chats[n_floor];
                m_chats[n_floor] = n_chat;
                m_chats[floor] = t_chat;
            }
        } else {
            m_chats[n_floor] = n_chat;
            m_chats.remove(floor);
        }
        updateChatsTable();
    }
}

void DialogChatsList::onDeleteChat(uint8_t floor, VkChat chat)
{
    QMessageBox::StandardButton btClicked = QMessageBox::question(this, "Удалить беседу?", "Вы действительно хотите удалить беседу \"" + chat.getTitle() + "\" из списка?");
    if (btClicked == QMessageBox::Yes) {
        m_chats.remove(floor);
        updateChatsTable();
    }
}

void DialogChatsList::updateChatsTable()
{
    QList<uint8_t> keys = m_chats.keys();
    std::sort(keys.begin(), keys.end());

    QTableWidget* table = ui->tableChats;
    table->setRowCount(0);

    foreach (uint8_t floor, keys) {
        VkChat chat = m_chats[floor];
        table->insertRow (ui->tableChats->rowCount());
        int lastRow = ui->tableChats->rowCount()-1;
        updateChatsTableRow(lastRow, floor, chat);

        ChatActionButton *btEditChat = new ChatActionButton("Изменить", chat, ui->tableChats);
        ChatActionButton *btDeleteChat = new ChatActionButton("Удалить", chat, ui->tableChats);
        btEditChat->setFloor(floor);
        btEditChat->setRow(lastRow);
        btDeleteChat->setFloor(floor);
        btDeleteChat->setRow(lastRow);

        QWidget *widgetWrapper = new QWidget();
        QHBoxLayout *layoutBt = new QHBoxLayout(widgetWrapper);
        QSpacerItem *vertSpacerHeader = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QSpacerItem *vertSpacerFooter= new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layoutBt->addItem(vertSpacerHeader);
        layoutBt->addWidget(btEditChat);
        layoutBt->addWidget(btDeleteChat);

        layoutBt->addItem(vertSpacerFooter);
        ui->tableChats->setCellWidget(
                 lastRow,
                 3,
                 widgetWrapper);

        connect(btEditChat, SIGNAL(cabtClickedFloor(uint8_t, VkChat)), this, SLOT(onEditChat(uint8_t, VkChat)));
        connect(btDeleteChat, SIGNAL(cabtClickedFloor(uint8_t, VkChat)), this, SLOT(onDeleteChat(uint8_t, VkChat)));

        ui->tableChats->resizeRowToContents(lastRow);
        ui->tableChats->resizeColumnsToContents();
    }
}

void DialogChatsList::updateChatsTableRow(uint row, uint8_t floor, VkChat chat)
{
    ui->tableChats->setItem
            (row,
             0,
             new QTableWidgetItem(QString::number(chat.getId())));
    ui->tableChats->setItem
            (row,
             1,
             new QTableWidgetItem(chat.getTitle()));
    ui->tableChats->setItem
            (row,
             2,
             new QTableWidgetItem(QString::number(floor)));
}
