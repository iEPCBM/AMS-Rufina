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
