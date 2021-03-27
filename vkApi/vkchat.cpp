#include "vkchat.h"

VkChat::VkChat(int id, QString token):
    api("***REMOVED***"),
    m_usrHandler("***REMOVED***")
{
    m_id = id;
    m_token = token;
}

VkChat::~VkChat(){
    foreach (VkUser* usr, m_administrators) {
        delete usr;
        usr = nullptr;
    }
    m_administrators.clear();
    delete m_usrOwner;
    m_usrOwner = nullptr;
}

bool VkChat::isValid()
{
    return m_isValid;
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

void VkChat::setId(unsigned int id)
{
    m_id = id;
}
