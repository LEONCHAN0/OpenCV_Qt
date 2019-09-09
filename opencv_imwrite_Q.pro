#-------------------------------------------------
#
# Project created by QtCreator 2019-08-29T10:43:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencv_imwrite_Q
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        Widget_op.cpp \
    mylabel.cpp

HEADERS  += \
    mylabel.h \
    Widget_op.h

FORMS    += Widget_op.ui

# disable C4819 warning
QMAKE_CXXFLAGS_WARN_ON += -wd4819

#Opencv Configuration

INCLUDEPATH+= D:\opencv-3.1.0\opencv\build\include

win32:CONFIG(release, debug|release): LIBS += -LD:/opencv-3.1.0/opencv/build/x64/vc12/lib/ -lopencv_world310
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/opencv-3.1.0/opencv/build/x64/vc12/lib/ -lopencv_world310d
else:unix: LIBS += -LD:/opencv-3.1.0/opencv/build/x64/vc12/lib/ -lopencv_world310

INCLUDEPATH += D:/opencv-3.1.0/opencv/build/x64/vc12
DEPENDPATH += D:/opencv-3.1.0/opencv/build/x64/vc12

