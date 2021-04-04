#ifndef DIALOGADDCHAT_H
#define DIALOGADDCHAT_H

#include <QDialog>
#include <QtWidgets>
#include <QSpacerItem>
#include "vkApi/vkapi.h"
#include "vkApi/vkchat.h"
#include "vkApi/vkchathandler.h"
#include "widgets/chatactionbutton.h"

#define STR_OWNER_MARKER "(создатель)"

namespace Ui {
class DialogAddChat;
}

class DialogAddChat : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddChat(QWidget *parent = nullptr);
    ~DialogAddChat();

public slots:
    void onChatGot(VkChat chat);
    void onAddChat(VkChat *chat);

private slots:
    void on_btStartStopFind_clicked();

private:
    Ui::DialogAddChat *ui;
    bool m_isSearching = false;
    void findChats();
    void getAdmins();
    void getOwner();
    void addChatToTable(VkChat chat, VkUser owner, QList<VkUser> admins, uint32_t actionId);
    void addActionButtonsToRow(int row);
    void startSearching();
    void stopSearching();
    void addChat(VkChat *chat);
    QList<uint32_t> filterUserIds(QList<int> usrIds);
    inline bool isUserId(int id);
    //VkChatHandler m_chatHandler;
    QList<VkChat> m_listChats;
};

#endif // DIALOGADDCHAT_H
