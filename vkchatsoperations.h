#ifndef VKCHATSOPERATIONS_H
#define VKCHATSOPERATIONS_H

#include "vkApi/vkchat.h"

class VkChatsOperations
{
public:
    VkChatsOperations(QHash<uint8_t, VkChat> *chats);

    QHash<uint8_t, VkChat> *chats() const;
    void setChats(QHash<uint8_t, VkChat> *chats);

    void popChat(VkChat chat);
    bool containsChat(VkChat chat);
    bool containsChat(uint chatId);
    bool hasFloorConflict(uint8_t floor);
    uint8_t getFloorByChat (VkChat chat);

private:
    QHash<uint8_t, VkChat> *m_chats;
};

#endif // VKCHATSOPERATIONS_H
