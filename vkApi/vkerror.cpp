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
    return m_description + (m_errorMsgList.contains(m_code)?(" ("+m_errorMsgList[m_code].trimmed()+")"):"");
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
    QFile fileList("D:\\Projects\\Programs\\CPP\\QT\\VK_ChatsMessageDelivery\\RUFINA\\RUFINA\\assets\\errlist.cfg");
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
