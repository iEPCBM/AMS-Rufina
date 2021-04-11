#ifndef CHATACTIONBUTTON_H
#define CHATACTIONBUTTON_H

#include <QPushButton>
#include <QWidget>
#include "vkApi/vkchat.h"

class ChatActionButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ChatActionButton(QString text, VkChat chat, uint row = 0, QWidget *parent = nullptr);
    ~ChatActionButton();
    VkChat chat() const;
    void setChat(VkChat chat);

    uint row() const;
    void setRow(const uint &row);

public slots:
    void doChatAction();

signals:
    void cabtClicked(uint, VkChat);

private:
    VkChat m_chat;
    uint m_row;
};

#endif // CHATACTIONBUTTON_H
