#include "mainwindow.h"

#include <QApplication>

// MVC in Qt is just MV (View & controller are merged together).
// Separated Controller is not necessary (Signals & Slots are sufficient)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
