#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif
#ifndef WIDGET_OP_H
#define WIDGET_OP_H
#include <QWidget>
#include <QImage>
#include <QLabel>

#include "mylabel.h"
#include <opencv2/opencv.hpp>

namespace Ui {
class Widget_op;
}

class Widget_op : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_op(QWidget *parent = 0);
    ~Widget_op();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_myLabel_1_clicked();

    void on_myLabel_2_clicked();

private:
    Ui::Widget_op *ui;

private:
    QImage MatToQImage(const cv::Mat& mat);
    void display_MatInQT(QLabel* label,cv::Mat mat);

private:
     cv::Mat mat_origin;
     cv::Mat mat_logo;
     cv::Mat mat_add;
     cv::Mat mat_Gaussian;
};

#endif // WIDGET_OP_H
