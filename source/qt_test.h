#ifndef QTTEST_H
#define QTTEST_H

#include "proc_settings.h"


class QtTest
{
public:
    QtTest();
    ~QtTest();
    void run(void);
    void list_test(void);
    void dir_test(void);
    void proc_settings_test(void);

    ProcSettings *settings_test;

};

#endif // QTTEST_H
