#include "tks.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tKS w;
    w.show();

    return a.exec();
}
