#ifndef PROC_H
#define PROC_H

/* This class has nothind to do with qt */

#include <opencv2/opencv.hpp>
#include <QImage>

#include <iostream>

using std::cout;
using std::endl;

using namespace cv;

class Proc
{
public:
    Proc(QImage img);
    ~Proc();

    struct Params{
        Rect size;
        int hessian_up_thresh;
        int hessian_down_thresh;
        int hessian_kernel_size;
    };

    bool run(QImage **img);
    void reset_img(QImage *img);
    void setParams(struct Params remote_params);
    struct Params params;

    //tools
    QImage mat_to_qimage(Mat img);
    Mat qimage_to_mat(QImage img);

private:
    Mat src_img;
    bool hasInit = false;

    Mat pre_cut(Mat img);
    Mat take_finger(Mat img);
    Mat finger_enhance(Mat img);
};

#endif // PROC_H
