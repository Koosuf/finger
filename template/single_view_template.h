#ifndef SINGLE_VIEW_TEMPLATE_H
#define SINGLE_VIEW_TEMPLATE_H

#include <QWidget>

namespace Ui {
class SingleViewTemplate;
}

class SingleViewTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit SingleViewTemplate(QWidget *parent = 0);
    ~SingleViewTemplate();

private:
    Ui::SingleViewTemplate *ui;
};

#endif // SINGLE_VIEW_TEMPLATE_H
