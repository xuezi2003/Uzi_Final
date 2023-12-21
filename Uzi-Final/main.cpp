#include "PrePage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PrePage w;
    w.show();
    return a.exec();
}
