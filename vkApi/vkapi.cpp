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

#include "vkapi.h"
#include "../mainwindow.h"

VkApi::VkApi(QString token)
{
    m_token = token;
    netMngr = new QNetworkAccessManager(this);
}

VkApi::~VkApi()
{
    delete netMngr;
    netMngr = NULL;
}

void VkApi::sendRequest(QString method, QHash<QString, QString> args)
{
    args["access_token"] = m_token;
    args["v"] = VK_API_VER;
    QString query = assemblyQuery(args);
    QString strUrl = VK_API_ENDPOINT+method+query;

    netMngr = new QNetworkAccessManager(this);

    connect(netMngr, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    netMngr->get(QNetworkRequest(QUrl(strUrl)));
    m_loop.exec(); //NOTE: Stop main thread
}

QByteArray VkApi::getResponse()
{
    return m_byteArrReply;
}

QJsonDocument VkApi::parseResponse()
{
    m_isError = false;
    QJsonParseError parseError;
    QJsonDocument json_doc = QJsonDocument::fromJson(m_byteArrReply, &parseError);
    QJsonObject json_obj = json_doc.object();
    if (parseError.error != QJsonParseError::NoError || json_obj.contains("error")) {
        m_isError = true;
        if (json_obj.contains("error")) {
            QJsonObject json_vkError = json_obj.value("error").toObject();
            int errCode = json_vkError.value("error_code").toInt();
            QString errMsg = json_vkError.value("error_msg").toString();
            m_vkError.setCode(errCode);
            m_vkError.setDescription(errMsg);
        }
    }
    return json_doc;
}

int32_t VkApi::getRandomId(QString strMsg, int peerId)
{
    R_ASSERT(!strMsg.isEmpty(), return -1, nullptr);
    QByteArray hash = QCryptographicHash::hash(strMsg.toUtf8(), QCryptographicHash::Sha256);
    int32_t val = static_cast<int32_t>(hash.at(strMsg.length()%0x20));
    int8_t factor = hash.at(peerId%0x20)%2==0?-1:1;
    val += factor*peerId/(strMsg.length());
    return val;
}

QJsonDocument VkApi::getJsonResponse() const
{
    return m_jsonResponse;
}

void VkApi::onFinished(QNetworkReply *r)
{
    m_loop.exit();
    if (r->error()!=QNetworkReply::NoError) {
        m_isError=true;
        ErrorMessages::errorNetwork(nullptr, r->errorString());
    }
    m_byteArrReply = r->readAll();
    m_jsonResponse = parseResponse();
    emit requestFinished(m_jsonResponse);
}

QString VkApi::assemblyQuery(QHash<QString, QString> args)
{
    QString strQuery = "?";
    QHashIterator<QString, QString> i(args);
    while (i.hasNext()) {
        i.next();
        strQuery+=i.key()+"="+i.value();
        if (i.hasNext()) {
            strQuery+="&";
        }
    }
    return strQuery;
}

VkError VkApi::getVkError() const
{
    return m_vkError;
}

bool VkApi::isError() const
{
    return m_isError;
}
