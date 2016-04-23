#include "proc.h"
#include <stack>


s_Point::s_Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

int s_Point::get_x()
{
    return this->x;
}

int s_Point::get_y()
{
    return this->y;
}



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
    Mat ori_vein = finger_enhance(finger_img);
    Mat clear_vein = proc_vein(ori_vein);

    *img = new QImage(mat_to_qimage(clear_vein));
    return true;
}

Mat Proc::pre_cut(Mat img)
{
    return img(params.size).clone();
}

Mat Proc::take_finger(Mat img)
{
    Mat thed,tmp;
    GaussianBlur(img,tmp,Size(7,7),0,0);
    threshold(tmp,tmp,0,128,CV_THRESH_BINARY | CV_THRESH_OTSU);
    tmp.convertTo(thed,CV_8U);


    Mat dist;
    distanceTransform(thed,dist,CV_DIST_C,3);

    double min_val,max_val;
    Point min_pos, max_pos;
    minMaxLoc(dist, &min_val, &max_val, &min_pos, &max_pos);
    floodFill(thed,max_pos,255);
    threshold(thed,thed,200,255, CV_THRESH_BINARY);

    for(int i=0; i<thed.rows; i++)
    {
        if(countNonZero(thed.row(i))*1.0/thed.cols < 0.2)
        {
            std::memset((void*)thed.ptr(i),0,thed.cols);
        }
    }

    int morph_size = 3;
    Mat element = getStructuringElement(MORPH_ELLIPSE,Size(2*morph_size+1, 2*morph_size+1),Point(morph_size,morph_size));

    morphologyEx(thed,thed,MORPH_CLOSE,element,Point(-1,-1),3);

    Mat rest;
    bitwise_and(img,thed,rest);


    Mat points;
    findNonZero(rest,points);
    return rest(boundingRect(points));
}


Mat Proc::proc_vein(Mat img)
{
    Mat rest = Mat::zeros(img.rows, img.cols, CV_8U);
    Mat tmp = Mat::zeros(img.rows+2, img.cols+2, CV_8U);

    img.copyTo(tmp(Rect(1,1,img.cols,img.rows)));


    std::set<int> insp_sets;
    for(int row=1; row < tmp.rows-1; row++)
    {
        for(int col=1; col < tmp.cols-1; col++)
        {
            if(!img.at<unsigned char>(row,col))
                continue;
            std::set<int> effe_sets;
            std::stack<s_Point> insp_dock;

            insp_sets.insert(row*tmp.cols +col);
            insp_dock.push(s_Point(row,col));

            while(insp_dock.size() > 0)
            {
                s_Point odot = insp_dock.top();
                insp_dock.pop();
                effe_sets.insert(odot.get_x() * tmp.cols + odot.get_y());
                for(int i=-1; i<=1; i++)
                {
                    for(int j=-1; j<=1; j++)
                    {
                        if(i | j)
                        {
                            s_Point dot(odot.get_x()+i, odot.get_y()+j);
                            if(insp_sets.find(dot.get_x()*tmp.cols + dot.get_y()) == insp_sets.end())
                            {
                                insp_sets.insert(dot.get_x()*tmp.cols + dot.get_y());
                                if(tmp.at<unsigned char>(dot.get_x(), dot.get_y()) > 0)
                                {
                                    insp_dock.push(dot);
                                }

                            }
                        }

                    }
                }
            }

            if(effe_sets.size() > params.single_object_size)
            {
                std::set<int>::iterator it;
                for(it = effe_sets.begin(); it != effe_sets.end(); it++)
                {
                    rest.at<unsigned char>(*it/tmp.cols, *it%tmp.cols) = 255;
                }
            }
        }
    }

    return rest;

}

Mat Proc::finger_enhance(Mat img)
{
    medianBlur(img,img,3);
    GaussianBlur(img,img,Size(5,5),0);

    //calculate hession matrix
    Mat grad_xx, grad_yy, grad_xy, grad_x, grad_y;
    Scharr(img, grad_x,  CV_32F, 1, 0, params.hessian_kernel_size);
    Scharr(img, grad_y, CV_32F, 0, 1, params.hessian_kernel_size);
    Scharr(grad_x, grad_xx, CV_32F, 1, 0, params.hessian_kernel_size);
    Scharr(grad_y, grad_yy, CV_32F, 0, 1, params.hessian_kernel_size);
    Scharr(grad_x, grad_xy, CV_32F, 0, 1, params.hessian_kernel_size);

    Mat tmp;
    tmp = grad_xx.mul(grad_xx) + 4*grad_xy.mul(grad_xy) + grad_yy.mul(grad_yy) - 2*grad_xx.mul(grad_yy);
    cv::sqrt(abs(tmp),tmp);

    tmp = grad_xx + grad_yy + tmp;

    Mat vein;
    threshold(tmp,vein, params.hessian_down_thresh, 255, CV_THRESH_BINARY);

    normalize(vein,vein,0,255,NORM_MINMAX);
    vein.convertTo(vein,CV_8U);


    Mat mask;
    threshold(tmp, mask, params.hessian_up_thresh, 255, CV_THRESH_BINARY);
    mask.convertTo(mask,CV_8U);

    int morph_size = 2;
    Mat element = getStructuringElement(MORPH_ELLIPSE,Size(2*morph_size+1, 2*morph_size+1),Point(morph_size,morph_size));
    morphologyEx(mask,mask,MORPH_DILATE,element,Point(-1,-1),1);
    bitwise_not(mask,mask);

    Mat rest;
    bitwise_and(vein,mask,rest);

    Mat dist;
    distanceTransform(rest,dist,CV_DIST_L2,3);

    GaussianBlur(dist,dist,Size(3,3),1);
    threshold(dist,dist,1.5,255,CV_THRESH_BINARY);
    dist.convertTo(dist,CV_8U);
    return dist;
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


