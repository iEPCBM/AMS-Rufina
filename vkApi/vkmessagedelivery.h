#ifndef VKMESSAGEDELIVERY_H
#define VKMESSAGEDELIVERY_H

#include <QObject>
#include "vkApi/vkapi.h"

class VkMessageDelivery : public QObject
{
    Q_OBJECT
public:
    explicit VkMessageDelivery(QString token, QObject *parent = nullptr);
    void sendMessage(int peer_id, QString text);
signals:
    void messageSent(QJsonDocument);
public slots:
    void onRequestFinished(QJsonDocument json_doc);
private:
    VkApi m_api;
};

#endif // VKMESSAGEDELIVERY_H
