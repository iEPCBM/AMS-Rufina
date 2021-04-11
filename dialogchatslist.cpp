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

        ChatActionButton *btEditChat = new ChatActionButton("Изменить", chat, lastRow, ui->tableChats);
        ChatActionButton *btDeleteChat = new ChatActionButton("Удалить", chat, lastRow, ui->tableChats);
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

        connect(btEditChat, SIGNAL(cabtClicked(uint, VkChat)), this, SLOT(onEditChat(uint, VkChat)));
        connect(btDeleteChat, SIGNAL(cabtClicked(uint, VkChat)), this, SLOT(onEditChat(uint, VkChat)));

        ui->tableChats->resizeRowToContents(lastRow);
        ui->tableChats->resizeColumnsToContents();
    }
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

void DialogChatsList::onDeleteChat(uint row, VkChat chat)
{
    QMessageBox::StandardButton btClicked = QMessageBox::question(this, "Удалить беседу?", "Вы действительно хотите удалить беседу \"" + chat.getTitle() + "\" из списка?");
    if (btClicked == QMessageBox::Yes) {

    }
}
