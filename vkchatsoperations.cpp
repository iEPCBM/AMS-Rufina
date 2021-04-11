#include "vkchatsoperations.h"

VkChatsOperations::VkChatsOperations()
{

}

QHash<uint8_t, VkChat> *VkChatsOperations::chats() const
{
    return m_chats;
}

void VkChatsOperations::setChats(QHash<uint8_t, VkChat> *chats)
{
    m_chats = chats;
}

void VkChatsOperations::popChat(VkChat chat)
{
    m_chats->remove(getFloorByChat(chat));
}

int16_t VkChatsOperations::getFloorByChat(VkChat chat)
{
    QList<uint8_t> floors = m_chats->keys();
    foreach (uint8_t floor, floors) {
        if ((*m_chats)[floor].getId()==chat.getId()) {
            return floor;
        }
    }
    return -1;
}
