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

#include "chatactionbutton.h"

ChatActionButton::ChatActionButton(QString text, VkChat chat, QWidget *parent):QPushButton(text, parent)
{
    m_chat = chat;
    connect(this, SIGNAL(clicked()), this, SLOT(doChatAction()));
}

VkChat ChatActionButton::chat() const
{
    return m_chat;
}

void ChatActionButton::setChat(VkChat chat)
{
    m_chat = chat;
}

void ChatActionButton::doChatAction()
{
    emit cabtClicked(m_row, m_chat);
    emit cabtClickedFloor(m_floor, m_chat);
}

uint8_t ChatActionButton::floor() const
{
    return m_floor;
}

void ChatActionButton::setFloor(const uint8_t &floor)
{
    m_floor = floor;
}

void ChatActionButton::setRow(const uint &row)
{
    m_row = row;
}

uint ChatActionButton::row() const
{
    return m_row;
}
