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

#ifndef VKAPI_H
#define VKAPI_H

#include <QString>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHash>
#include <QHashIterator>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTextCodec>
#include <QEventLoop>
#include "vkApi/vkerror.h"

#define VK_API_VER "5.130"
#define VK_API_ENDPOINT "https://api.vk.com/method/"
#define VK_API_MULTICHAT_BASE_ID 2000000000

class VkApi : public QObject
{
    Q_OBJECT
public:
    explicit VkApi(QString token);
    ~VkApi();
    void sendRequest(QString method, QHash<QString, QString> args);
    QByteArray getResponse();

    static int32_t getRandomId(QString strMsg, int peerId);
    QJsonDocument getJsonResponse() const;
    bool isError() const;

    VkError getVkError() const;

signals:
    void requestFinished(QJsonDocument json_doc);

public slots:
    void onFinished(QNetworkReply *r);

private:
    QJsonDocument parseResponse();
    QEventLoop m_loop;

    QByteArray m_byteArrReply;
    QString m_token;
    QObject* m_parent;
    QString assemblyQuery (QHash<QString, QString> args);
    QNetworkAccessManager *netMngr;
    QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> netReply;
    bool m_isError = false;
    QJsonDocument m_jsonResponse;
    VkError m_vkError;
};

#endif // VKAPI_H
