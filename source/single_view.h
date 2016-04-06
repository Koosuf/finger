#ifndef SINGLEVIEW_H
#define SINGLEVIEW_H

#include <QWidget>
#include <QString>
#include <QImage>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class SingleView : public QWidget
{
    Q_OBJECT
public:
    explicit SingleView(QWidget *parent = 0);
     ~SingleView();
    explicit SingleView(QString img_name);

    void create_view();
    void set_mainwindow_pointer(QMainWindow *pointer);



private:

    QMainWindow *mainwindow;
    QGridLayout *main_layout;
    QLabel *img_lable;

    QImage *ori_img;
    QImage *proc_img;
    QPushButton *quit_button;
    QPushButton *proc_button;

signals:

public slots:
};

#endif // SINGLEVIEW_H
