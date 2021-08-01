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

#ifndef VKCHAT_H
#define VKCHAT_H

#include <QString>
#include <QHash>
#include <QEventLoop>
#include <QJsonArray>
#include "vkApi/vkapi.h"
#include "vkApi/vkuser.h"
#include "vkApi/vkuserhandler.h"

#define STR_UNKNOWN "Нет данных"

class VkChat
{
public:
    VkChat(int id, QString title, QList<int> administratorsIds, int ownerId);
    VkChat(int id, QString title);
    VkChat(int id);
    VkChat();
    ~VkChat();

    QString getTitle() const;

    unsigned int getId() const;

    void setTitle(const QString &strTitle);

    void setId(unsigned int id);

    QList<int> getAdministratorsIds() const;
    void setAdministratorsIds(const QList<int> &administratorsIds);

    int getOwnerId() const;
    void setOwnerId(const int &ownerId);

    bool hasOwner();
    bool hasAdmins();
    bool hasTitle();

    bool operator== (const VkChat &a);
private:
    QString m_strTitle;
    QList<int> m_administratorsIds;
    int m_ownerId=0;
    unsigned int m_id;
};
#endif // VKCHAT_H
