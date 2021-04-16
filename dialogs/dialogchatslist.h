#ifndef DIALOGCHATSLIST_H
#define DIALOGCHATSLIST_H

#include <QDialog>
#include "dialogs/dialogaddchat.h"
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
    explicit DialogChatsList(QHash<uint8_t, VkChat> chats, QString token = "", bool isEncrypted = false, QWidget *parent = nullptr);
    ~DialogChatsList();

    void setToken(const QString &token, const bool &isEncrypted);

    QHash<uint8_t, VkChat> getChats() const;

private slots:
    void on_btnAddChat_clicked();
    void onEditChat(uint8_t floor, VkChat chat);
    void onDeleteChat(uint8_t floor, VkChat chat);

private:
    Ui::DialogChatsList *ui;
    QString m_token;
    bool m_isEncrypted;
    QHash<uint8_t, VkChat> m_chats;

    void setChats(QHash<uint8_t, VkChat> chats);
    void updateChatsTable();
    void updateChatsTableRow(uint row, uint8_t floor, VkChat chat);
};

#endif // DIALOGCHATSLIST_H
