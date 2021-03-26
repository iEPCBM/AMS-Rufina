#include "vkchat.h"

VkChat::VkChat(int id, QString token):
    api(this, "***REMOVED***")
{
    m_id = id;
    m_token = token;
}

bool VkChat::getConversationData()
{
    QHash<QString, QString> query;
    query["peer_ids"]=QString::number(VK_API_MULTICHAT_BASE_ID+m_id);
    //VkApi api(this, "***REMOVED***");
    connect(&api,SIGNAL(requestFinished(QJsonDocument)),this,SLOT(VkApiRequestFinished(QJsonDocument)));
    api.sendRequest("messages.getConversationsById", query);
    return true;
}

QString VkChat::getTitle() const
{
    return m_strTitle;
}

QHash<int, QString> VkChat::getAdministrators() const
{
    return m_administrators;
}

unsigned int VkChat::getId() const
{
    return m_id;
}

void VkChat::setId(unsigned int id)
{
    m_id = id;
}

void VkChat::responseChatParse()
{
    QJsonObject json_obj = m_jsonResp.object();
    m_strTitle = STR_UNKNOWN;
    m_administrators[0] = STR_UNKNOWN;
    if (json_obj.value("count").toInt()==1) {
        QJsonObject item = json_obj.value("items").toArray()[0].toObject();
        if (item.value("peer").toObject().value("type").toString()=="chat") {
            QJsonObject chatSettings = item.value("chat_settings").toObject();
            m_strTitle = chatSettings.value("title").toString(STR_UNKNOWN);

        }
    }
}

void VkChat::VkApiRequestFinished(QJsonDocument json_doc)
{
    qDebug()<<"Finished";
    qDebug()<<json_doc.toJson();
    m_jsonResp = json_doc;
    emit dataWasGot(json_doc);
}

