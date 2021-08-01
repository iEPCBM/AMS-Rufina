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

#ifndef DIALOGPASSWORDENTER_H
#define DIALOGPASSWORDENTER_H

#include <QDialog>
#include <QMessageBox>
#include "aesfacade.h"

namespace Ui {
class DialogPasswordEnter;
}

class DialogPasswordEnter : public QDialog
{
    Q_OBJECT

public:
    DialogPasswordEnter(QByteArray encryptedData, QByteArray iv, QWidget *parent = nullptr);
    ~DialogPasswordEnter();

    QString getPassword();

    bool isSuccessful() const;

    QByteArray getDecryptedData() const;

    QByteArray getEncryptedData() const;
    void setEncryptedData(const QByteArray &encryptedData);

private slots:
    void on_buttonBox_accepted();
    void accept(){}

private:
    Ui::DialogPasswordEnter *ui;
    QByteArray m_encryptedData;
    QString m_pswd;
    AESFacade m_aes;
    QByteArray m_decryptedData;
    bool m_isSuccessful = false;
};

#endif // DIALOGPASSWORDENTER_H
