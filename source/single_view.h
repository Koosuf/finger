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

    void create_view();

public slots:
    void open_Act(void);
    void quit_Act(void);
    void proc_Act(void);
};

#endif // SINGLEVIEW_H
