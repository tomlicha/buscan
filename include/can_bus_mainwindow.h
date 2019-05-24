#ifndef CAN_BUS_MAINWINDOW_H
#define CAN_BUS_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class CAN_BUS_MainWindow;
}

class CAN_BUS_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CAN_BUS_MainWindow(QWidget *parent = 0);
    ~CAN_BUS_MainWindow();

private:
    Ui::CAN_BUS_MainWindow *ui;
};

#endif // CAN_BUS_MAINWINDOW_H
