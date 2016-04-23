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
        int enhanced_hessian_up_thresh;
        int enhanced_hessian_down_thresh;
        int enhanced_hessian_kernel_size;
        int proc_vein_single_object_size;
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

    //for finger enhance
    void create_finger_enhance_dialog(void);
    QGridLayout finger_enhance_layout;
    struct FingerEnhanceDialog{
        QLabel title;
        struct input_dialog up_thresh, down_thresh, kernerl_size;
    }finger_enhance_dialog;

    //for proc vein

    void create_proc_vein_dialog(void);
    QGridLayout proc_vein_layout;
    struct ProcVeinDialog{
        QLabel title;
        struct input_dialog single_object_size;
    }proc_vein_dialog;

    QDialogButtonBox ret_box;

signals:

public slots:
    void check_Act(void);
    void cancel_Act(void);
};

#endif // PROCSETTINGS_H
