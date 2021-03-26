#ifndef VKCHAT_H
#define VKCHAT_H

#include <QString>
#include <QHash>
#include <QEventLoop>
#include <QJsonArray>
#include "vkApi/vkapi.h"
#include "settings.h"

#define STR_UNKNOWN "UNKNOWN"

class VkChat : public QObject
{
    Q_OBJECT
public:
    VkChat(int id, QString token);
    virtual ~VkChat(){};

    bool isValid();
    bool getConversationData();

    QString getTitle() const;
    QHash<int, QString> getAdministrators() const;

    unsigned int getId() const;
    void setId(unsigned int id);
    void responseChatParse();
signals:
    void dataWasGot(QJsonDocument json_doc);

public slots:
    void VkApiRequestFinished(QJsonDocument json_doc);

private:
    QEventLoop m_loop;
    QJsonDocument m_jsonResp;
    QString m_strTitle;
    QHash<int, QString> m_administrators;
    QString m_strOwner;
    unsigned int m_id;
    QString m_token;
    VkApi api;
};

#endif // VKCHAT_H
