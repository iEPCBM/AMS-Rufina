#include "settings.h"
#include <QDebug>

Settings::Settings(QString strPath)
{
    m_strPath = strPath;
}

void Settings::exportConf(QString strPath)
{
    QFile *file = new QFile(strPath);
    if (!file->open(QIODevice::WriteOnly)) {
        qDebug()<<"err_parse";
        return;
    }
    writeConf(file);
    file->close();
}

void Settings::importConf(QString strPath)
{
    QFile *file = new QFile(strPath);
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug()<<"err_parse";
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
    QFile *file = new QFile(m_strPath);
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug()<<"err_parse";
        return;
    }
    readConf(file);
    file->close();
}

Settings* Settings::getInstance()
{
    Settings* ptr_stg = new Settings("D:\\Projects\\Programs\\CPP\\QT\\VK_ChatsMessageDelivery\\RUFINA\\RUFINA\\assets\\config.xml");
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
            xml.writeAttribute(VALUE_ATTR, m_vkToken);
            xml.writeEndElement(); // VK_TOKEN_TAG

            xml.writeStartElement(CHATS_WRAPPER_TAG);
                for (auto i=2; i<=5; i++) {
                    xml.writeStartElement(CHAT_TAG);
                    xml.writeAttribute(NAME_ATTR, m_chats[i].getTitle());
                    xml.writeAttribute(ID_ATTR, QString::number(m_chats[i].getId()));
                    xml.writeAttribute(FLOOR_ATTR, QString::number(i));
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
        qDebug()<<xml.errorString();
        return false;
    }

    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        attributes = xml.attributes();
        //qDebug()<<xml.name();
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
                                qDebug()<<attributes.value(VALUE_ATTR);
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
                            if(attributes.hasAttribute(VALUE_ATTR)) {
                                m_vkToken = attributes.value(VALUE_ATTR).toString();
                            } else {
                                m_vkToken = "";
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
                                        qDebug()<<floorN<<" "<<chat.getTitle();
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

QHash<uint8_t, VkChat> Settings::getChats() const
{
    return m_chats;
}
