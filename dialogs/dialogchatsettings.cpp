#include "dialogchatsettings.h"
#include "ui_dialogchatsettings.h"

DialogChatSettings::DialogChatSettings(VkChat chat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChatSettings)
{
    ui->setupUi(this);
    m_chat = chat;
    ui->leChatId->setText(QString::number(m_chat.getId()));
    if (m_chat.hasTitle()) {
        ui->leChatTitle->setText(m_chat.getTitle());
    }
}

DialogChatSettings::~DialogChatSettings()
{
    delete ui;
}

void DialogChatSettings::on_buttonBox_accepted()
{
    m_chat.setTitle(ui->leChatTitle->text());
    m_floor = static_cast<uint8_t>(ui->spinFloor->value());
}

VkChat DialogChatSettings::chat() const
{
    return m_chat;
}

uint8_t DialogChatSettings::floor() const
{
    return m_floor;
}
