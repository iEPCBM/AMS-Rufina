#ifndef FLOOR_H
#define FLOOR_H

#include <QString>
#include <QCryptographicHash>
#include <QMessageBox>

#define PSEUDO_ID -1
#define CONFIRMATION_HASH_SALT "PROSTI, RUFINA"
#define STATEMENT_SEPARATOR "_&#_VERA_#&_"

class Floor
{
public:
    Floor(int chat_id, int floorNum, QString strChatTitle);

    int vkChatID() const;
    QByteArray getHashSum();

private:
    inline bool checkChatID (int ID);

    int m_vkChatID;
    unsigned char m_floorNum;
    QString m_strChatTitle;
    QString m_hashSignature;
};

#endif // FLOOR_H
