#include "messageassembler.h"

MessageAssembler::MessageAssembler(Settings *settings, QString message, bool hsymbols, bool pingAll, bool signature)
{
    m_strMessage = message;
    m_hasSignature = signature;
    m_hasHeaderSymbols = hsymbols;
    m_hasPingAll = pingAll;

    m_strHeaderSymblos = settings->getHsymbols();
    m_strSignature = settings->getSignature();
}

QString MessageAssembler::assembly()
{
    QString strMsg = "";
    if (m_hasHeaderSymbols) {
        strMsg += m_strHeaderSymblos + QSTR_ENDL;
    }
    if (m_hasPingAll) {
        strMsg += QSTR_PING_ALL;
    }
    strMsg += m_strMessage.trimmed();
    if (m_hasSignature) {
        strMsg += QSTR_ENDL + m_strSignature;
    }
    return strMsg.trimmed();
}
