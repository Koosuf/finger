#ifndef PROC_H
#define PROC_H

/* This class has nothind to do with qt */

#include <opencv2/opencv.hpp>

#include <iostream>

using std::cout;
using std::endl;

using namespace cv;

class Proc
{
public:
    Proc(string filename);
    ~Proc();

    struct Params{
        Rect size;
    };

    bool run(Mat &img);
    void reset_img(String filename);
    void setParams(struct Params remote_params);
    struct Params params;

private:
    Mat src_img;
    bool hasInit = false;

    Mat pre_cut(Mat img);
};

#endif // PROC_H
