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

#ifndef MESSAGEASSEMBLER_H
#define MESSAGEASSEMBLER_H

#include <QString>
#include "settings.h"

#define QSTR_PING_ALL QString("@all, ")
#define QSTR_ENDL QString("\n")

class MessageAssembler
{
public:
    MessageAssembler(Settings *settings, QString message,  bool hsymbols, bool pingAll, bool signature);
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
