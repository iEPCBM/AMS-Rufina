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

#include "vkerror.h"

VkError::VkError(int16_t code, QString description)
{
    m_code = code;
    m_description = description;
    fillErrorMsgList();
}

VkError::VkError()
{
    clear();
    fillErrorMsgList();
}

int16_t VkError::code() const
{
    return m_code;
}

void VkError::setCode(const int16_t &code)
{
    m_code = code;
}

QString VkError::description() const
{
    return m_description + (m_errorMsgList.contains(m_code)?(" ("+m_errorMsgList[m_code].trimmed()+")."):"");
}

void VkError::setDescription(const QString &description)
{
    m_description = description;
}

bool VkError::hasError()
{
    return !((m_code==0)&m_description.isEmpty());
}

void VkError::clear()
{
    m_code = 0;
    m_description = "";
}

void VkError::fillErrorMsgList()
{
    QFile fileList(FILEPATH_VKAPI_ERR_LIST);
    if (!fileList.open(QFile::ReadOnly)) {
        ErrorMessages::errorFileAccess(nullptr, fileList.fileName());
        return;
    }
    while (!fileList.atEnd())
    {
       QString line = QString::fromUtf8(fileList.readLine());
       QStringList errNote = line.split("~");
       bool isOk = true;
       uint16_t code = errNote[0].toInt(&isOk);
       if (isOk) {
           m_errorMsgList[code] = errNote[1];
       }
    }

    fileList.close();
}
