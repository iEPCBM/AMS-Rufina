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
    foreach ( VkUser* usr, m_administrators) {
        usr = const_cast<VkUser*>(usr);
        delete usr;
        usr = nullptr;
    }
    m_administrators.clear();
    delete m_usrOwner;
    m_usrOwner = nullptr;
}

QString VkChat::getTitle() const
{
    return m_strTitle;
}

QVector<VkUser*> VkChat::getAdministrators() const
{
    return m_administrators;
}

unsigned int VkChat::getId() const
{
    return m_id;
}

VkUser *VkChat::getOwner() const
{
    return m_usrOwner;
}

void VkChat::setAdministrators(const QVector<VkUser*> &administrators)
{
    m_administrators = administrators;
}

void VkChat::setOwner(const VkUser* usrOwner)
{
    m_usrOwner = const_cast<VkUser*>(usrOwner);
}

void VkChat::setTitle(const QString &strTitle)
{
    m_strTitle = strTitle;
}
