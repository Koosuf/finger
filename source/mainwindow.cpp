#include "mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("FVR--2016"));
    show();
    create_actions();
    create_menus();

    setup();
}

MainWindow::~MainWindow()
{
    //delete layout
    if(view_layout)
        delete view_layout;

    //delete views
    qDeleteAll(view_list.begin(), view_list.end());

    //delete menus
    if(file_menu)
        delete file_menu;
    if(setting_menu)
        delete setting_menu;
    if(about_menu)
        delete about_menu;

    //delete actions
    if(new_act)
        delete new_act;
    if(exit_act)
        delete exit_act;
}


void MainWindow::setup()
{
    views = new QWidget(this);
    view_layout = new QGridLayout(views);

    SingleView *single_view = new SingleView("default.png");
    view_list.append(single_view);
    view_layout->addWidget(single_view,0,0);

    views->setLayout(view_layout);
    setCentralWidget(views);
}

void MainWindow::create_menus()
{
    file_menu = menuBar()->addMenu(tr("&File"));
    file_menu->setStyleSheet("color:blue");
    file_menu->addAction(new_act);
    file_menu->addSeparator();
    file_menu->addAction(exit_act);

    setting_menu = menuBar()->addMenu(tr("&Setings"));
    about_menu = menuBar()->addMenu(tr("&About"));
}

void MainWindow::create_actions()
{
    exit_act = new QAction(tr("&Close"),this);
    exit_act->setShortcut(QKeySequence::Close);
    connect(exit_act,SIGNAL(triggered(bool)),this,SLOT(exit_Act()));

    new_act = new QAction(tr("&New"),this);
    new_act->setShortcut(QKeySequence::New);
    connect(new_act,SIGNAL(triggered(bool)),this,SLOT(new_Act()));
}

void MainWindow::new_Act()
{
    int count = view_list.count();
    if(count >= 16)
    {
        QMessageBox::information(this,tr("提示"),tr("最多显示16幅图片"),QMessageBox::Ok);
        return;
    }

    SingleView *single_view = new SingleView("default.png");
    view_list.append(single_view);
    view_layout->addWidget(single_view,count/4,count%4);
}

void MainWindow::exit_Act()
{
    close();
}

