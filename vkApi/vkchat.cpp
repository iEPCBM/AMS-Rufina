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

#include "vkchat.h"

VkChat::VkChat(int id, QString title, QList<int> administratorsIds, int ownerId)
{
    m_id = id;
    m_strTitle = title;
    m_administratorsIds = administratorsIds;
    m_ownerId = ownerId;
}

VkChat::VkChat(int id, QString title)
{
    m_id = id;
    m_strTitle = title;
}

VkChat::VkChat(int id)
{
    m_id = id;
}

VkChat::VkChat()
{
    m_strTitle = "";
    m_id = 0;
}

VkChat::~VkChat(){

}

QString VkChat::getTitle() const
{
    return m_strTitle;
}

unsigned int VkChat::getId() const
{
    return m_id;
}

void VkChat::setTitle(const QString &strTitle)
{
    m_strTitle = strTitle;
}

void VkChat::setId(unsigned int id)
{
    m_id = id;
}

QList<int> VkChat::getAdministratorsIds() const
{
    return m_administratorsIds;
}

void VkChat::setAdministratorsIds(const QList<int> &administratorsIds)
{
    m_administratorsIds = administratorsIds;
}

int VkChat::getOwnerId() const
{
    return m_ownerId;
}

void VkChat::setOwnerId(const int &ownerId)
{
    m_ownerId = ownerId;
}

bool VkChat::hasOwner()
{
    return m_ownerId > 0;
}

bool VkChat::hasAdmins()
{
    return !m_administratorsIds.empty();
}

bool VkChat::hasTitle()
{
    return !m_strTitle.isEmpty();
}

bool VkChat::operator==(const VkChat &a)
{
    if (m_id==a.getId()) {
        return true;
    }
    return false;
}

