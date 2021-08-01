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

#ifndef DIALOGCHATSETTINGS_H
#define DIALOGCHATSETTINGS_H

#include <QDialog>
#include <QMessageBox>

#include "vkApi/vkchat.h"

namespace Ui {
class DialogChatSettings;
}

class DialogChatSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChatSettings(VkChat chat, QHash<uint8_t, VkChat>savedChats = QHash<uint8_t, VkChat>(), QWidget *parent = nullptr);
    explicit DialogChatSettings(uint8_t floor, VkChat chat, QWidget *parent = nullptr);
    ~DialogChatSettings();

    uint8_t floor() const;

    VkChat chat() const;

private slots:
    void on_spinFloor_valueChanged(int arg1);

    void on_leChatTitle_textChanged(const QString &arg1);

    void accept();

private:
    Ui::DialogChatSettings *ui;
    VkChat m_chat;
    uint8_t m_floor;
    QHash<uint8_t, VkChat> m_savedChats;

    bool hasChatConflict();
};
#endif // DIALOGCHATSETTINGS_H
