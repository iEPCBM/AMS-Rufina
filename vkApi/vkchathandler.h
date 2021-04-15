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
#include "vkApi/vkerror.h"
#include <QObject>

class VkChatHandler : public QObject
{
    Q_OBJECT
public:
    explicit VkChatHandler(QObject *parent = nullptr, QString token="");

    void clear();
    bool isValid();
    bool hasError();
    void getConversationData(uint32_t id);

    unsigned int getId() const;
    void setId(unsigned int id);
    void responseChatParse();
    VkChat getChat() const;

    VkError getVkError() const;

signals:
    void dataWasGot(VkChat);

public slots:
    void getConversationFinished(QJsonDocument json_doc);

private:
    QJsonDocument m_jsonResp;
    QString m_token;
    VkApi api;
    VkChat m_chat;
    bool m_isValid;
    bool m_hasError;
    VkError m_vkError;
};

#endif // VKCHATHANDLER_H
