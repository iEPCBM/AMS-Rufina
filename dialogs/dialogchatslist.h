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

#ifndef DIALOGCHATSLIST_H
#define DIALOGCHATSLIST_H

#include <QDialog>
#include <QHash>
#include "dialogs/dialogaddchat.h"
#include "dialogs/dialogchatsettings.h"
#include "vkApi/vkchat.h"
#include "filepaths.h"

namespace Ui {
class DialogChatsList;
}

class DialogChatsList : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChatsList(QHash<uint8_t, VkChat> chats, QString token = "", bool isEncrypted = false, QString iv="", QWidget *parent = nullptr);
    ~DialogChatsList();

    void setToken(const QString &token, const bool &isEncrypted);

    QHash<uint8_t, VkChat> getChats() const;

private slots:
    void on_btnAddChat_clicked();
    void onEditChat(uint8_t floor, VkChat chat);
    void onDeleteChat(uint8_t floor, VkChat chat);

    void on_btnDeleteAllChats_clicked();

private:
    Ui::DialogChatsList *ui;
    QString m_token;
    QString m_IV;
    bool m_isEncrypted;
    QHash<uint8_t, VkChat> m_chats;

    void updateChatsTable();
    void updateChatsTableRow(uint row, uint8_t floor, VkChat chat);
};

#endif // DIALOGCHATSLIST_H
