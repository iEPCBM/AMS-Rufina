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
