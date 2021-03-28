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

#define STR_UNKNOWN "UNKNOWN"

class VkChat
{
public:
    VkChat(int id, QString title, QVector<VkUser> administrators, VkUser owner);
    VkChat(int id);
    VkChat();
    ~VkChat();

    QString getTitle() const;
    QVector<VkUser*> getAdministrators() const;

    unsigned int getId() const;

    VkUser *getOwner() const;

    void setTitle(const QString &strTitle);

    void setAdministrators(const QVector<VkUser*> &administrators);

    void setOwner(const VkUser *usrOwner);

private:
    QString m_strTitle;
    QVector<VkUser*> m_administrators;
    VkUser *m_usrOwner;
    unsigned int m_id;
};

#endif // VKCHAT_H
