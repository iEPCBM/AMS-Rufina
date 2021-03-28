#include "vkchathandler.h"

VkChatHandler::VkChatHandler(QObject *parent, uint32_t id, QString token) :
    QObject(parent),
    api("***REMOVED***"),
    m_usrHandler("***REMOVED***"),
    m_chat(id)
{
    m_id = id;
}

bool VkChatHandler::isValid()
{
    return m_isValid;
}

void VkChatHandler::getConversationData()
{
    QHash<QString, QString> query;
    query["peer_ids"]=QString::number(VK_API_MULTICHAT_BASE_ID+m_id);
    //VkApi api(this, "***REMOVED***");
    connect(&api,SIGNAL(requestFinished(QJsonDocument)),this,SLOT(getConversationFinished(QJsonDocument)));
    api.sendRequest("messages.getConversationsById", query);
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
            uint32_t ownerId = objChatSettings.value("owner_id").toInt();
            connect(&m_usrHandler, SIGNAL(requestFinished(QVector<VkUser*>)), this, SLOT(getOwnerFinished(QVector<VkUser*>)));
            m_usrHandler.sendRequest(ownerId);
            qDebug()<<"Owner done";
            disconnect(&m_usrHandler, SIGNAL(requestFinished(QVector<VkUser*>)), this, SLOT(getOwnerFinished(QVector<VkUser*>)));
            QJsonArray adminIds = objChatSettings.value("admin_ids").toArray();
            foreach (const QJsonValue & jsonValId, adminIds) {
                int id = jsonValId.toInt();
                if (id>0) {
                    connect(&m_usrHandler, SIGNAL(requestFinished(QVector<VkUser*>)), this, SLOT(getAdminsFinished(QVector<VkUser*>)));
                    m_usrHandler.sendRequest(id);
                }
            }
            m_isValid = true;
        }
    }
}

void VkChatHandler::getConversationFinished(QJsonDocument json_doc)
{
    qDebug()<<"Finished";
    qDebug()<<json_doc.toJson();
    m_jsonResp = json_doc;
    responseChatParse();
    emit dataWasGot(m_chat);
}

void VkChatHandler::getAdminsFinished(QVector<VkUser *> vec_usrs)
{
    m_chat.setAdministrators(vec_usrs);
    qDebug()<<"==== Admin 0: " + vec_usrs[0]->getAssembledName();
}

void VkChatHandler::getOwnerFinished(QVector<VkUser *> vec_usrs)
{
    qDebug()<<vec_usrs.length();
    m_chat.setOwner(vec_usrs.at(0));
    qDebug()<<"==== Owner: " + vec_usrs.at(0)->getAssembledName();
}
