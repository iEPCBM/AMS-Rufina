#ifndef CHATACTIONBUTTON_H
#define CHATACTIONBUTTON_H

#include <QPushButton>
#include <QWidget>
#include "vkApi/vkchat.h"

class ChatActionButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ChatActionButton(QString text, VkChat *chat = nullptr, QWidget *parent = nullptr);
    ~ChatActionButton();
    VkChat *chat() const;
    void setChat(VkChat *chat);

public slots:
    void doChatAction();

signals:
    void cabtClicked(VkChat *);

private:
    VkChat *m_chat;
};

#endif // CHATACTIONBUTTON_H
