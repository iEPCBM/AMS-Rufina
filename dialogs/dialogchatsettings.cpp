#include "dialogchatsettings.h"
#include "ui_dialogchatsettings.h"

DialogChatSettings::DialogChatSettings(VkChat chat, QHash<uint8_t, VkChat>savedChats, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChatSettings)
{
    ui->setupUi(this);
    m_chat = chat;
    ui->leChatId->setText(QString::number(m_chat.getId()));
    if (m_chat.hasTitle()) {
        ui->leChatTitle->setText(m_chat.getTitle());
    }
    m_savedChats = savedChats;
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

bool DialogChatSettings::hasChatConflict()
{
    return m_savedChats.contains(ui->spinFloor->value()); // &m_savedChats[floor].hasTitle()
}

VkChat DialogChatSettings::chat() const
{
    return m_chat;
}

void DialogChatSettings::accept()
{
    if (ui->leChatTitle->text().isEmpty()) {
       QMessageBox::warning(this, "Название беседы пустое", "Название беседы не может быть пустым. Введите название в соответствующее поле.");
       return;
    }
    if (hasChatConflict()) {
        QMessageBox::StandardButtons btClicked = QMessageBox::question(this, "Заменить беседу?",
                             "Беседа для " + QString::number(m_floor)+ " этажа уже существует. Заменить беседу \"" +
                                                                      m_savedChats[m_floor].getTitle() + "\" на беседу \"" +
                                                                      m_chat.getTitle() + "\"?");
        if (btClicked == QMessageBox::No) {
            return;
        }
    }
    QDialog::accept();
}

uint8_t DialogChatSettings::floor() const
{
    return m_floor;
}

void DialogChatSettings::on_spinFloor_valueChanged(int arg1)
{
    m_floor = static_cast<uint8_t>(arg1);
}

void DialogChatSettings::on_leChatTitle_textChanged(const QString &arg1)
{
    m_chat.setTitle(arg1);
}
