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

void DialogAddChat::onChatGot(QJsonDocument json_doc)
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
        connect(&chat,SIGNAL(dataWasGot(QJsonDocument)),this, SLOT(onChatGot(QJsonDocument)));
        chat.getConversationData();
        id++;
        addChatToTable();
    }
}

void DialogAddChat::addChatToTable()
{
    ui->tableChats->insertRow ( ui->tableChats->rowCount() );
    ui->tableChats->setItem ( ui->tableChats->rowCount()-1,
                             0,
                             new QTableWidgetItem("123"));
}
