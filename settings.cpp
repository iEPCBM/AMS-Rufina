#include "settings.h"
#include <QDebug>

Settings::Settings(QString strPath)
{
    m_strPath = strPath;
}

void Settings::save()
{

}

void Settings::extract()
{
    QFile file(m_strPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"err_parse";
        return;
    }
    QXmlStreamReader xml(&file);
    QXmlStreamAttributes attributes;
    if (xml.hasError()) {
        qDebug()<<xml.errorString();
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
                        } /*else if (xml.name()==CHATS_WRAPPER_TAG) {
                            xml.readNext();
                            attributes = xml.attributes();
                            while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == CHATS_WRAPPER_TAG))
                            {
                                if (xml.tokenType() == QXmlStreamReader::StartElement)
                                {
                                    if (xml.name()==CHAT_TAG) {
                                        if(attributes.hasAttribute(VALUE_ATTR)) {
                                            m_isEncrypted = attributes.value(VALUE_ATTR).toInt()?true:false;
                                        } else {
                                            m_signature = false;
                                        }
                                    }
                                }
                            }
                        }*/
                    }
                    xml.readNext();
                    attributes = xml.attributes();
                }
            }
        }
    }
    file.close();
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
