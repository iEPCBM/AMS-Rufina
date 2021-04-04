#include "chatactionbutton.h"

ChatActionButton::ChatActionButton(QString &text, VkChat *chat, QWidget *parent):QPushButton(text, parent)
{
    m_chat = chat;
    connect(this, SIGNAL(clicked()), this, SLOT(doChatAction()));
}

ChatActionButton::~ChatActionButton()
{
    delete m_chat;
    m_chat = NULL;
}

VkChat *ChatActionButton::chat() const
{
    return m_chat;
}

void ChatActionButton::setChat(VkChat *chat)
{
    m_chat = chat;
}

void ChatActionButton::doChatAction()
{
    emit cabtClicked(m_chat);
}
