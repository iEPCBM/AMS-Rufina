#include "floor.h"

Floor::Floor(int chat_id, int floorNum, QString strChatTitle)
{
    m_vkChatID = checkChatID(chat_id)? chat_id:PSEUDO_ID;
    m_floorNum = floorNum;
    strChatTitle = m_strChatTitle;
}

inline bool Floor::checkChatID(int ID)
{
    if (ID>=0 && ID<100000000) return true;
    return false;
}

QByteArray Floor::getHashSum()
{
    QByteArray data2hash, hash;
    data2hash=QString(
                m_strChatTitle+STATEMENT_SEPARATOR+
                QString::number(m_vkChatID)+STATEMENT_SEPARATOR+
                QString::number(m_floorNum)+STATEMENT_SEPARATOR+
                CONFIRMATION_HASH_SALT).toUtf8();
    hash = QCryptographicHash::hash(data2hash, QCryptographicHash::Md5);
    return hash;
}

int Floor::vkChatID() const
{
    return m_vkChatID;
}
