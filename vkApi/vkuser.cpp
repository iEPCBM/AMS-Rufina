#include "vkuser.h"

VkUser::VkUser(QJsonObject vkApiReponseObj)
{
    m_name = vkApiReponseObj.value(VK_FLD_FIRST_NAME).toString();
    m_surname = vkApiReponseObj.value(VK_FLD_LAST_NAME).toString();
    m_id = vkApiReponseObj.value(VK_FLD_ID).toInt();
}

VkUser::VkUser(uint32_t id, QString name, QString surname)
{
    m_id = id;
    m_name = name;
    m_surname = surname;
}

VkUser::VkUser()
{

}

QString VkUser::name() const
{
    return m_name;
}

QString VkUser::surname() const
{
    return m_surname;
}

uint32_t VkUser::getId() const
{
    return m_id;
}

void VkUser::setName(const QString &name)
{
    m_name = name;
}

void VkUser::setSurname(const QString &surname)
{
    m_surname = surname;
}

void VkUser::setId(const uint32_t &id)
{
    m_id = id;
}

QString VkUser::getAssembledName()
{
    return m_name + " " + m_surname;
}
