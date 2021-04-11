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

