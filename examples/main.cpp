#include "tstplotter.h"

#include <QtGui>
#include <QApplication>
#include <QMainWindow>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TSTPlotter w;
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    return a.exec();
};
