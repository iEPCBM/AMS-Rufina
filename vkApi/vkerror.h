#ifndef VKERROR_H
#define VKERROR_H

#include <QString>

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

private:
    int16_t m_code;
    QString m_description;
};

#endif // VKERROR_H
