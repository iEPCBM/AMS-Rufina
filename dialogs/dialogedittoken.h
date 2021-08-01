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

#ifndef DIALOGEDITTOKEN_H
#define DIALOGEDITTOKEN_H

#include <QDialog>

namespace Ui {
class DialogEditToken;
}

class DialogEditToken : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditToken(QString token, QWidget *parent = nullptr);
    ~DialogEditToken();

    QString token() const;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogEditToken *ui;
    QString m_token;
};

#endif // DIALOGEDITTOKEN_H
