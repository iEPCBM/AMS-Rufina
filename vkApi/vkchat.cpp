#include "vkchat.h"

VkChat::VkChat(int id, QString title, QVector<VkUser> administrators, VkUser owner)
{
    m_id = id;
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

