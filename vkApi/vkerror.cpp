#include "vkerror.h"

VkError::VkError(int16_t code, QString description)
{
    m_code = code;
    m_description = description;
}

VkError::VkError()
{
    m_code = 0;
    m_description = "";
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
    return m_description;
}

void VkError::setDescription(const QString &description)
{
    m_description = description;
}

bool VkError::hasError()
{
    return !((m_code==0)&m_description.isEmpty());
}
