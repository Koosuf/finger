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

    Mat cut_img = pre_cut(src_img);
    Mat finger_img = take_finger(cut_img);

    *img = new QImage(mat_to_qimage(finger_img));
    return true;
}

Mat Proc::pre_cut(Mat img)
{
    return img(params.size).clone();
}

Mat Proc::take_finger(Mat img)
{
    Mat thed,tmp;
    threshold(img,tmp,0,128,CV_THRESH_BINARY | CV_THRESH_OTSU);
    tmp.convertTo(thed,CV_8U);

    for(int i=0; i<thed.rows; i++)
    {
        if(countNonZero(thed.row(i))*1.0/thed.cols < 0.2)
        {
            std::memset((void*)thed.ptr(i),0,thed.cols);
        }
    }

    Mat dist;
    distanceTransform(thed,dist,CV_DIST_C,3);
    threshold(dist,dist,20,255,CV_THRESH_BINARY);

    double min_val,max_val;
    Point min_pos, max_pos;
    minMaxLoc(dist, &min_val, &max_val, &min_pos, &max_pos);
    floodFill(thed,max_pos,255);
    threshold(thed,thed,200,255, CV_THRESH_BINARY);

    int morph_size = 3;
    Mat element = getStructuringElement(MORPH_ELLIPSE,Size(2*morph_size+1, 2*morph_size+1),Point(morph_size,morph_size));

    morphologyEx(thed,thed,MORPH_DILATE,element);

    Mat rest;
    bitwise_and(img,thed,rest);

    return rest;
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

