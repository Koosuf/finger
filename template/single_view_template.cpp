#include "single_view_template.h"
#include "ui_singleviewtemplate.h"

SingleViewTemplate::SingleViewTemplate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleViewTemplate)
{
    ui->setupUi(this);
}

SingleViewTemplate::~SingleViewTemplate()
{
    delete ui;
}
