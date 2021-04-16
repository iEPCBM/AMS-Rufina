#ifndef VKMESSAGEDELIVERY_H
#define VKMESSAGEDELIVERY_H

#include <QObject>
#include "vkApi/vkapi.h"
#include "vkApi/vkerror.h"
#include "vkApi/AbstractMethod.h"

class VkMessageDelivery : public QObject, public AbstractMethod
{
    Q_OBJECT
public:
    explicit VkMessageDelivery(QString token, QObject *parent = nullptr);
    ~VkMessageDelivery() {}
    void sendMessage(int peer_id, QString text);
    QJsonDocument getJsonResponse() const;

    bool hasError() const;
    void clear();

signals:
    void messageSent(QJsonDocument);
public slots:
    void onRequestFinished(QJsonDocument json_doc);
private:
    VkApi m_api;
    QJsonDocument m_jsonResponse;
};

#endif // VKMESSAGEDELIVERY_H
