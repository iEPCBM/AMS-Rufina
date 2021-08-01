/*
 *  AMS Rufina - automated message delivery program
 *  Copyright (C) 2021 Rishat D. Kagirov (iEPCBM)
 *
 *     This file is part of AMS Rufina.
 *
 *  AMS Rufina is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Foobar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

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
#include "dialogs/dialogpasswordenter.h"
#include "settings.h"
#include "filepaths.h"

#define STR_OWNER_MARKER "(создатель)"

namespace Ui {
class DialogAddChat;
}

class DialogAddChat : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddChat(QString token, bool isEncrypted, QString iv = "", QWidget *parent = nullptr);
    ~DialogAddChat();

    QHash<uint8_t, VkChat> getAddedChats() const;
    void setAddedChats(const QHash<uint8_t, VkChat> &addedChats);

public slots:
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

    QList<uint32_t> filterUserIds(QList<int> usrIds);
    inline bool isUserId(int id);

    void setChatAddedState(uint row, bool state);
    //VkChatHandler m_chatHandler;
    QHash<uint8_t, VkChat> m_savedChats; //floor - VkChat
    QList<VkChat> m_listDetectedChats;

    QString m_encryptedToken;
    QString m_decryptedToken;
    QString m_IV;
    bool m_isEncryptedToken;

    bool  decryptToken();
};

#endif // DIALOGADDCHAT_H
