#ifndef VKERROR_H
#define VKERROR_H

#include <QString>
#include <QHash>
#include <QFile>
#include "rassert.h"
#include <QTextStream>

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
