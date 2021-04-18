#ifndef VKCHATHANDLER_H
#define VKCHATHANDLER_H

#include <QString>
#include <QHash>
#include <QEventLoop>
#include <QJsonArray>
#include "vkApi/vkapi.h"
#include "vkApi/vkuser.h"
#include "vkApi/vkuserhandler.h"
#include "settings.h"
#include "vkApi/vkchat.h"
#include "vkApi/AbstractMethod.h"
#include <QObject>

class VkChatHandler : public QObject, public AbstractMethod
{
    Q_OBJECT
public:
    explicit VkChatHandler(QObject *parent = nullptr, QString token="");
    ~VkChatHandler() {}
    void clear();
    bool isValid();
    void getConversationData(uint32_t id);

    unsigned int getId() const;
    void setId(unsigned int id);
    void responseChatParse();
    VkChat getChat() const;

signals:
    void dataWasGot(VkChat);

private:
    QJsonDocument m_jsonResp;
    QString m_token;
    VkApi api;
    VkChat m_chat;
    bool m_isValid;
};

#endif // VKCHATHANDLER_H
