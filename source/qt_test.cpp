#include "qt_test.h"
#include <QList>
#include <QDir>

#include <iostream>
#include "proc_settings.h"

using std::cout;
using std::endl;


QtTest::QtTest()
{
}

QtTest::~QtTest()
{
    if(settings_test)
        delete settings_test;
}

void QtTest::run()
{
    //list_test();
    //dir_test();
    //proc_settings_test();
}

void QtTest::list_test()
{
    QList<int> integerlist;
    int num = 100;
    integerlist.append(num);
    num=200;
    integerlist.append(num);
    cout<<"First: "<<integerlist.at(0)<<endl;
    cout<<"Last: "<<integerlist.at(1)<<endl;
    integerlist.removeOne(100);
    cout<<"Now: "<<integerlist.first()<<endl;
}

void QtTest::dir_test()
{
    cout<<QDir::currentPath().toStdString()<<endl;
}

void QtTest::proc_settings_test()
{
    settings_test = new ProcSettings();
    settings_test->show();
}
