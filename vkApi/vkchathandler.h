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

#ifndef VKCHATHANDLER_H
#define VKCHATHANDLER_H

#include <QString>
#include <QHash>
#include <QEventLoop>
#include <QJsonArray>
#include "vkApi/vkapi.h"
#include "vkApi/vkuser.h"
#include "vkApi/vkuserhandler.h"
#include "settings.h"
#include "vkApi/vkchat.h"
#include "vkApi/AbstractMethod.h"
#include <QObject>

class VkChatHandler : public QObject, public AbstractMethod
{
    Q_OBJECT
public:
    explicit VkChatHandler(QObject *parent = nullptr, QString token="");
    ~VkChatHandler() {}
    void clear();
    bool isValid();
    void getConversationData(uint32_t id);

    unsigned int getId() const;
    void setId(unsigned int id);
    void responseChatParse();
    VkChat getChat() const;

signals:
    void dataWasGot(VkChat);

private:
    QJsonDocument m_jsonResp;
    QString m_token;
    VkApi api;
    VkChat m_chat;
    bool m_isValid;
};

#endif // VKCHATHANDLER_H
