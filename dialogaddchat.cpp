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
    addChatToTable(chat);
}


void DialogAddChat::on_btStartStopFind_clicked()
{
    m_isSearching = !m_isSearching;
    if (m_isSearching) {
        ui->btStartStopFind->setText("Завершить поиск");
        findChats();
    } else {
        ui->btStartStopFind->setText("Начать поиск");
    }

}

void DialogAddChat::findChats()
{
    uint32_t id=1;
    while(m_isSearching) {
        VkChatHandler chatHandler(this, id, "");
        VkUserHandler usrHandler(this, "");
        connect(&chatHandler,SIGNAL(dataWasGot(VkChat)),this, SLOT(onChatGot(VkChat)));
        chatHandler.getConversationData();
        if (!chatHandler.isValid()) {
            m_isSearching = false;
            break;
        }
        id++;
        //m_listChats.push_back(chat);
        //addChatToTable(chat);
    }
}

void DialogAddChat::addChatToTable(VkChat chat)
{
    ui->tableChats->insertRow ( ui->tableChats->rowCount() );
    int lastRow = ui->tableChats->rowCount()-1;
    ui->tableChats->setItem
            (lastRow,
             0,
             new QTableWidgetItem(QString::number(chat.getId())));
    ui->tableChats->setItem
            (lastRow,
             1,
             new QTableWidgetItem(chat.getTitle()));

}
