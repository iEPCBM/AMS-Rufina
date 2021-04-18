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
