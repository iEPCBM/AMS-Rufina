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
    Floor(uint8_t floorNum, int chat_id, QString strChatTitle);
    Floor(uint8_t floorNum);
    QByteArray getHashSum();

private:
    uint8_t m_floorNum;

};
#endif // FLOOR_H
