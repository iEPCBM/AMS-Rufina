#include "aesfacade.h"

AESFacade::AESFacade(QByteArray arrData)
{
    m_aes = new AES(AES_KEY_LEN);
    m_arrSourceData = arrData;
}

bool AESFacade::decryption(QString strPassword)
{
    QByteArray hash = QCryptographicHash::hash(strPassword.toUtf8(), QCryptographicHash::Sha256);
    QByteArray iv = getIV();
    uchar* decryptedData = m_aes->DecryptCBC(
                (uchar*)m_arrSourceData.data(),
                m_arrSourceData.length(),
                (uchar*)hash.data(), (uchar*)iv.data());
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
    qDebug()<<hashOfData;
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
    QByteArray iv = getIV();
    uint32_t outLen = 0;
    uchar* encryptedData = m_aes->EncryptCBC(
                (uchar*)dataToEncry.data(),
                dataToEncry.length(),
                (uchar*)key.data(),
                (uchar*)iv.data(),
                outLen);
    QByteArray data = QByteArray((char*)encryptedData, outLen);

    return data;
}

QByteArray AESFacade::getIV()
{
    QByteArray retVal;
    for (auto i=0; i<AES_KEY_LEN/8; i++) retVal.push_back(IV_MEM);
    return retVal;
}

QByteArray AESFacade::getDecryptedData() const
{
    return m_arrDecryData;
}

QString AESFacade::getStrErr() const
{
    return m_strErr;
}

void AESFacade::clear()
{
    //TODO: clear algorythm
}
