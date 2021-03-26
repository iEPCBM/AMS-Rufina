#include "messageassembler.h"

MessageAssembler::MessageAssembler(QString message, bool hsymbols, bool pingAll, bool signature)
{
    Settings* settings;
    settings = Settings::getInstance();

    m_strMessage = message;
    m_hasSignature = signature;
    m_hasHeaderSymbols = hsymbols;
    m_hasPingAll = pingAll;

    m_strHeaderSymblos = settings->getHsymbols();
    m_strSignature = settings->getSignature();
    delete settings; //NOTE: minimize memory (I'm hate heap)
    settings = NULL;
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
