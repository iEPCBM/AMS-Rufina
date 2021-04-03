#ifndef VKUSER_H
#define VKUSER_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVector>
#include "vkApi/vkapi.h"

#define VK_FLD_FIRST_NAME "first_name"
#define VK_FLD_LAST_NAME "last_name"
#define VK_FLD_ID "id"

class VkUser
{
public:
    VkUser(QJsonObject vkApiReponseObj);
    VkUser(uint32_t id, QString name, QString surname);
    VkUser();
    QString name() const;
    QString surname() const;

    uint32_t getId() const;

    void setName(const QString &name);

    void setSurname(const QString &surname);

    void setId(const uint32_t &id);

     QString getAssembledName();
private:
    QString m_name;
    QString m_surname;
    uint32_t m_id;
};

#endif // VKUSER_H
