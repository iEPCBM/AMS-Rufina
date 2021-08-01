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

#ifndef DIALOGCREATEPASSWORD_H
#define DIALOGCREATEPASSWORD_H

#include <QDialog>
#include <QPushButton>
#include "aesfacade.h"

namespace Ui {
class DialogCreatePassword;
}

class DialogCreatePassword : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCreatePassword(QByteArray data, QWidget *parent = nullptr);
    ~DialogCreatePassword();

    QByteArray endcryptedData() const;

    QByteArray IV() const;

private slots:
    void on_lePasswordConfirm_textEdited(const QString &arg1);

    void on_lePassword_textEdited(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::DialogCreatePassword *ui;
    inline bool checkPassword();

    AESFacade m_aes;
    QByteArray m_endcryptedData;
    QByteArray m_IV;
};

#endif // DIALOGCREATEPASSWORD_H
