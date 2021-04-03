#include "vkchathandler.h"

VkChatHandler::VkChatHandler(QObject *parent, QString token) :
    QObject(parent),
    api("***REMOVED***")
{
}

void VkChatHandler::clear()
{
    m_chat = VkChat();
    m_isValid = true;
    m_jsonResp = QJsonDocument();
}

bool VkChatHandler::isValid()
{
    return m_isValid;
}

void VkChatHandler::getConversationData(uint32_t id)
{
    m_chat.setId(id);
    QHash<QString, QString> query;
    query["peer_ids"]=QString::number(VK_API_MULTICHAT_BASE_ID+id);
    connect(&api,SIGNAL(requestFinished(QJsonDocument)),this,SLOT(getConversationFinished(QJsonDocument)));
    api.sendRequest("messages.getConversationsById", query);
    qDebug()<<api.getJsonResponse().toJson();
    m_jsonResp = api.getJsonResponse();
    responseChatParse();
}

void VkChatHandler::responseChatParse()
{
    QJsonObject json_obj = m_jsonResp.object();
    if (api.isError()) {
        m_isValid = false;
        return;
    }
    QJsonObject responseObj = json_obj.value("response").toObject();
    m_chat.setTitle(STR_UNKNOWN);
    //m_administrators[0] = STR_UNKNOWN;
    if (responseObj.value("count").toInt()==1) {
        QJsonObject item = responseObj.value("items").toArray()[0].toObject();
        if (item.value("peer").toObject().value("type").toString()=="chat") {
            QJsonObject objChatSettings = item.value("chat_settings").toObject();
            m_chat.setTitle(objChatSettings.value("title").toString(STR_UNKNOWN));
            m_chat.setOwnerId(objChatSettings.value("owner_id").toInt());
            QJsonArray adminIds = objChatSettings.value("admin_ids").toArray();
            QList<int> adms;
            foreach (const QJsonValue& val, adminIds) {
                adms.append(val.toInt());
            }
            m_chat.setAdministratorsIds(adms);
            m_isValid = true;
        }
    }
}

void VkChatHandler::getConversationFinished(QJsonDocument json_doc)
{
    qDebug()<<"Finished";
}

VkChat VkChatHandler::getChat() const
{
    return m_chat;
}
