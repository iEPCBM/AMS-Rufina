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
