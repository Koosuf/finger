#include "proc_settings.h"
#include <QIntValidator>
#include <QDebug>

ProcSettings::ProcSettings(QWidget *parent) : QWidget(parent)
{
    load();
    update_from_file();
    create_view();
    setLayout(&main_layout);
}

void ProcSettings::load()
{
    /* check config file if exits */
    QString filename("/Users/taozhigang/Documents/develop/finger/config/settings.plist");
    configs = new QSettings(filename,QSettings::NativeFormat);
}

ProcSettings::~ProcSettings()
{
    if(configs)
        delete configs;

}


void ProcSettings::create_view()
{
    create_pre_cut_dialog();
    create_finger_enhance_dialog();
    main_layout.addLayout(&pre_cut_layout,0,0,3,5);
    main_layout.addLayout(&finger_enhance_layout,3,0,3,5);

    ret_box.addButton(QDialogButtonBox::Ok);
    ret_box.addButton(QDialogButtonBox::Cancel);
    main_layout.addWidget(&ret_box,6,3,1,2);
    connect(&ret_box,SIGNAL(accepted()),this,SLOT(check_Act()));
    connect(&ret_box,SIGNAL(rejected()),this,SLOT(cancel_Act()));
}

void ProcSettings::create_pre_cut_dialog()
{
    pre_cut_dialog.title.setText(tr("预裁剪"));

    pre_cut_dialog.tag_x.label.setText(tr("x"));
    pre_cut_dialog.tag_x.line.setValidator(new QIntValidator(0,320));
    pre_cut_dialog.tag_x.line.setText(QVariant(settings.pre_cut_size.x()).toString());
    pre_cut_dialog.tag_y.label.setText("y");
    pre_cut_dialog.tag_y.line.setValidator(new QIntValidator(0,240));
    pre_cut_dialog.tag_y.line.setText(QVariant(settings.pre_cut_size.y()).toString());

    pre_cut_dialog.tag_dx.label.setText(tr("dx"));
    pre_cut_dialog.tag_dx.line.setValidator(new QIntValidator(0,320));
    pre_cut_dialog.tag_dx.line.setText(QVariant(settings.pre_cut_size.width()).toString());
    pre_cut_dialog.tag_dy.label.setText("dy");
    pre_cut_dialog.tag_dy.line.setValidator(new QIntValidator(0,240));
    pre_cut_dialog.tag_dy.line.setText(QVariant(settings.pre_cut_size.height()).toString());

    pre_cut_layout.addWidget(&pre_cut_dialog.title,0,0);
    pre_cut_layout.addWidget(&pre_cut_dialog.tag_x.label,1,0);
    pre_cut_layout.addWidget(&pre_cut_dialog.tag_x.line,1,1);
    pre_cut_layout.addWidget(&pre_cut_dialog.tag_y.label,1,3);
    pre_cut_layout.addWidget(&pre_cut_dialog.tag_y.line,1,4);
    pre_cut_layout.addWidget(&pre_cut_dialog.tag_dx.label,2,0);
    pre_cut_layout.addWidget(&pre_cut_dialog.tag_dx.line,2,1);
    pre_cut_layout.addWidget(&pre_cut_dialog.tag_dy.label,2,3);
    pre_cut_layout.addWidget(&pre_cut_dialog.tag_dy.line,2,4);
}

