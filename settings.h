#ifndef SETTINGS_H
#define SETTINGS_H

#include <QXmlStreamReader>
#include <QFile>

#include "floor.h"
#include <QVector>

#define CONFIG_WRAPPER_TAG "config"
#define SEQURE_WRAPPER_TAG "secure"
#define CHATS_WRAPPER_TAG "chats"

#define HIGHTLIGHT_SYMBOLS_TAG "hsymbols"
#define SIGNATURE_TAG "signature"

#define ENCRY_TAG "encrypted"
#define HASH_TAG "hash"
#define VK_TOKEN_TAG "vktoken"

#define CHAT_TAG "chat"

#define VALUE_ATTR "value"
#define NAME_ATTR "name"
#define ID_ATTR "id"
#define HASH_SIGNATURE_ATTR "hashSig"

class Settings
{
public:
    Settings(QString strPath);
    void exportConf(QString strPath);
    void importConf(QString strPath);
    void save();

    void extract();
    void update();

    static Settings* getInstance();

    QString getHsymbols() const;
    void setHsymbols(const QString &hsymbols);

    QString getSignature() const;
    void setSignature(const QString &signature);

    bool isEncrypted() const;
    void setEncrypted(bool isEncrypted);

    QString getTokenSignature() const;
    void setTokenSignature(const QString &tokenSignature);

    QString getVkToken() const;
    void setVkToken(const QString &vkToken);

private:
    QString m_strPath;
    QXmlStreamReader m_xmlStream;
    QString m_hsymbols;
    QString m_signature;

    QString m_tokenSignature;
    QString m_vkToken;
    bool m_isEncrypted;
    QVector<Floor> m_floors;
};

#endif // SETTINGS_H
