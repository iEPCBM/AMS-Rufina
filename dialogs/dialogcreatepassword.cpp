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

#include "dialogcreatepassword.h"
#include "ui_dialogcreatepassword.h"

DialogCreatePassword::DialogCreatePassword(QByteArray data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreatePassword),
    m_aes(data)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->lbIsPswdEqual->setStyleSheet("color: red;");
    ui->lePassword->setFocus();
}

DialogCreatePassword::~DialogCreatePassword()
{
    delete ui;
}

void DialogCreatePassword::on_lePasswordConfirm_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(checkPassword());
    ui->lbIsPswdEqual->setText(checkPassword()?"":"Пароли не совпадают");
}
void DialogCreatePassword::on_lePassword_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(checkPassword());
    ui->lbIsPswdEqual->setText(checkPassword()?"":"Пароли не совпадают");
}

bool DialogCreatePassword::checkPassword()
{
    if (ui->lePassword->text()!=ui->lePasswordConfirm->text()||ui->lePassword->text().isEmpty()) return false;
    return true;
}

QByteArray DialogCreatePassword::IV() const
{
    return m_IV;
}

QByteArray DialogCreatePassword::endcryptedData() const
{
    return m_endcryptedData;
}

void DialogCreatePassword::on_buttonBox_accepted()
{
    m_endcryptedData = m_aes.encryption(ui->lePassword->text());
    m_IV = m_aes.getIV();
}
