#ifndef SINGLEVIEW_H
#define SINGLEVIEW_H

#include <QWidget>
#include <QString>
#include <QImage>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <opencv2/opencv.hpp>
#include "proc.h"

using cv::Mat;

class SingleView : public QWidget
{
    Q_OBJECT
public:
     ~SingleView();
    explicit SingleView(QString img_name);

private:
    QGridLayout *main_layout;
    QLabel *img_lable;

    QImage *ori_img;
    QImage *proc_img;
    QPushButton *quit_button;
    QPushButton *proc_button;
    QPushButton *open_button;
    QPushButton *save_button;

    Proc *proc;

    void create_view();
    void set_params();

public slots:
    void open_Act(void);
    void quit_Act(void);
    void proc_Act(void);
    void save_Act(void);
};

#endif // SINGLEVIEW_H
