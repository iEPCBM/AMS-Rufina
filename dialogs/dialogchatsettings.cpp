/*
 *  AMS Rufina - automated message delivery program
 *  Copyright (C) 2021 Rishat D. Kagirov (iEPCBM)
 *
 *     This file is part of AMS Rufina.
 *
 *  AMS Rufina is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Foobar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "dialogchatsettings.h"
#include "ui_dialogchatsettings.h"

DialogChatSettings::DialogChatSettings(VkChat chat, QHash<uint8_t, VkChat>savedChats, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChatSettings)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

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
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

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

bool DialogChatSettings::hasChatConflict()
{
    return m_savedChats.contains(m_floor); // &m_savedChats[floor].hasTitle()
}

VkChat DialogChatSettings::chat() const
{
    return m_chat;
}

void DialogChatSettings::accept()
{
    m_chat.setTitle(ui->leChatTitle->text());
    m_floor = static_cast<uint8_t>(ui->spinFloor->value());
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
