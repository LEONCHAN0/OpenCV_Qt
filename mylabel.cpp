#include "mylabel.h"
#include <QMessageBox>

myLabel::myLabel(QWidget *parent):QLabel(parent)
{

}

void myLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
          emit clicked();	// 发射信号
    }
}
