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

#include "vkchathandler.h"

VkChatHandler::VkChatHandler(QObject *parent, QString token) :
    QObject(parent),
    api(token)
{
    clear();
}

void VkChatHandler::clear()
{
    m_chat = VkChat();
    m_isValid = true;
    m_hasError = false;
    m_jsonResp = QJsonDocument();
}

bool VkChatHandler::isValid()
{
    return m_isValid;
}

void VkChatHandler::getConversationData(uint32_t id)
{
    m_chat.setId(id);
    QHash<QString, QString> query;
    query["peer_ids"]=QString::number(VK_API_MULTICHAT_BASE_ID+id);
    api.sendRequest("messages.getConversationsById", query);
    m_jsonResp = api.getJsonResponse();
    responseChatParse();
}

void VkChatHandler::responseChatParse()
{
    QJsonObject json_obj = m_jsonResp.object();
    if (api.isError()) {
        m_isValid = false;
        m_hasError = true;
        m_vkError = api.getVkError();
        return;
    }
    QJsonObject responseObj = json_obj.value("response").toObject();
    if (responseObj.value("count").toInt()==1) {
        QJsonObject item = responseObj.value("items").toArray()[0].toObject();
        if (item.value("peer").toObject().value("type").toString()=="chat") {
            QJsonObject objChatSettings = item.value("chat_settings").toObject();
            m_chat.setTitle(objChatSettings.value("title").toString(""));
            m_chat.setOwnerId(objChatSettings.value("owner_id").toInt());
            QJsonArray adminIds = objChatSettings.value("admin_ids").toArray();
            QList<int> adms;
            foreach (const QJsonValue& val, adminIds) {
                adms.append(val.toInt());
            }
            m_chat.setAdministratorsIds(adms);
            m_isValid = true;
        }
    }
}

VkChat VkChatHandler::getChat() const
{
    return m_chat;
}
