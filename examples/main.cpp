#include "tstplotter.h"

#include <QtGui>
#include <QApplication>
#include <QMainWindow>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TSTPlotter w;
 
    printf("%u %u\n",18%4, 18/4);

    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    w.start();

    return a.exec();
};
