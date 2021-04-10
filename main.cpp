#include "mainwindow.h"

#include <QApplication>
#include "rassert.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("windows");
    MainWindow w;
    w.show();
    R_ASSERT(false, nullptr, qDebug()<<"ERROR!");
    return a.exec();
}
