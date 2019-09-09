#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>
#include <QMouseEvent>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = 0);

protected:
   virtual void mousePressEvent(QMouseEvent *event);

signals:
    void clicked(void); // 声明鼠标左击中信号

};

#endif // MYLABEL_H
