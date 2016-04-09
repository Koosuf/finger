#include "proc.h"

Proc::Proc(QImage img)
{
    src_img = qimage_to_mat(img);
}


Proc::~Proc()
{

}

void Proc::reset_img(QImage *img)
{
    src_img = qimage_to_mat(*img);
}

void Proc::setParams(Params remote_params)
{
    params = remote_params;
    hasInit = true;
}

bool Proc::run(QImage **img)
{
    if(src_img.empty() || !hasInit)
        return false;
    if(*img)
    {
        delete *img;
        *img = NULL;
    }

    *img = new QImage(mat_to_qimage(pre_cut(src_img)));
    return true;
}

Mat Proc::pre_cut(Mat img)
{
    return img(params.size).clone();
}

Mat Proc::take_finger(Mat img)
{

}


Mat Proc::qimage_to_mat(QImage img)
{
    Mat tmp(img.height(),img.width(),CV_8UC1,(uchar*)img.bits(),img.bytesPerLine());
    return tmp;
}

QImage Proc::mat_to_qimage(Mat img)
{
    QImage tmp((const uchar *) img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
    tmp.bits();
    return tmp;
}

