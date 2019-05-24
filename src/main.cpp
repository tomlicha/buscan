#include <QtWidgets/QApplication>
#include "mainwindow.h"
#include "can_bus_ihm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CAN_BUS_IHM w(0);
    //MainWindow w(0,300,300);
    w.show();
    return a.exec();
}
