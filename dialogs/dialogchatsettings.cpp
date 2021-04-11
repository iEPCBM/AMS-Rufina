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

DialogChatSettings::DialogChatSettings(uint8_t floor, VkChat chat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChatSettings)
{
    ui->setupUi(this);
    m_chat = chat;
    ui->leChatId->setText(QString::number(m_chat.getId()));
    if (m_chat.hasTitle()) {
        ui->leChatTitle->setText(m_chat.getTitle());
    }
    m_floor = floor;
    ui->spinFloor->setValue(floor);
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

void DialogChatSettings::accept()
{
    if (ui->leChatTitle->text().isEmpty()) {
       QMessageBox::critical(this, "Название беседы пустое", "Название беседы не может быть пустым. Введите название в соответствующее поле.");
       return;
    }
    QDialog::accept();
}

uint8_t DialogChatSettings::floor() const
{
    return m_floor;
}
