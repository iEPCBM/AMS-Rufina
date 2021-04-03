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
    while(m_isSearching) {
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
        if (isUserId(chat.getOwnerId()) && chat.getOwnerId()!=0) {
            usrHandler.sendRequest(chat.getOwnerId());
            owner = usrHandler.getUsers().at(0);
        } else {
            owner.setName(STR_UNKNOWN);
        }

        if (!chatHandler.isValid()) {
            stopSearching();
            break;
        }
        id++;
        //m_listChats.push_back(chat);
        addChatToTable(chatHandler.getChat(), owner, admins);
        chatHandler.clear();
    }
}

void DialogAddChat::addChatToTable(VkChat chat, VkUser owner, QList<VkUser> admins)
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
    QString strAdmList = "";
    if (owner.getAssembledName().trimmed() != QString(STR_UNKNOWN).trimmed()) {
        "<p><a href=\"https://vk.com/id"+QString::number(owner.getId())+"\">" +owner.getAssembledName().trimmed() + "</a>";
        strAdmList+=QString(" ")+STR_OWNER_MARKER+"\n";
        strAdmList += "</p>\n";
    }
    else {
        strAdmList = owner.getAssembledName().trimmed();
    }
    foreach (VkUser user, admins) {
        strAdmList += "<p><a href=\"https://vk.com/id"+QString::number(user.getId())+"\">" + user.getAssembledName() + "</a></p>\n";
    }
    QLabel *lbAdmins = new QLabel(strAdmList.trimmed(), ui->tableChats);
    lbAdmins->setTextFormat(Qt::RichText);
    lbAdmins->setOpenExternalLinks(true);
    ui->tableChats->setCellWidget(
             lastRow,
             2,
             lbAdmins);
    lbAdmins = NULL;
    ui->tableChats->resizeRowToContents(lastRow);
    ui->tableChats->resizeColumnsToContents();
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
