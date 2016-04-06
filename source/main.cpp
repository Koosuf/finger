#include "mainwindow.h"
#include <QApplication>
#include "qt_test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QtTest test;
    test.run();

    MainWindow w;
    w.show();

    return a.exec();
}
