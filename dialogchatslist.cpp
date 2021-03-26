#include "dialogchatslist.h"
#include "ui_dialogchatslist.h"

DialogChatsList::DialogChatsList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChatsList)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

DialogChatsList::~DialogChatsList()
{
    delete ui;
}

void DialogChatsList::on_btnAddChat_clicked()
{
    DialogAddChat dlgAddChat(this);
    dlgAddChat.exec();
}
