#include "proc.h"

Proc::Proc(string filename)
{
    src_img = cv::imread(filename,CV_LOAD_IMAGE_GRAYSCALE);
}


Proc::~Proc()
{

}

void Proc::reset_img(string filename)
{
    src_img = cv::imread(filename,CV_LOAD_IMAGE_GRAYSCALE);
}

void Proc::setParams(Params remote_params)
{
    params = remote_params;
    hasInit = true;
}

bool Proc::run(Mat &img)
{
    if(src_img.empty() || !hasInit)
        return false;

    img = pre_cut(src_img);
    return true;
}

Mat Proc::pre_cut(Mat img)
{

}

