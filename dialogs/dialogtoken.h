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

#ifndef DIALOGTOKEN_H
#define DIALOGTOKEN_H

#include <QDialog>

namespace Ui {
class DialogToken;
}

class DialogToken : public QDialog
{
    Q_OBJECT

public:
    explicit DialogToken(QWidget *parent = nullptr);
    ~DialogToken();

    void setToken(const QString &strToken);

private:
    inline void displayToken();
    QString m_strToken;
    Ui::DialogToken *ui;
};

#endif // DIALOGTOKEN_H
