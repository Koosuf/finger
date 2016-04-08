#ifndef PROCSETTINGS_H
#define PROCSETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QRect>
#include <QWidget>
#include <QPushButton>


class ProcSettings : public QWidget
{
    Q_OBJECT
public:
    explicit ProcSettings(QWidget *parent = 0);
    ~ProcSettings();

    struct Settings{
        QRect pre_cut_size;
    }settings;

    struct input_dialog{
        QLabel label;
        QLineEdit line;
    };

    QSettings *configs;

private:
    void create_view(void);
    void load(void);
    void update_from_file(void);
    void update_from_ui(void);
    void update_to_file(void);



    QGridLayout main_layout;


    //for pre cut
    void create_pre_cut_dialog(void);
    QGridLayout pre_cut_layout;
    struct PreCutDialog{
        QLabel title;
        struct input_dialog tag_x, tag_y, tag_dx, tag_dy;
    }pre_cut_dialog;

    QDialogButtonBox ret_box;

signals:

public slots:
    void check_Act(void);
    void cancel_Act(void);
};

#endif // PROCSETTINGS_H
