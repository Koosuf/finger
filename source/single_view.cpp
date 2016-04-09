#include "single_view.h"
#include <QFileInfo>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>


SingleView::SingleView(QString img_name)
{
    QFileInfo check_file(img_name);
    if(!check_file.exists() || !check_file.isFile())
        img_name = "/Users/taozhigang/Documents/develop/finger/resource/default.png";
    ori_img = new QImage(img_name);
    proc_img = NULL;
    proc = new Proc(*ori_img);
    create_view();
    this->setLayout(main_layout);
    setFixedSize(340,300);
}


SingleView::~SingleView()
{
    if(ori_img)
        delete ori_img;
    if(proc_img)
        delete proc_img;

    if(proc)
        delete proc;
}

void SingleView::create_view()
{
    main_layout = new QGridLayout(this);

    img_lable = new QLabel(this);
    img_lable->setFixedSize(320,240);
    img_lable->setPixmap(QPixmap::fromImage(*ori_img));
    main_layout->addWidget(img_lable,0,0,1,3);

    open_button = new QPushButton(tr("&open"));
    connect(open_button,SIGNAL(clicked(bool)),this,SLOT(open_Act()));
    open_button->setDefault(true);
    main_layout->addWidget(open_button,1,0);

    proc_button = new QPushButton(tr("&proc"));
    connect(proc_button,SIGNAL(clicked(bool)),this,SLOT(proc_Act()));
    proc_button->setDefault(true);
    main_layout->addWidget(proc_button,1,1);

    quit_button = new QPushButton(tr("&quit"));
    quit_button->setDefault(true);
    connect(quit_button,SIGNAL(clicked(bool)),this,SLOT(quit_Act()));
    main_layout->addWidget(quit_button,1,2);
}


void SingleView::open_Act()
{
    QString img_name = QFileDialog::getOpenFileName(this, "Select Images", "/Users/taozhigang/Desktop/finger_image/", "Images (*.png *.jpg *.bmp)");
    QFileInfo check_file(img_name);
    if(!check_file.exists() || !check_file.isFile())
        return;
    ori_img->load(img_name);

    if(ori_img->width()*2 >= ori_img->height()*3)
        *ori_img = ori_img->scaledToWidth(320);
    else
        *ori_img = ori_img->scaledToHeight(240);

    img_lable->setPixmap(QPixmap::fromImage(*ori_img));
}

void SingleView::proc_Act()
{
    //warning default image format is rgb32 use script to conver them

    QImage tmp_img(ori_img->scaled(320,240));
    proc->reset_img(&tmp_img);

    set_params();

    if(!proc->run(&proc_img))
    {
        QMessageBox::warning(this,tr("错误"),tr("处理失败"),QMessageBox::Ok);
        if(proc_img)
        {
            delete proc_img;
            proc_img =NULL;
        }
     }

    img_lable->setPixmap(QPixmap::fromImage(*proc_img));

}

void SingleView::quit_Act()
{
    emit destroyed(this);
}

void SingleView::set_params()
{
    QSettings settings(tr("/Users/taozhigang/Documents/develop/finger/config/settings.plist"),QSettings::NativeFormat);

    struct Proc::Params params;
    params.size.x = settings.value("img_proc/pre_cut/size/x",0).toInt();
    params.size.y = settings.value("img_proc/pre_cut/size/y",0).toInt();
    params.size.width = settings.value("img_proc/pre_cut/size/width", ori_img->width()).toInt();
    params.size.height = settings.value("img_proc/pre_cut/size/height",ori_img->height()).toInt();

    proc->setParams(params);

}
