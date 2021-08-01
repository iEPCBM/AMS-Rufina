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

#include "aesfacade.h"

AESFacade::AESFacade(QByteArray arrData)
{
    m_aes = new AES(AES_KEY_LEN);
    m_arrSourceData = arrData;
}

AESFacade::AESFacade(QByteArray arrData, QByteArray iv)
{
    m_aes = new AES(AES_KEY_LEN);
    m_IV = iv;
    m_arrSourceData = arrData;
}

bool AESFacade::decryption(QString strPassword)
{
    R_ASSERT((m_IV.length()==0x20), return false, nullptr);

    QByteArray hash = QCryptographicHash::hash(strPassword.toUtf8(), QCryptographicHash::Sha256);
    uchar* decryptedData = m_aes->DecryptCBC(
                (uchar*)m_arrSourceData.data(),
                m_arrSourceData.length(),
                (uchar*)hash.data(), (uchar*)m_IV.data());
    QByteArray data = QByteArray((char*)decryptedData, m_arrSourceData.length());

    //stage 1
    if (!data.contains(DATA_SEPARATOR)) {
        m_strErr = STR_ERR_IVALID_PASSWORD;
        return false;
    }
    data.chop(data.count((char)0x00));
    QList<QByteArray> listData = data.split(DATA_SEPARATOR);
    m_arrDecryData = listData[INDEX_DATA];
    m_arrCheckHash = listData[INDEX_HASH];
    //stage 2
    QByteArray hashOfData = QCryptographicHash::hash(
                m_arrDecryData, QCryptographicHash::Sha256).toHex();
    if (m_arrCheckHash != hashOfData) {
        m_strErr = STR_ERR_IVALID_PASSWORD;
        return false;
    }
    return true;
}

QByteArray AESFacade::encryption(QString strPassword)
{
    QByteArray key = QCryptographicHash::hash(
                strPassword.toUtf8(),
                QCryptographicHash::Sha256);

    QByteArray hashData = QCryptographicHash::hash(
                m_arrSourceData,
                QCryptographicHash::Sha256).toHex();
    QByteArray dataToEncry = m_arrSourceData + DATA_SEPARATOR + hashData;
    m_IV = generateIV();
    uint32_t outLen = 0;
    uchar* encryptedData = m_aes->EncryptCBC(
                (uchar*)dataToEncry.data(),
                dataToEncry.length(),
                (uchar*)key.data(),
                (uchar*)m_IV.data(),
                outLen);
    QByteArray data = QByteArray((char*)encryptedData, outLen);

    return data;
}

QByteArray AESFacade::generateIV()
{
    QString data = QDate::currentDate().toString(Qt::ISODate)+DATA_SEPARATOR
                    +QTime::currentTime().toString(Qt::ISODateWithMs);
    QByteArray retVal =  QCryptographicHash::hash(
                data.toUtf8(),
                QCryptographicHash::Sha256);
    return retVal;
}

QByteArray AESFacade::getIV() const
{
    return m_IV;
}

QByteArray AESFacade::getDecryptedData() const
{
    return m_arrDecryData;
}

QString AESFacade::getStrErr() const
{
    return m_strErr;
}
