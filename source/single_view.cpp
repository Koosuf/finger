#include "single_view.h"
#include <QFileInfo>
#include <QPushButton>
#include <QDialogButtonBox>

SingleView::SingleView(QWidget *parent) : QWidget(parent)
{

}

SingleView::SingleView(QString img_name)
{
    QFileInfo check_file(img_name);
    if(!check_file.exists() || !check_file.isFile())
        img_name = "../../../../resource/default.png";
    ori_img = new QImage(img_name);
    create_view();
    this->setLayout(main_layout);
    show();
}


SingleView::~SingleView()
{
    if(!ori_img)
        delete ori_img;
    if(!proc_img)
        delete proc_img;
}

void SingleView::create_view()
{
    main_layout = new QGridLayout(this);

    img_lable = new QLabel(this);
    img_lable->setFixedSize(320,240);
    img_lable->setPixmap(QPixmap::fromImage(*ori_img));
    main_layout->addWidget(img_lable,0,0,1,4);

    quit_button = new QPushButton(tr("&quit"));
    quit_button->setDefault(true);
    quit_button->setAutoFillBackground(true);
    main_layout->addWidget(quit_button,1,1);

    proc_button = new QPushButton(tr("&proc"));
    proc_button->setDefault(true);
    main_layout->addWidget(proc_button,1,2);

}
