#include "mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QCloseEvent>



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
    //delete views
    qDeleteAll(view_list.begin(), view_list.end());

    //delete layout
    if(view_layout)
        delete view_layout;

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

    //delete dialog
    if(proc_settings)
        delete proc_settings;
}


void MainWindow::setup()
{
    views = new QWidget(this);
    view_layout = new QGridLayout(views);

    SingleView *single_view = new SingleView("default.png");
    connect(single_view,&SingleView::destroyed,this,&MainWindow::reorder_views);
    view_list.append(single_view);
    view_layout->addWidget(single_view,0,0);

    views->setLayout(view_layout);
    setCentralWidget(views);
}

void MainWindow::create_menus()
{
    file_menu = menuBar()->addMenu(tr("&文件"));
    file_menu->setStyleSheet("color:blue");
    file_menu->addAction(new_act);
    file_menu->addSeparator();
    file_menu->addAction(exit_act);

    test_menu = menuBar()->addMenu(tr("测试"));
    test_menu->addAction(image_fusion_act);


    setting_menu = menuBar()->addMenu(tr("&设置"));
    setting_menu->addAction(proc_setting_act);


    about_menu = menuBar()->addMenu(tr("&About"));
}

void MainWindow::create_actions()
{
    exit_act = new QAction(tr("&关闭"),this);
    exit_act->setShortcut(QKeySequence::Close);
    connect(exit_act,SIGNAL(triggered(bool)),this,SLOT(exit_Act()));

    new_act = new QAction(tr("&新建"),this);
    new_act->setShortcut(QKeySequence::New);
    connect(new_act,SIGNAL(triggered(bool)),this,SLOT(new_Act()));

    proc_setting_act = new QAction(tr("&图像设置"),this);
    connect(proc_setting_act,SIGNAL(triggered(bool)),this,SLOT(proc_setting_Act()));

    image_fusion_act = new QAction(tr("图像融合"),this);
    connect(image_fusion_act, SIGNAL(triggered(bool)),this,SLOT(image_fusion_Act()));
}

void MainWindow::new_Act()
{
    int count = view_list.count();
    if(count >= 9)
    {
        QMessageBox::information(this,tr("提示"),tr("最多显示9幅图片"),QMessageBox::Ok);
        return;
    }


    SingleView *single_view = new SingleView("default.png");
    connect(single_view,&SingleView::destroyed,this,&MainWindow::reorder_views);
    view_list.append(single_view);
    view_layout->addWidget(single_view,count/2,count%2);

    view_layout->activate();
    setFixedSize(sizeHint());
}

void MainWindow::exit_Act()
{
    exit(0);
}

void MainWindow::reorder_views(QObject* pointer)
{
    view_list.removeOne((SingleView*)pointer);
    view_layout->removeWidget((SingleView*)pointer);
    ((SingleView*)pointer)->close();


    int count = 0;

    foreach(SingleView* view, view_list)
    {
        view_layout->removeWidget(view);
        view_layout->addWidget(view,count/2,count%2);
        count++;
    }

    view_layout->activate();

    if(view_list.count() == 0)
        exit(0);

    setFixedSize(sizeHint());
}

void MainWindow::proc_setting_Act()
{
    proc_settings = new ProcSettings();
    proc_settings->show();
}


void MainWindow::image_fusion_Act()
{
    QStringList images = QFileDialog::getOpenFileNames(this,"选择多张图片","/Users/taozhigang/Documents/develop/finger/result", "Images (*.png *.xpm *.jpg)");
    while(images.count() < 2)
    {
        int ret = QMessageBox::information(this,tr("提示"),tr("请选择大于两张的图片"),QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        if(ret == QMessageBox::Ok)
            images = QFileDialog::getOpenFileNames(this,"选择多张图片","/Users/taozhigang/Documents/develop/finger/result", "Images (*.png *.xpm *.jpg)");
        else
            return;
    }

    cv::Mat rest = cv::Mat::zeros(80,200,CV_32F);

    foreach (QString image, images)
    {
        cv::Mat img = cv::imread(image.toStdString(),0);
        cv::resize(img,img,cv:: Size(200,80));
        img.convertTo(img,CV_32F);
        rest = rest + img;
    }

    cv::GaussianBlur(rest,rest,cv::Size(5,5),1);

    threshold(rest,rest,200,255,CV_THRESH_TOZERO);

    rest.convertTo(rest,CV_8U);

    cv::namedWindow("fusion");
    cv::imshow("fusion",rest);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
