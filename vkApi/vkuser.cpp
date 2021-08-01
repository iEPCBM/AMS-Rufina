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

#include "vkuser.h"

VkUser::VkUser(QJsonObject vkApiReponseObj)
{
    m_name = vkApiReponseObj.value(VK_FLD_FIRST_NAME).toString();
    m_surname = vkApiReponseObj.value(VK_FLD_LAST_NAME).toString();
    m_id = vkApiReponseObj.value(VK_FLD_ID).toInt();
}

VkUser::VkUser(uint32_t id, QString name, QString surname)
{
    m_id = id;
    m_name = name;
    m_surname = surname;
}

VkUser::VkUser()
{

}

QString VkUser::name() const
{
    return m_name;
}

QString VkUser::surname() const
{
    return m_surname;
}

uint32_t VkUser::getId() const
{
    return m_id;
}

void VkUser::setName(const QString &name)
{
    m_name = name;
}

void VkUser::setSurname(const QString &surname)
{
    m_surname = surname;
}

void VkUser::setId(const uint32_t &id)
{
    m_id = id;
}

QString VkUser::getAssembledName()
{
    return m_name + " " + m_surname;
}
