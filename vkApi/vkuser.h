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

#ifndef VKUSER_H
#define VKUSER_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVector>
#include "vkApi/vkapi.h"

#define VK_FLD_FIRST_NAME "first_name"
#define VK_FLD_LAST_NAME "last_name"
#define VK_FLD_ID "id"

class VkUser
{
public:
    VkUser(QJsonObject vkApiReponseObj);
    VkUser(uint32_t id, QString name, QString surname);
    VkUser();
    QString name() const;
    QString surname() const;

    uint32_t getId() const;

    void setName(const QString &name);

    void setSurname(const QString &surname);

    void setId(const uint32_t &id);

     QString getAssembledName();
private:
    QString m_name;
    QString m_surname;
    uint32_t m_id;
};

#endif // VKUSER_H
