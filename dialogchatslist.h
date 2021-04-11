#ifndef DIALOGCHATSLIST_H
#define DIALOGCHATSLIST_H

#include <QDialog>
#include "dialogaddchat.h"
#include "dialogs/dialogchatsettings.h"
#include "vkApi/vkchat.h"
#include <QHash>

namespace Ui {
class DialogChatsList;
}

class DialogChatsList : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChatsList(QHash<uint8_t, VkChat> chats, QWidget *parent = nullptr);
    ~DialogChatsList();

    QHash<uint8_t, VkChat> getChats();
    void setChats(QHash<uint8_t, VkChat> chats);

private slots:
    void on_btnAddChat_clicked();
    void onEditChat(uint8_t floor, VkChat chat);
    void onDeleteChat(uint8_t floor, VkChat chat);

private:
    Ui::DialogChatsList *ui;
    QHash<uint8_t, VkChat> m_chats;

    void updateChatsTable();
    void updateChatsTableRow(uint row, uint8_t floor, VkChat chat);
};

#endif // DIALOGCHATSLIST_H
