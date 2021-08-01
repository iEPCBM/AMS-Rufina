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

#ifndef VKERROR_H
#define VKERROR_H

#include <QString>
#include <QHash>
#include <QFile>
#include "rassert.h"
#include "filepaths.h"

class VkError
{
public:
    VkError(int16_t code, QString description);
    VkError();

    int16_t code() const;
    void setCode(const int16_t &code);

    QString description() const;
    void setDescription(const QString &description);

    bool hasError();
    void clear();

private:
    int16_t m_code;
    QString m_description;
    QHash<uint16_t, QString> m_errorMsgList;
    void fillErrorMsgList();
};

#endif // VKERROR_H
