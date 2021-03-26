#ifndef MESSAGEASSEMBLER_H
#define MESSAGEASSEMBLER_H

#include <QString>
#include "settings.h"

#define QSTR_PING_ALL QString("@all, ")
#define QSTR_ENDL QString("\n")

class MessageAssembler
{
public:
    MessageAssembler(QString message,  bool hsymbols, bool pingAll, bool signature);
    virtual ~MessageAssembler(){};
    QString assembly();
private:
    QString m_strSignature;
    QString m_strHeaderSymblos;

    QString m_strMessage;
    bool m_hasSignature;
    bool m_hasHeaderSymbols;
    bool m_hasPingAll;
};

#endif // MESSAGEASSEMBLER_H
