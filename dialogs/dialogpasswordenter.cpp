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

#include "dialogpasswordenter.h"
#include "ui_dialogpasswordenter.h"

DialogPasswordEnter::DialogPasswordEnter(QByteArray encryptedData, QByteArray iv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPasswordEnter),
    m_aes(encryptedData, iv)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

DialogPasswordEnter::~DialogPasswordEnter()
{
    delete ui;
}

QString DialogPasswordEnter::getPassword()
{
    return m_pswd;
}

void DialogPasswordEnter::on_buttonBox_accepted()
{
    m_pswd = ui->lePswd->text();
    if (m_aes.decryption(m_pswd)) {
        m_decryptedData = m_aes.getDecryptedData();
        m_isSuccessful = true;
        this->close();
    } else {
        QMessageBox::StandardButton bt =
                QMessageBox::critical(this, "Ошибка", "Неправильный пароль!", QMessageBox::Retry|QMessageBox::Ok, QMessageBox::Retry);
        if (bt == QMessageBox::Ok) {
            this->close();
        } else {
            ui->lePswd->clear();
            ui->lePswd->setFocus();
        }
    }
}

QByteArray DialogPasswordEnter::getEncryptedData() const
{
    return m_encryptedData;
}

void DialogPasswordEnter::setEncryptedData(const QByteArray &encryptedData)
{
    m_encryptedData = encryptedData;
}

QByteArray DialogPasswordEnter::getDecryptedData() const
{
    return m_decryptedData;
}

bool DialogPasswordEnter::isSuccessful() const
{
    return m_isSuccessful;
}
