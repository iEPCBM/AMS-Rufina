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

#ifndef VKUSERHANDLER_H
#define VKUSERHANDLER_H

#include <QString>
#include <QObject>
#include "vkApi/vkuser.h"
#include "vkApi/vkerror.h"
#include "vkApi/AbstractMethod.h"


class VkUserHandler : public QObject, public AbstractMethod
{
    Q_OBJECT
public:  
    explicit VkUserHandler(QObject *parent=nullptr, QString token="");
    ~VkUserHandler() {}

public:
    void clear();

    void sendRequest(uint32_t id);
    void sendRequest(QList<uint32_t>id);

    QList<VkUser> getUsers() const;

signals:
    void requestFinished(QVector<VkUser*>);

private:
    QString m_token;
    VkApi m_api;
    QList<VkUser> m_vecUsers;
};

#endif // VKUSERHANDLER_H
