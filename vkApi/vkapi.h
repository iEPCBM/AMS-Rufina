#ifndef VKAPI_H
#define VKAPI_H

#include <QString>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHash>
#include <QHashIterator>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTextCodec>
#include <QEventLoop>

#define VK_API_VER "5.130"
#define VK_API_ENDPOINT "https://api.vk.com/method/"
#define VK_API_MULTICHAT_BASE_ID 2000000000

class VkApi : public QObject
{
    Q_OBJECT
public:
    explicit VkApi(QString token);
    ~VkApi();
    void sendRequest(QString method, QHash<QString, QString> args);
    QByteArray getResponse();

    static int32_t getRandomId(QString strMsg, int peerId);
    QJsonDocument getJsonResponse() const;
    bool isError() const;

signals:
    void requestFinished(QJsonDocument json_doc);

public slots:
    void onFinished(QNetworkReply *r);

private:
    QJsonDocument parseResponse();
    QEventLoop m_loop;

    QByteArray m_byteArrReply;
    QString m_token;
    QObject* m_parent;
    QString assemblyQuery (QHash<QString, QString> args);
    QNetworkAccessManager *netMngr;
    QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> netReply;
    bool m_isError = false;
    QJsonDocument m_jsonResponse;
};

#endif // VKAPI_H
