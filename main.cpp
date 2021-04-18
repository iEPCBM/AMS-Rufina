#include "mainwindow.h"

#include <QApplication>
#include "rassert.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("windows");
    QTranslator qtTranslator;
    if (qtTranslator.load("qtbase_ru", ":/langs/third_party/"))
    {
        a.installTranslator(&qtTranslator);
    }
    MainWindow w;

    w.show();
    R_ASSERT(false, qDebug()<<"ERROR!", nullptr);
    return a.exec();
}
