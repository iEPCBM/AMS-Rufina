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

#include "dialogchatconfirmation.h"
#include "ui_dialogchatconfirmation.h"

DialogChatConfirmation::DialogChatConfirmation(VkChat chat, QString token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChatConfirmation),
    m_msgDelivery(token, this)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->leCodeInput->setValidator(new QRegExpValidator(QRegExp("^[a-fA-F0-9]+$"), this));
    m_chat = chat;
    QTimer::singleShot(0, this, SLOT(onShowed())); //Hmmm. After
}

DialogChatConfirmation::~DialogChatConfirmation()
{
    delete ui;
}

QByteArray DialogChatConfirmation::crc32b(QByteArray message)
{
    uint32_t byte, crc, mask, len;

    len = message.length();
    crc = 0xFFFFFFFF;

    for (auto i = 0; --len; i++) {
       byte = static_cast<uint32_t>(message.at(i));
       crc = crc ^ byte;
       for (auto j = 0; j < 8; j++) {
          mask = -(crc & 1);
          crc = (crc >> 1) ^ (0xEDB88320 & mask);
       }
    }
    crc = ~crc;
    QByteArray retVal(reinterpret_cast<char*>(&crc), sizeof(crc));
    return retVal;
}

void DialogChatConfirmation::generateCode()
{
    QRandomGenerator *randGen = QRandomGenerator::global();
    m_data2hash = QDate::currentDate().toString(Qt::ISODate)+" "
            +QTime::currentTime().toString(Qt::ISODateWithMs)
            +QString::number(VK_API_MULTICHAT_BASE_ID+m_chat.getId())
            +QString::number(randGen->generate())
            +CRC_SALT;
    QByteArray crcHash = crc32b(m_data2hash.toUtf8()).toHex();
    m_pubKey = randGen->bounded(1000);
    ui->lbPubKey->setText(QString::number(m_pubKey));
    m_msgDelivery.sendMessage(VK_API_MULTICHAT_BASE_ID+m_chat.getId(),
                              QString(STR_CONFIRMATION_PREAMBLE) + QString::fromUtf8(crcHash)
                              +"\nСверочный код: " + QString::number(m_pubKey));
    if(m_msgDelivery.hasError()) {
        VkError vkErr = m_msgDelivery.getVkError();
        if (vkErr.hasError()) {
            ErrorMessages::errorVkApi(this, vkErr.code(), vkErr.description());
        }
        this->reject();
    }
}

bool DialogChatConfirmation::isConfirmated() const
{
    return m_isConfirmated;
}

void DialogChatConfirmation::on_btSendAgain_clicked()
{
    generateCode();
}

void DialogChatConfirmation::on_buttonBox_accepted()
{
    QByteArray checkHash = crc32b(m_data2hash.toUtf8()).toHex();
    if (ui->leCodeInput->text().toLower()!=QString::fromUtf8(checkHash)) {
        QMessageBox::StandardButton bt = QMessageBox::warning(this, "Ошибка", "Код не совпадает", QMessageBox::Retry|QMessageBox::Ok);
        if (bt==QMessageBox::Retry){
            ui->leCodeInput->clear();
            generateCode();
        }
        else {this->close();}
    } else {
        m_isConfirmated = true;
        this->close();
    }
}

void DialogChatConfirmation::onShowed()
{
    generateCode();
}
