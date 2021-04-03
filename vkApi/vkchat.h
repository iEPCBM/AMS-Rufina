#ifndef VKCHAT_H
#define VKCHAT_H

#include <QString>
#include <QHash>
#include <QEventLoop>
#include <QJsonArray>
#include "vkApi/vkapi.h"
#include "vkApi/vkuser.h"
#include "vkApi/vkuserhandler.h"
#include "settings.h"

#define STR_UNKNOWN "_н/д_"

class VkChat
{
public:
    VkChat(int id, QString title, QVector<VkUser> administrators, VkUser owner);
    VkChat(int id);
    VkChat();
    ~VkChat();

    QString getTitle() const;

    unsigned int getId() const;

    void setTitle(const QString &strTitle);

    void setId(unsigned int id);

    QList<int> getAdministratorsIds() const;
    void setAdministratorsIds(const QList<int> &administratorsIds);

    int getOwnerId() const;
    void setOwnerId(const int &ownerId);

    bool hasOwner();
    bool hasAdmins();

private:
    QString m_strTitle;
    QList<int> m_administratorsIds;
    int m_ownerId=0;
    unsigned int m_id;
};

#endif // VKCHAT_H
