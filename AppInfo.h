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

#ifndef APPINFO_H
#define APPINFO_H

#include <QString>
#include <QVersionNumber>
#include <QDateTime>
#include "third_party/CompileTime/CompileTime.h"

#define APP_LICENSE "GNU GPL v3"

#if APP_VER_PAT == 0
# define APP_VERSION_STAGE "alpha"
#elif APP_VER_PAT == 1
# define APP_VERSION_STAGE "beta"
#else
# define APP_VERSION_STAGE "release"
#endif

struct AppInfo {
    static QString buildAboutText() {
        QDateTime datetime;
        datetime.setTime_t(UNIX_TIMESTAMP);

        QString text =
                QString("<h1>САОС \"Руфина\"</h1>") +
                "<p>Система автоматизированной отправки сообщений \"Руфина\"</p>"
                "<p><b>Версия: </b> " + getVersion() + " (" + APP_VERSION_STAGE + ")</p>"
                "<p><b>Дата и время сборки: </b> " + datetime.toString(Qt::DateFormat::DefaultLocaleLongDate) + " (UTC)</p>"
                "<p><b>Лицензия: </b> " + APP_LICENSE + "</p>"
                "<hr>"
                "<p>САОС \"Руфина\" Copyright &copy; 2021 Ришат Д. Кагиров</p>"
                "<p>Это свободная программа: вы можете перераспространять ее и/или изменять "
                "ее на условиях Стандартной общественной лицензии GNU в том виде, в каком "
                "она была опубликована Фондом свободного программного обеспечения; либо "
                "версии 3 лицензии, либо (по вашему выбору) любой более поздней версии.</p>"
                "<p>Эта программа распространяется в надежде, что она будет полезной, "
                "но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА "
                "или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной "
                "общественной лицензии GNU.</p>"
                "<p>Вы должны были получить копию Стандартной общественной лицензии GNU "
                "вместе с этой программой. Если это не так, см. "
                "<a href=\"https://www.gnu.org/licenses/\">https://www.gnu.org/licenses/</a>.</p>";
        return text;
    }
    static QString getVersion() {
#ifdef Q_OS_WIN
        QVector<int> verNums;
        verNums.append(APP_VER_MAJ);
        verNums.append(APP_VER_MIN);
        verNums.append(APP_VER_PAT);
        verNums.append(APP_VER_BUILD);

        QVersionNumber verNum (verNums);
#else
        QVersionNumber verNum (APP_VER_MAJ, APP_VER_MIN, APP_VER_PAT);
#endif
        return verNum.toString();
    }
};

#endif // APPINFO_H
