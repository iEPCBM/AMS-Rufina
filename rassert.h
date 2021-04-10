#ifndef RASSERT_H
#define RASSERT_H

#include <QMessageBox>

#define R_ASSERT(EXPRESSION, PARENT, EXCEPTION_ACTIONS) \
    if(!EXPRESSION) { \
        QMessageBox::critical(PARENT, "Вызвано исключение", \
                                 static_cast<QString>("Вызвано исключение!\nНе удовлетворено условие: ")+#EXPRESSION+\
                                 "\nВ файле: " + __FILE__ + " (стр.: "+ QString::number(__LINE__) +").\nБудет выполнено действие: " + #EXCEPTION_ACTIONS); \
        EXCEPTION_ACTIONS;}

struct ErrorMessages {
    static void errorNetwork(QWidget *parent) {
        QMessageBox::critical(parent, "Проблемы с подключением к Интернету",
                                 static_cast<QString>("Не удалось подключиться к серверу. Проверьте подключение к Интернету и повторитк попытку."));
    }
    static void errorVkApi(QWidget *parent, int errorCode, QString description) {
        QMessageBox::warning(parent, "Ошибка VK API",
                                 static_cast<QString>("VK API вернул ошибку.\nКод ошибки: ")+QString::number(errorCode)+"\nОписание ошибки: "+description);
    }
    static void errorFileAccess(QWidget *parent, QString filePath) {
        QMessageBox::critical(parent, "Ошибка доступа к файлу",
                                 static_cast<QString>("Ошибка доступа к файлу: ")+filePath);
    }
};

#endif // RASSERT_H
