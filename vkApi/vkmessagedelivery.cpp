#include "vkmessagedelivery.h"

VkMessageDelivery::VkMessageDelivery(QString token, QObject *parent) : QObject(parent),
    m_api(token)
{
    clear();
}

void VkMessageDelivery::sendMessage(int peer_id, QString text)
{
    clear();
    QHash<QString, QString> query;
    query["random_id"]=QString::number(VkApi::getRandomId(text, peer_id));
    query["peer_id"]=QString::number(peer_id);
    query["message"]=QUrl::toPercentEncoding(text);
    connect(&m_api, SIGNAL(requestFinished(QJsonDocument)), this, SLOT(onRequestFinished(QJsonDocument)));
    m_api.sendRequest("messages.send", query);
    m_jsonResponse = m_api.getJsonResponse();
    if (m_api.isError()) {
        m_vkError = m_api.getVkError();
        m_hasError = true;
    }
}

void VkMessageDelivery::onRequestFinished(QJsonDocument json_doc)
{
    emit messageSent(json_doc);
}

bool VkMessageDelivery::hasError() const
{
    return m_hasError;
}

void VkMessageDelivery::clear()
{
    m_vkError.clear();
    m_hasError = false;
}

QJsonDocument VkMessageDelivery::getJsonResponse() const
{
    return m_jsonResponse;
}
