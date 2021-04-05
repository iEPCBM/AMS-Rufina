#include "dialogchatsettings.h"
#include "ui_dialogchatsettings.h"

DialogChatSettings::DialogChatSettings(VkChat *chat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChatSettings)
{
    ui->setupUi(this);
    m_chat = chat;
    ui->leChatId->setText(QString::number(m_chat->getId()));
    if (m_chat->hasTitle()) {
        ui->leChatTitle->setText(m_chat->getTitle());
    }
}

DialogChatSettings::~DialogChatSettings()
{
    delete ui;
}
