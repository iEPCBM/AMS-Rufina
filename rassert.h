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

#ifndef RASSERT_H
#define RASSERT_H

#include <QMessageBox>

#define R_ASSERT(EXPRESSION, EXCEPTION_ACTIONS, PARENT) \
    if(!(EXPRESSION)) { \
        QMessageBox::critical(PARENT, "Вызвано исключение", \
                                 static_cast<QString>("Вызвано исключение!\nНе удовлетворено условие: ")+#EXPRESSION+\
                                 "\nВ файле: " + __FILE__ + " (стр.: "+ QString::number(__LINE__) +").\nБудет выполнено действие: " + #EXCEPTION_ACTIONS); \
        EXCEPTION_ACTIONS;}

struct ErrorMessages {
    static void errorNetwork(QWidget *parent, QString description) {
        QMessageBox::critical(parent, "Проблемы с подключением к серверу",
                                 static_cast<QString>("Не удалось подключиться к серверу. Проверьте подключение к Интернету и повторите попытку.\nОшибка: "+description));
    }
    static void errorVkApi(QWidget *parent, int errorCode, QString description) {
        QMessageBox::warning(parent, "Ошибка VK API",
                                 static_cast<QString>("VK API вернул ошибку.\nКод ошибки: ")+QString::number(errorCode)+"\nОписание ошибки: "+description);
    }
    static QMessageBox::StandardButton errorVkApi(QWidget *parent, int errorCode, QString description, QMessageBox::StandardButtons btns) {
        return QMessageBox::warning(parent, "Ошибка VK API",
                                 static_cast<QString>("VK API вернул ошибку.\nКод ошибки: ")+QString::number(errorCode)+"\nОписание ошибки: "+description, btns);
    }
    static void errorFileAccess(QWidget *parent, QString filePath) {
        QMessageBox::critical(parent, "Ошибка доступа к файлу",
                                 static_cast<QString>("Ошибка доступа к файлу: ")+filePath);
    }
    static void errorXmlParse(QWidget *parent, QString filePath, QString strError="") {
        QMessageBox::critical(parent, "Ошибка обработки XML файла",
                                 (static_cast<QString>("Ошибка обработки XML файла: ")+filePath + "\n" + strError).trimmed());
    }
};

#endif // RASSERT_H
