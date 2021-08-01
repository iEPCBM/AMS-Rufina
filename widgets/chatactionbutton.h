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

#ifndef CHATACTIONBUTTON_H
#define CHATACTIONBUTTON_H

#include <QPushButton>
#include <QWidget>
#include "vkApi/vkchat.h"

class ChatActionButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ChatActionButton(QString text, VkChat chat, QWidget *parent = nullptr);

    VkChat chat() const;
    void setChat(VkChat chat);

    uint row() const;
    void setRow(const uint &row);

    uint8_t floor() const;
    void setFloor(const uint8_t &floor);

public slots:
    void doChatAction();

signals:
    void cabtClicked(uint, VkChat);
    void cabtClickedFloor(uint8_t, VkChat);

private:
    VkChat m_chat;
    uint m_row = 0;
    uint8_t m_floor = 0;
};

#endif // CHATACTIONBUTTON_H
