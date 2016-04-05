#ifndef SINGLEVIEW_H
#define SINGLEVIEW_H

#include <QWidget>
#include <QString>
#include <QImage>


class SingleView : public QWidget
{
    Q_OBJECT
public:
    explicit SingleView(QWidget *parent = 0);
    explicit SingleView(QString img_name);

    bool create_layout();

private:

    QImage *ori_img;
    QImage *proc_img;

signals:

public slots:
};

#endif // SINGLEVIEW_H
