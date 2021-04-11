#ifndef DIALOGADDCHAT_H
#define DIALOGADDCHAT_H

#include <QDialog>
#include <QtWidgets>
#include <QSpacerItem>
#include "vkApi/vkapi.h"
#include "vkApi/vkchat.h"
#include "vkApi/vkchathandler.h"
#include "widgets/chatactionbutton.h"
#include "dialogs/dialogchatconfirmation.h"
#include "dialogs/dialogchatsettings.h"
#include "settings.h"

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

    QHash<uint8_t, VkChat> getAddedChats() const;
    void setAddedChats(const QHash<uint8_t, VkChat> &addedChats);

public slots:
    void onChatGot(VkChat chat);
    void onAddChat(uint row, VkChat chat);

private slots:
    void on_btStartStopFind_clicked();

private:
    Ui::DialogAddChat *ui;
    bool m_isSearching = false;
    void findChats();
    void getAdmins();
    void getOwner();
    void addChatToTable(VkChat chat, VkUser owner, QList<VkUser> admins, uint32_t actionId);
    int32_t findRowByChatId(uint chatId);
    void updateChatTitleInRow(int row, QString title);
    void addActionButtonsToRow(int row);
    void startSearching();
    void stopSearching();

    bool hasSavedChat(VkChat chat);
    bool hasSavedChat(uint id);
    bool hasFloorConflict(uint8_t floor);

    QList<uint32_t> filterUserIds(QList<int> usrIds);
    inline bool isUserId(int id);

    void setChatAddedState(uint row, bool state);
    //VkChatHandler m_chatHandler;
    QHash<uint8_t, VkChat> m_savedChats; //floor - VkChat
    QList<VkChat> m_listDetectedChats;
    Settings *m_settings;
};

#endif // DIALOGADDCHAT_H
