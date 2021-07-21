#ifndef AESFACADE_H
#define AESFACADE_H

#include "third_party/AES/AES.h"
#include "rassert.h"
#include <QString>
#include <QByteArray>
#include <QCryptographicHash>
#include <QList>
#include <QByteArray>
#include <QTime>
#include <QDate>

#define AES_KEY_LEN 0x100

#define DATA_SEPARATOR '$'
#define CRYPTOGRAPHIC_SALT "Alina"

#define INDEX_DATA 0
#define INDEX_HASH 1

#define STR_ERR_IVALID_PASSWORD QString("Invalid password (Line: ") + QString::number(__LINE__) + "; File: " + __FILE__ + ")."

class AESFacade
{
public:
    explicit AESFacade(QByteArray arrData);
    explicit AESFacade(QByteArray arrData, QByteArray iv);

    bool decryption(QString strPassword);
    QByteArray encryption(QString strPassword);

    QByteArray getDecryptedData() const;

    QByteArray getCheckHash() const;

    QString getStrErr() const;

    void clear();

    QByteArray getIV() const;

private:
    QByteArray generateIV();
    AES *m_aes;
    QByteArray m_IV;

    QByteArray m_arrSourceData;

    QByteArray m_arrDecryData;
    QByteArray m_arrCheckHash;

    QString m_strErr;
};

#endif // AESFACADE_H
