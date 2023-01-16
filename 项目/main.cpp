#include "notewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    noteWindow w;
    w.show();
    return a.exec();
}
