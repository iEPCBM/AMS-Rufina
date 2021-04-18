#include "vkApi/vkchathandler.h"

VkUserHandler::VkUserHandler(QObject *parent, QString token)
    : QObject(parent),
      m_api(token)
{
    m_token = token;
}

void VkUserHandler::clear()
{
    if (!m_vecUsers.isEmpty()) {
        m_vecUsers.clear();
    }
}

void VkUserHandler::sendRequest(uint32_t id)
{
    QHash<QString, QString> query;
    query["user_ids"]=QString::number(id);
    m_api.sendRequest("users.get", query);
    if (m_api.isError()) {
        m_vkError = m_api.getVkError();
        m_hasError = true;
    }
    QJsonArray arrResp = m_api.getJsonResponse().object().value("response").toArray();
    foreach(const QJsonValue &val, arrResp) {
        QJsonObject obj = val.toObject();
        m_vecUsers.push_back(VkUser(obj));
    }
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

    m_api.sendRequest("users.get", query);
    QJsonArray arrResp = m_api.getJsonResponse().object().value("response").toArray();
    foreach(const QJsonValue &val, arrResp) {
        QJsonObject obj = val.toObject();
        m_vecUsers.push_back(VkUser(obj));
    }
}

QList<VkUser> VkUserHandler::getUsers() const
{
    return m_vecUsers;
}
