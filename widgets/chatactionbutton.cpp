#include "chatactionbutton.h"

ChatActionButton::ChatActionButton(QString text, VkChat chat, uint row, QWidget *parent):QPushButton(text, parent)
{
    m_chat = chat;
    m_row = row;
    connect(this, SIGNAL(clicked()), this, SLOT(doChatAction()));
}

ChatActionButton::~ChatActionButton()
{
    m_chat = NULL;
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
}

void ChatActionButton::setRow(const uint &row)
{
    m_row = row;
}

uint ChatActionButton::row() const
{
    return m_row;
}
