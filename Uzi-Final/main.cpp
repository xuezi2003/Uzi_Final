#include "PrePage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PrePage w;
    qDebug() << "say hello git";
    w.show();
    return a.exec();
}
