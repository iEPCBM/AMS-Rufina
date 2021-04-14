#ifndef APPINFO_H
#define APPINFO_H

#include <QString>
#include <QVersionNumber>
#include <QDateTime>
#include "third_party/CompileTime/CompileTime.h"

#define APP_VERSION_MAJ 1
#define APP_VERSION_MIN 0
#define APP_VERSION_MIC 0

#define APP_LICENSE "GNU GPL v3"

#if APP_VERSION_MIC == 0
# define APP_VERSION_STAGE "alpha"
#elif APP_VERSION_MIC == 1
# define APP_VERSION_STAGE "beta"
#else
# define APP_VERSION_STAGE "release"
#endif

struct AppInfo {
    static QString buildAboutText() {
        QDateTime datetime;
        datetime.setTime_t(UNIX_TIMESTAMP);
        QVersionNumber verNum (APP_VERSION_MAJ, APP_VERSION_MIN, APP_VERSION_MIN);
        QString text =
                QString("<h1>САОС \"Руфина\"</h1>") +
                "<p>Система автоматизированной отправки сообщений \"Руфина\"</p>" +
                "<p><b>Версия: </b> " + verNum.toString() + " (" + APP_VERSION_STAGE + ")</p>" +
                "<p><b>Дата и время сборки: </b> " + datetime.toString(Qt::DateFormat::DefaultLocaleLongDate) + " (UTC)</p>" +
                "<p><b>Лицензия: </b> " + APP_LICENSE + "</p>" +
                "<hr>" +
                "<p>САОС \"Руфина\" Copyright &copy; 2021 Ришат Д. Кагиров</p>" +
                "<p>Это свободная программа: вы можете перераспространять ее и/или изменять" +
                " ее на условиях Стандартной общественной лицензии GNU в том виде, в каком" +
                " она была опубликована Фондом свободного программного обеспечения; либо" +
                " версии 3 лицензии, либо (по вашему выбору) любой более поздней версии.</p>" +
                "<p>Эта программа распространяется в надежде, что она будет полезной," +
                " но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА" +
                " или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной" +
                " общественной лицензии GNU.</p>" +
                "<p>Вы должны были получить копию Стандартной общественной лицензии GNU" +
                " вместе с этой программой. Если это не так, см." +
                " <a href=\"https://www.gnu.org/licenses/\">https://www.gnu.org/licenses/</a>.</p>";
        return text;
    }
};

#endif // APPINFO_H
