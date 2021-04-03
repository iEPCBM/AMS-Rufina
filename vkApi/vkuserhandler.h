#ifndef VKUSERHANDLER_H
#define VKUSERHANDLER_H

#include <QString>
#include <QObject>
#include "vkApi/vkuser.h"

class VkUserHandler : public QObject
{
    Q_OBJECT
public:  
    explicit VkUserHandler(QObject *parent=nullptr, QString token="");

public:
    void clear();

    void sendRequest(uint32_t id);
    void sendRequest(QList<uint32_t>id);

    QList<VkUser> getUsers() const;

public slots:
    void onRequestFinished(QJsonDocument json_doc);

signals:
    void requestFinished(QVector<VkUser*>);

private:
    QString m_token;
    VkApi m_api;
    QList<VkUser> m_vecUsers;
};

#endif // VKUSERHANDLER_H
