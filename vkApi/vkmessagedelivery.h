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

#ifndef VKMESSAGEDELIVERY_H
#define VKMESSAGEDELIVERY_H

#include <QObject>
#include "vkApi/vkapi.h"
#include "vkApi/vkerror.h"
#include "vkApi/AbstractMethod.h"

class VkMessageDelivery : public QObject, public AbstractMethod
{
    Q_OBJECT
public:
    explicit VkMessageDelivery(QString token, QObject *parent = nullptr);
    ~VkMessageDelivery() {}
    void sendMessage(int peer_id, QString text);
    QJsonDocument getJsonResponse() const;

    bool hasError() const;
    void clear();

signals:
    void messageSent(QJsonDocument);
public slots:
    void onRequestFinished(QJsonDocument json_doc);
private:
    VkApi m_api;
    QJsonDocument m_jsonResponse;
};

#endif // VKMESSAGEDELIVERY_H
