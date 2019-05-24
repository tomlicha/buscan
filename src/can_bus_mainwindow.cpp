#include "can_bus_mainwindow.h"
#include "ui_can_bus_mainwindow.h"

CAN_BUS_MainWindow::CAN_BUS_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CAN_BUS_MainWindow)
{
    ui->setupUi(this);
}

CAN_BUS_MainWindow::~CAN_BUS_MainWindow()
{
    delete ui;
}
