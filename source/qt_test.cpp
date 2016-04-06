#include "qt_test.h"
#include <QList>
#include <QDir>

#include <iostream>

using std::cout;
using std::endl;


QtTest::QtTest()
{
}

void QtTest::run()
{
    //list_test();
    dir_test();
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
}

void QtTest::dir_test()
{
    cout<<QDir::currentPath().toStdString()<<endl;
}
