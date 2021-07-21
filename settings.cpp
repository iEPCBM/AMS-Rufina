#include "settings.h"

Settings::Settings(QString strPath)
{
    m_strPath = strPath;
}

void Settings::exportConf(QString strPath)
{
    QFile *file = new QFile(strPath);
    if (!file->open(QIODevice::WriteOnly)) {
        ErrorMessages::errorFileAccess(nullptr, strPath);
        return;
    }
    writeConf(file);
    file->close();
}

void Settings::importConf(QString strPath)
{
    QFile *file = new QFile(strPath);
    if (!file->open(QIODevice::ReadOnly)) {
        ErrorMessages::errorFileAccess(nullptr, strPath);
        return;
    }
    readConf(file);
    file->close();
}

void Settings::save()
{
    exportConf(m_strPath);
}

void Settings::extract()
{
    importConf(m_strPath);
}

Settings* Settings::getInstance()
{
    Settings* ptr_stg = new Settings(FILEPATH_CONFIGS);
    ptr_stg->extract();
    return ptr_stg;
}

QString Settings::getHsymbols() const
{
    return m_hsymbols;
}

void Settings::setHsymbols(const QString &hsymbols)
{
    m_hsymbols = hsymbols;
}

QString Settings::getSignature() const
{
    return m_signature;
}

void Settings::setSignature(const QString &signature)
{
    m_signature = signature;
}

bool Settings::isEncrypted() const
{
    return m_isEncrypted;
}

void Settings::setEncrypted(bool isEncrypted)
{
    m_isEncrypted = isEncrypted;
}

QString Settings::getTokenSignature() const
{
    return m_tokenSignature;
}

void Settings::setTokenSignature(const QString &tokenSignature)
{
    m_tokenSignature = tokenSignature;
}

QString Settings::getVkToken() const
{
    return m_vkToken;
}

void Settings::setVkToken(const QString &vkToken)
{
    m_vkToken = vkToken;
}

bool Settings::writeConf(QFile *file)
{
    QXmlStreamWriter xml(file);
    if (xml.hasError()) {
         ErrorMessages::errorFileAccess(nullptr, file->fileName());
        return false;
    }
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement(CONFIG_WRAPPER_TAG);
        xml.writeStartElement(HIGHTLIGHT_SYMBOLS_TAG);
        xml.writeAttribute(VALUE_ATTR, m_hsymbols);
        xml.writeEndElement(); // HIGHTLIGHT_SYMBOLS_TAG

        xml.writeStartElement(SIGNATURE_TAG);
        xml.writeAttribute(VALUE_ATTR, m_signature);
        xml.writeEndElement(); // SIGNATURE_TAG

        xml.writeStartElement(SEQURE_WRAPPER_TAG);
            xml.writeStartElement(ENCRY_TAG);
            xml.writeAttribute(VALUE_ATTR, QString::number(m_isEncrypted?1:0));
            xml.writeEndElement(); // ENCRY_TAG

            xml.writeStartElement(VK_TOKEN_TAG);
            if (m_isEncrypted) xml.writeAttribute(IV_ATTR, m_initializeVector);
            xml.writeAttribute(VALUE_ATTR, m_vkToken);
            xml.writeEndElement(); // VK_TOKEN_TAG

            xml.writeStartElement(CHATS_WRAPPER_TAG);
                QList<uint8_t> aviable_floors = m_chats.keys();
                foreach (uint8_t floor, aviable_floors) {
                    xml.writeStartElement(CHAT_TAG);
                    xml.writeAttribute(NAME_ATTR, m_chats[floor].getTitle());
                    xml.writeAttribute(ID_ATTR, QString::number(m_chats[floor].getId()));
                    xml.writeAttribute(FLOOR_ATTR, QString::number(floor));
                    xml.writeEndElement(); // CHAT_TAG
                }
            xml.writeEndElement(); // CHATS_WRAPPER_TAG
        xml.writeEndElement(); // SEQURE_WRAPPER_TAG
    xml.writeEndElement(); // CONFIG_WRAPPER_TAG
    xml.writeEndDocument();
    return true;
}

