#include "vkapi.h"
#include "../mainwindow.h"

VkApi::VkApi(QString token)
{
    m_token = token;
    netMngr = new QNetworkAccessManager(this);
}

VkApi::~VkApi()
{
    delete netMngr;
    netMngr = NULL;
}

void VkApi::sendRequest(QString method, QHash<QString, QString> args)
{
    args["access_token"] = m_token;
    args["v"] = VK_API_VER;
    QString query = assemblyQuery(args);
    QString strUrl = VK_API_ENDPOINT+method+query;

    qDebug() << strUrl;

    netMngr = new QNetworkAccessManager(this);

    connect(netMngr, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    netMngr->get(QNetworkRequest(QUrl(strUrl)));
    m_loop.exec(); //NOTE: Stop main thread
}

QByteArray VkApi::getResponse()
{
    return m_byteArrReply;
}

QJsonDocument VkApi::parseResponse()
{
    m_isError = false;
    QJsonParseError parseError;
    QJsonDocument json_doc = QJsonDocument::fromJson(m_byteArrReply, &parseError);
    QJsonObject json_obj = json_doc.object();
    if (parseError.error != QJsonParseError::NoError || json_obj.contains("error")) {
        m_isError = true;
    }
    return json_doc;
}

int32_t VkApi::getRandomId(QString strMsg, int peerId)
{
    int32_t val = QCryptographicHash::hash(strMsg.toUtf8(), QCryptographicHash::Sha256).at(peerId%256)-peerId/(strMsg.length()*peerId%256);
    qDebug()<<val;
    return val;
}

QJsonDocument VkApi::getJsonResponse() const
{
    return m_jsonResponse;
}

void VkApi::onFinished(QNetworkReply *r)
{
    m_loop.exit();
    m_byteArrReply = r->readAll();
    m_jsonResponse = parseResponse();
    emit requestFinished(m_jsonResponse);
}

QString VkApi::assemblyQuery(QHash<QString, QString> args)
{
    QString strQuery = "?";
    QHashIterator<QString, QString> i(args);
    while (i.hasNext()) {
        i.next();
        strQuery+=i.key()+"="+i.value();
        if (i.hasNext()) {
            strQuery+="&";
        }
    }
    return strQuery;
}

bool VkApi::isError() const
{
    return m_isError;
}
