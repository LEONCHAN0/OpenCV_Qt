#include "Widget_op.h"
#include "ui_Widget_op.h"

#include <QFileDialog>
#include <QMessageBox>

using namespace cv;

Widget_op::Widget_op(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_op)
{
    ui->setupUi(this);

    // 关联信号和槽
    QObject::connect(ui->label_1, &myLabel::clicked, this, &Widget_op::on_myLabel_1_clicked);
    QObject::connect(ui->label_2, &myLabel::clicked, this, &Widget_op::on_myLabel_2_clicked);

    // 窗口固定尺寸
    this->setFixedSize(900,675);
    //设置窗口的标题栏只有关闭、最小化的按钮
    // 置顶窗口，不抢焦点
    this->setWindowFlags(Qt::WindowCloseButtonHint |Qt::WindowMinimizeButtonHint |Qt::WindowStaysOnTopHint);

    ui->label_1->setText(tr("点击加载图片..."));
    ui->label_1->setFont(QFont("微软雅黑",20,QFont::Bold,true));
    ui->label_1->setStyleSheet("color:blue; background-color:lightGray;");//设置文本颜色+背景颜色(前景色)

    ui->label_2->setText(tr("点击加载图片..."));
    ui->label_2->setFont(QFont("微软雅黑",20,QFont::Bold,true));
    ui->label_2->setStyleSheet("color:blue; background-color:lightGray;");//设置文本颜色+背景颜色(前景色)

    ui->label_3->setStyleSheet("background-color:lightGray;");
    ui->label_4->setStyleSheet("background-color:lightGray;");

    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);

}

Widget_op::~Widget_op()
{
    delete ui;
}

// Mat转QImage
QImage Widget_op::MatToQImage(const cv::Mat& mat)
{

    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, (int)mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        //qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, (int)mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        //qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }

}

// MAT 显示于 QT
void Widget_op::display_MatInQT(QLabel* label,Mat mat)
{

   label->setPixmap(QPixmap::fromImage(MatToQImage(mat)).scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

// 打开显示 mat_1
void Widget_op::on_pushButton_1_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("文件对话框"),"F:/C++/2. OPENCV 3.1.0/opencv_imwrite_Q", tr("图片文件(*.png *.jpg *.jpeg *.bmp *.tif *.tiff);;所有文件(*)"));
    if(!fileName.isEmpty())
    {
        mat_origin= imread(fileName.toLocal8Bit().data());

        if(mat_origin.data)
        {
            // 通过 lable 方式显示图片
            display_MatInQT( ui->label_1,mat_origin);
        }
        else
        {
            QMessageBox::information(this, tr("提示"),tr("未成功载入图片！"), QMessageBox::Ok);
        }
    }
}

// 打开显示 mat_2
void Widget_op::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("文件对话框"),"F:/C++/2. OPENCV 3.1.0/opencv_imwrite_Q", tr("图片文件(*.png *.jpg *.jpeg *.bmp *.tif *.tiff);;所有文件(*)"));
    if(!fileName.isEmpty())
    {
         mat_logo = imread(fileName.toLocal8Bit().data(),1); // 总是转换图像到彩色图，在返回
        if(mat_logo.data)
        {
            display_MatInQT( ui->label_2,mat_logo);
        }
        else
        {
            QMessageBox::information(this, tr("提示"),tr("未成功载入图片！"), QMessageBox::Ok);
        }
     }

    if(mat_origin.data&&mat_logo.data)
     {
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
    }
}

// 混合 mat_1和mat_2 并显示
void Widget_op::on_pushButton_3_clicked()
{
    if(!mat_add.data)
    {
        if(mat_origin.data&&mat_logo.data)
         {
            mat_add=mat_origin.clone();
            Mat imageROI = mat_add(Rect(800, 350, mat_logo.cols,mat_logo.rows));
            // 加权混合
            if(imageROI.type()==mat_logo.type())
            {
                addWeighted(imageROI, 0.5, mat_logo, 0.3, 0.0, imageROI);
                display_MatInQT(ui->label_3,mat_add);
            }
            else
            {
                 QMessageBox::information(this, tr("提示"),tr("类型不同，无法混合！"), QMessageBox::Ok);
            }
            ui->pushButton_4->setEnabled(true);
        }
        else
        {
            QMessageBox::critical(this, tr("错误"),tr("未成功载入Mat1和Mat2！"), QMessageBox::Ok);
        }
    }
}

// 图像处理：高斯滤波（模糊）
void Widget_op::on_pushButton_5_clicked()
{
    if(!mat_Gaussian.data)
    {
        if(mat_add.data)
        {
            // 高斯模糊
            GaussianBlur(mat_add,mat_Gaussian,Size(29,29),0,0);
            display_MatInQT(ui->label_4,mat_Gaussian);
        }
        else
        {
            QMessageBox::information(this, tr("提示"),tr("未成功载入加权混合图片！"), QMessageBox::Ok);
        }
    }
}

// 保存文件
void Widget_op::on_pushButton_4_clicked()
{
    if(mat_add.data)
    {
       QString filename = QFileDialog::getSaveFileName(this,tr("保存对话框"),"F:/C++/2. OPENCV 3.1.0/opencv_imwrite_Q",tr("*.jpg;; *.bmp;; *.png;; *.tif;; *.GIF"));
       if(!filename.isEmpty())
       {
         imwrite(filename.toLocal8Bit().data(),mat_add);
       }
    }
    else
    {
        QMessageBox::information(this, tr("提示"),tr("未处理完图片！"), QMessageBox::Ok);
    }
}

// 点击标签1
void Widget_op::on_myLabel_1_clicked()
{
    // 触发 按钮1 点击事件
    ui->pushButton_1->click();
}

// 点击标签2
void Widget_op::on_myLabel_2_clicked()
{
    // 触发 按钮2 点击事件
    ui->pushButton_2->click();
}