bool Settings::readConf(QFile *file)
{
    QXmlStreamReader xml(file);
    QXmlStreamAttributes attributes;
    if (xml.hasError()) {
        ErrorMessages::errorXmlParse(nullptr, file->fileName(), xml.errorString());
        return false;
    }

    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        attributes = xml.attributes();
        if (token==QXmlStreamReader::StartDocument)
            continue;
        else if (token == QXmlStreamReader::StartElement) {
            if (xml.name()==CONFIG_WRAPPER_TAG) {
                continue;
            }
            else if (xml.name()==HIGHTLIGHT_SYMBOLS_TAG) {
                if(attributes.hasAttribute(VALUE_ATTR)) {
                    m_hsymbols = attributes.value(VALUE_ATTR).toString();
                } else {
                    m_hsymbols = "";
                }
            }
            else if (xml.name()==SIGNATURE_TAG) {
                if(attributes.hasAttribute(VALUE_ATTR)) {
                    m_signature = attributes.value(VALUE_ATTR).toString();
                } else {
                    m_signature = "";
                }
            }
            else if (xml.name()==SEQURE_WRAPPER_TAG) {
                xml.readNext();
                attributes = xml.attributes();
                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == SEQURE_WRAPPER_TAG))
                {
                    if (xml.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xml.name()==ENCRY_TAG) {
                            if(attributes.hasAttribute(VALUE_ATTR)) {
                                m_isEncrypted = attributes.value(VALUE_ATTR).toInt()?true:false;
                            } else {
                                m_isEncrypted = false;
                            }
                        } else if (xml.name()==HASH_TAG) {
                            if(attributes.hasAttribute(VALUE_ATTR)) {
                                m_tokenSignature = attributes.value(VALUE_ATTR).toString();
                            } else {
                                m_tokenSignature = "";
                            }
                        } else if (xml.name()==VK_TOKEN_TAG) {
                            if (attributes.hasAttribute(VALUE_ATTR)) {
                                m_vkToken = attributes.value(VALUE_ATTR).toString();
                            } else {
                                m_vkToken = "";
                            }
                            if (attributes.hasAttribute(IV_ATTR)) {
                                m_initializeVector = attributes.value(IV_ATTR).toString();
                            } else {
                                m_initializeVector = "";
                            }
                        } else if (xml.name()==CHATS_WRAPPER_TAG) {
                            xml.readNext();
                            attributes = xml.attributes();
                            while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == CHATS_WRAPPER_TAG))
                            {
                                if (xml.tokenType() == QXmlStreamReader::StartElement)
                                {
                                    if (xml.name()==CHAT_TAG) {
                                        VkChat chat;
                                        uint8_t floorN;
                                        if (attributes.hasAttribute(NAME_ATTR)) {
                                            chat.setTitle(attributes.value(NAME_ATTR).toString());
                                        }
                                        if (attributes.hasAttribute(ID_ATTR)) {
                                            chat.setId(attributes.value(ID_ATTR).toUInt());
                                        }
                                        if (attributes.hasAttribute(FLOOR_ATTR)) {
                                            floorN = attributes.value(FLOOR_ATTR).toUInt();
                                        } else {
                                            floorN = 0;
                                        }
                                        if (m_chats.contains(floorN)) {
                                            //TODO: Warning box
                                        }
                                        m_chats[floorN]=chat;
                                    }
                                }
                                xml.readNext();
                                attributes = xml.attributes();
                            }
                        }
                    }
                    xml.readNext();
                    attributes = xml.attributes();
                }
            }
        }
    }
    return true;
}

QString Settings::getInitializeVector() const
{
    return m_initializeVector;
}

void Settings::setInitializeVector(const QString &initializeVector)
{
    m_initializeVector = initializeVector;
}

void Settings::setChats(const QHash<uint8_t, VkChat> &chats)
{
    m_chats = chats;
}

QHash<uint8_t, VkChat> Settings::getChats() const
{
    return m_chats;
}