void ProcSettings::create_finger_enhance_dialog()
{
    finger_enhance_dialog.title.setText(tr("静脉增强"));
    finger_enhance_dialog.up_thresh.label.setText(tr("上阈值"));
    finger_enhance_dialog.up_thresh.line.setValidator(new QIntValidator(-1000000,1000000));
    finger_enhance_dialog.up_thresh.line.setText(QVariant(settings.enhanced_hessian_up_thresh).toString());
    finger_enhance_dialog.down_thresh.label.setText(tr("下阈值"));
    finger_enhance_dialog.down_thresh.line.setValidator(new QIntValidator(-1000000,1000000));
    finger_enhance_dialog.down_thresh.line.setText(QVariant(settings.enhanced_hessian_down_thresh).toString());

    finger_enhance_dialog.kernerl_size.label.setText(tr("核尺寸"));
    finger_enhance_dialog.kernerl_size.line.setValidator(new QIntValidator(1,7));
    finger_enhance_dialog.kernerl_size.line.setText(QVariant(settings.enhanced_hessian_kernel_size).toString());

    finger_enhance_layout.addWidget(&finger_enhance_dialog.title,0,0);
    finger_enhance_layout.addWidget(&finger_enhance_dialog.up_thresh.label,1,0);
    finger_enhance_layout.addWidget(&finger_enhance_dialog.up_thresh.line,1,1);
    finger_enhance_layout.addWidget(&finger_enhance_dialog.down_thresh.label,1,3);
    finger_enhance_layout.addWidget(&finger_enhance_dialog.down_thresh.line,1,4);
    finger_enhance_layout.addWidget(&finger_enhance_dialog.kernerl_size.label,2,0);
    finger_enhance_layout.addWidget(&finger_enhance_dialog.kernerl_size.line,2,1);

}

void ProcSettings::update_from_ui()
{
    settings.pre_cut_size.setX(pre_cut_dialog.tag_x.line.text().toInt());
    settings.pre_cut_size.setY(pre_cut_dialog.tag_y.line.text().toInt());
    settings.pre_cut_size.setWidth(pre_cut_dialog.tag_dx.line.text().toInt());
    settings.pre_cut_size.setHeight(pre_cut_dialog.tag_dy.line.text().toInt());

    settings.enhanced_hessian_up_thresh = finger_enhance_dialog.up_thresh.line.text().toInt();
    settings.enhanced_hessian_down_thresh = finger_enhance_dialog.down_thresh.line.text().toInt();
    settings.enhanced_hessian_kernel_size = finger_enhance_dialog.kernerl_size.line.text().toInt();
}

void ProcSettings::update_to_file()
{
    configs->setValue("img_proc/pre_cut/size/x",settings.pre_cut_size.x());
    configs->setValue("img_proc/pre_cut/size/y",settings.pre_cut_size.y());
    configs->setValue("img_proc/pre_cut/size/width",settings.pre_cut_size.width());
    configs->setValue("img_proc/pre_cut/size/height",settings.pre_cut_size.height());

    configs->setValue("img_proc/finger_enhance/hessian/up_thresh", settings.enhanced_hessian_up_thresh);
    configs->setValue("img_proc/finger_enhance/hessian/down_thresh", settings.enhanced_hessian_down_thresh);
    configs->setValue("img_proc/finger_enhance/hessian/kernel_size",settings.enhanced_hessian_kernel_size);
}


void ProcSettings::update_from_file()
{
    /* update pre_cut size */
    settings.pre_cut_size.setX(configs->value("img_proc/pre_cut/size/x",0).toInt());
    settings.pre_cut_size.setY(configs->value("img_proc/pre_cut/size/y",0).toInt());
    settings.pre_cut_size.setWidth(configs->value("img_proc/pre_cut/size/width",0).toInt());
    settings.pre_cut_size.setHeight(configs->value("img_proc/pre_cut/size/height",0).toInt());

    settings.enhanced_hessian_up_thresh = configs->value("img_proc/finger_enhance/hessian/up_thresh",20000).toInt();
    settings.enhanced_hessian_down_thresh = configs->value("img_proc/finger_enhance/hessian/down_thresh",100).toInt();
    settings.enhanced_hessian_kernel_size = configs->value("img_proc/finger_enhance/hessian/kernel_size",3).toInt();
}

void ProcSettings::check_Act()
{
    update_from_ui();
    update_to_file();
    close();
}

void ProcSettings::cancel_Act()
{
    close();
}



