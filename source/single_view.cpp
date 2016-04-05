#include "single_view.h"
#include <QFileInfo>


SingleView::SingleView(QWidget *parent) : QWidget(parent)
{

}

SingleView::SingleView(QString img_name)
{
    QFileInfo check_file(img_name);
    if(check_file.exists() && check_file.isFile())

}
