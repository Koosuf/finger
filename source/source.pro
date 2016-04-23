#-------------------------------------------------
#
# Project created by QtCreator 2016-03-31T17:24:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


INCLUDEPATH += /usr/local/Cellar/opencv/2.4.12_2/include
LIBS += -L/usr/local/Cellar/opencv/2.4.12_2/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
TARGET = source
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    single_view.cpp \
    qt_test.cpp \
    proc_settings.cpp \
    proc.cpp

HEADERS  += mainwindow.h \
    single_view.h \
    qt_test.h \
    proc_settings.h \
    proc.h
