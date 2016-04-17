#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QList>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QFileDialog>

#include "single_view.h"
#include "proc_settings.h"
#include "opencv2/opencv.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void reorder_views(QObject* pointer = Q_NULLPTR);

private:
    void setup(void);
    void create_menus(void);
    void create_actions(void);
    bool add_view(void);


private:
    QList<SingleView*> view_list;
    QGridLayout *view_layout;
    QWidget *views;

    QMenu *file_menu;
    QMenu *setting_menu;
    QMenu *test_menu;
    QMenu *about_menu;

    /* actions for file_menu */
    QAction *new_act;
    QAction *exit_act;

    /* actions for setting menu */
    QAction *proc_setting_act;

    /* actions for test menu */
    QAction *image_fusion_act;

    ProcSettings *proc_settings;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void new_Act(void);
    void exit_Act(void);
    void proc_setting_Act(void);
    void image_fusion_Act(void);
};

#endif // MAINWINDOW_H
