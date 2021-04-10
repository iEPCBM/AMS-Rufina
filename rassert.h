#ifndef RASSERT_H
#define RASSERT_H

#include <QMessageBox>

#define R_ASSERT(EXPRESSION, PARENT, EXCEPTION_ACTIONS) \
    if(!EXPRESSION) { \
        QMessageBox::critical(PARENT, "Вызвано исключение", \
                                 static_cast<QString>("Вызвано исключение!\nНе удовлетворено условие: ")+#EXPRESSION+\
                                 "\nВ файле: " + __FILE__ + " (стр.: "+ QString::number(__LINE__) +").\nБудет выполнено действие: " + #EXCEPTION_ACTIONS); \
        EXCEPTION_ACTIONS;}

#define R_ERR_NETWORK(PARENT) \


#endif // RASSERT_H
