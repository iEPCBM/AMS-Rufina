/*
 *  AMS Rufina - automated message delivery program
 *  Copyright (C) 2021 Rishat D. Kagirov (iEPCBM)
 *
 *     This file is part of AMS Rufina.
 *
 *  AMS Rufina is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Foobar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

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
