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

#include "vkmessagedelivery.h"

VkMessageDelivery::VkMessageDelivery(QString token, QObject *parent) : QObject(parent),
    m_api(token)
{
    clear();
}

void VkMessageDelivery::sendMessage(int peer_id, QString text)
{
    clear();
    QHash<QString, QString> query;
    query["random_id"]=QString::number(VkApi::getRandomId(text, peer_id));
    query["peer_id"]=QString::number(peer_id);
    query["message"]=QUrl::toPercentEncoding(text);
    connect(&m_api, SIGNAL(requestFinished(QJsonDocument)), this, SLOT(onRequestFinished(QJsonDocument)));
    m_api.sendRequest("messages.send", query);
    m_jsonResponse = m_api.getJsonResponse();
    if (m_api.isError()) {
        m_vkError = m_api.getVkError();
        m_hasError = true;
    }
}

void VkMessageDelivery::onRequestFinished(QJsonDocument json_doc)
{
    emit messageSent(json_doc);
}

bool VkMessageDelivery::hasError() const
{
    return m_hasError;
}

void VkMessageDelivery::clear()
{
    m_vkError.clear();
    m_hasError = false;
}

QJsonDocument VkMessageDelivery::getJsonResponse() const
{
    return m_jsonResponse;
}
