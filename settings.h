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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QXmlStreamReader>
#include <QFile>
#include "vkApi/vkchat.h"
#include "rassert.h"
#include "filepaths.h"

#define CONFIG_WRAPPER_TAG "config"
#define SEQURE_WRAPPER_TAG "secure"
#define CHATS_WRAPPER_TAG "chats"

#define HIGHTLIGHT_SYMBOLS_TAG "hsymbols"
#define SIGNATURE_TAG "signature"

#define ENCRY_TAG "encrypted"
#define HASH_TAG "hash"
#define VK_TOKEN_TAG "vktoken"

#define CHAT_TAG "chat"

#define VALUE_ATTR "value"
#define IV_ATTR "iv"
#define NAME_ATTR "name"
#define ID_ATTR "id"
#define FLOOR_ATTR "floor"

class Settings
{
public:
    Settings(QString strPath);
    void exportConf(QString strPath);
    void importConf(QString strPath);
    void save();

    void extract();

    static Settings* getInstance();

    QString getHsymbols() const;
    void setHsymbols(const QString &hsymbols);

    QString getSignature() const;
    void setSignature(const QString &signature);

    bool isEncrypted() const;
    void setEncrypted(bool isEncrypted);

    QString getTokenSignature() const;
    void setTokenSignature(const QString &tokenSignature);

    QString getVkToken() const;
    void setVkToken(const QString &vkToken);

    QHash<uint8_t, VkChat> getChats() const;
    void setChats(const QHash<uint8_t, VkChat> &chats);

    QString getInitializeVector() const;
    void setInitializeVector(const QString &initializeVector);

private:
    QString m_strPath;
    QString m_hsymbols;
    QString m_signature;

    bool writeConf(QFile *file);
    bool readConf(QFile *file);

    QString m_tokenSignature;
    QString m_vkToken;
    QString m_initializeVector;
    bool m_isEncrypted;
    QHash<uint8_t, VkChat> m_chats; // n floor - Chat table
};

#endif // SETTINGS_H
