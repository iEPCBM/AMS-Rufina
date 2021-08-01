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

#ifndef DIALOGCHATCONFIRMATION_H
#define DIALOGCHATCONFIRMATION_H

#include <QDialog>
#include <QTime>
#include <QDate>
#include <QTimer>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QRandomGenerator>
#include "vkApi/vkchat.h"
#include "vkApi/vkmessagedelivery.h"
#include "rassert.h"


#define CRC_SALT "Руфина, прости меня. Ты мне правда нравишься."
#define STR_CONFIRMATION_PREAMBLE "Код подтверждения: "

namespace Ui {
class DialogChatConfirmation;
}

class DialogChatConfirmation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChatConfirmation(VkChat chat, QString token, QWidget *parent = nullptr);
    ~DialogChatConfirmation();

    bool isConfirmated() const;

private slots:
    void on_btSendAgain_clicked();

    void on_buttonBox_accepted();
    void accept(){}
    void onShowed();
private:
    Ui::DialogChatConfirmation *ui;
    QByteArray crc32b(QByteArray message);
    VkChat m_chat;
    VkMessageDelivery m_msgDelivery;
    QString m_data2hash;
    uint32_t m_pubKey;
    void generateCode();
    bool m_isConfirmated = false;
};

#endif // DIALOGCHATCONFIRMATION_H
