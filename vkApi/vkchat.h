#ifndef VKCHAT_H
#define VKCHAT_H

#include <QString>
#include <QHash>
#include <QEventLoop>
#include <QJsonArray>
#include "vkApi/vkapi.h"
#include "vkApi/vkuser.h"
#include "vkApi/vkuserhandler.h"
#include "settings.h"

#define STR_UNKNOWN "UNKNOWN"

class VkChat : public QObject
{
    Q_OBJECT
public:
    explicit VkChat(int id, QString token);
    virtual ~VkChat();

    bool isValid();
    bool getConversationData();

    QString getTitle() const;
    QVector<VkUser*> getAdministrators() const;

    unsigned int getId() const;
    void setId(unsigned int id);
    void responseChatParse();
signals:
    void dataWasGot();

public slots:
    void getConversationFinished(QJsonDocument json_doc);
    void getAdminsFinished(QVector<VkUser*> vec_usrs);
    void getOwnerFinished(QVector<VkUser*> vec_usrs);
private:
    QEventLoop m_loop;
    QJsonDocument m_jsonResp;
    QString m_strTitle;
    QVector<VkUser*> m_administrators;
    VkUser* m_usrOwner;
    unsigned int m_id;
    QString m_token;
    VkApi api;
    VkUserHandler m_usrHandler;
    bool m_isValid;
};

#endif // VKCHAT_H
