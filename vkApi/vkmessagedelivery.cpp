#include "vkmessagedelivery.h"

VkMessageDelivery::VkMessageDelivery(QString token, QObject *parent) : QObject(parent),
    m_api(token)
{

}

void VkMessageDelivery::sendMessage(int peer_id, QString text)
{
    QHash<QString, QString> query;
    query["random_id"]=QString::number(VkApi::getRandomId(text, peer_id));
    query["peer_id"]=QString::number(peer_id);
    query["message"]=text;
    connect(&m_api, SIGNAL(requestFinished(QJsonDocument)), this, SLOT(onRequestFinished(QJsonDocument)));
    m_api.sendRequest("messages.send", query);
}

void VkMessageDelivery::onRequestFinished(QJsonDocument json_doc)
{
    emit messageSent(json_doc);
}
