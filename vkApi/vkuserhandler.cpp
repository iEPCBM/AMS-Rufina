#include "vkApi/vkchathandler.h"

VkUserHandler::VkUserHandler(QObject *parent, QString token)
    : QObject(parent),
      m_api(token)
{
    m_token = token;
}

void VkUserHandler::clear()
{
    m_vecUsers.clear();
}

void VkUserHandler::sendRequest(uint32_t id)
{
    QHash<QString, QString> query;
    query["user_ids"]=QString::number(id);
    connect(&m_api,SIGNAL(requestFinished(QJsonDocument)),this,SLOT(onRequestFinished(QJsonDocument)));
    m_api.sendRequest("users.get", query);
    QJsonArray arrResp = m_api.getJsonResponse().object().value("response").toArray();
    foreach(const QJsonValue &val, arrResp) {
        QJsonObject obj = val.toObject();
        qDebug()<<val.isObject();
        m_vecUsers.push_back(VkUser(obj));
    }
    qDebug()<<m_vecUsers.length();
}

void VkUserHandler::sendRequest(QList<uint32_t> ids)
{
    //Parsing
    QHash<QString, QString> query;
    QString strIds = "";
    auto i=0;
    foreach (const uint32_t id, ids) {
        if (id>0) {
            strIds += QString::number(id);
             if (++i < ids.length()) {
                strIds +=",";
            }
        }
    }
    query["user_ids"]=strIds;
    connect(&m_api,SIGNAL(requestFinished(QJsonDocument)),this,SLOT(onRequestFinished(QJsonDocument)));

    m_api.sendRequest("users.get", query);
    qDebug()<<m_api.getResponse();
    QJsonArray arrResp = m_api.getJsonResponse().object().value("response").toArray();
    foreach(const QJsonValue &val, arrResp) {
        QJsonObject obj = val.toObject();
        qDebug()<<val.isObject();
        m_vecUsers.push_back(VkUser(obj));
    }
}

void VkUserHandler::onRequestFinished(QJsonDocument json_doc)
{
    //emit requestFinished(vecUsers);
    qDebug()<<"Users request done!";
}

QList<VkUser> VkUserHandler::getUsers() const
{
    return m_vecUsers;
}
