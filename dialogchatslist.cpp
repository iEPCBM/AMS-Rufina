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
    QHash<uint8_t, VkChat> retHash;
    QTableWidget* table = ui->tableChats;

    for (auto i=0; i<ui->tableChats->rowCount(); i++) {
        VkChat memChat(table->item(i, 0)->text().toInt(), table->item(i, 1)->text());
        retHash[table->item(i, 2)->text().toUInt()]=memChat;
    }
    return retHash;
}

void DialogChatsList::setChats(QHash<uint8_t, VkChat> chats)
{
    QList<uint8_t> keys = chats.keys();
    QTableWidget* table = ui->tableChats;

    foreach (uint8_t floor, keys) {
        VkChat chat = chats[floor];
        table->insertRow (ui->tableChats->rowCount());
        int lastRow = ui->tableChats->rowCount()-1;
        ui->tableChats->setItem
                (lastRow,
                 0,
                 new QTableWidgetItem(QString::number(chat.getId())));
        ui->tableChats->setItem
                (lastRow,
                 1,
                 new QTableWidgetItem(chat.getTitle()));
        ui->tableChats->setItem
                (lastRow,
                 2,
                 new QTableWidgetItem(QString::number(floor)));
    }
}

void DialogChatsList::on_btnAddChat_clicked()
{
    DialogAddChat dlgAddChat(this);
    dlgAddChat.exec();
}
