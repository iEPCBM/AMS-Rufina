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

void DialogAddChat::onChatGot()
{
    qDebug()<<"got";
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
        VkChat chat(id,"");
        connect(&chat,SIGNAL(dataWasGot()),this, SLOT(onChatGot()));
        chat.getConversationData();
        if (!chat.isValid()) {
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
             new QTableWidgetItem(chat.getId()));
    ui->tableChats->setItem
            (lastRow,
             1,
             new QTableWidgetItem(chat.getTitle()));

}
