#include "Widget_op.h"
#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget_op w;
    w.show();

    return a.exec();
}
