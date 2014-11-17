#include "samplewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SampleWindow w;
    w.show();

    return a.exec();
}
