#ifndef ABSTRACTMETHOD_H
#define ABSTRACTMETHOD_H

#include "vkApi/vkerror.h"

class AbstractMethod {
protected:
    bool m_hasError;
    VkError m_vkError;
public:
    VkError getVkError() const;
    bool hasError() const;
};

inline bool AbstractMethod::hasError() const
{
    return m_hasError;
}

inline VkError AbstractMethod::getVkError() const
{
    return m_vkError;
}

#endif // ABSTRACTMETHOD_H
