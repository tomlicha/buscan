#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QtWidgets/QMainWindow>
#include <qgridlayout.h>
#include <objectgl.h>
#include <QMenuBar>
#include <QMessageBox>
#include <QTimer>
#include <QtCore>
#include <QDebug>
#include <libpcan.h>        // /usr/include/libpcan.h
#include <fcntl.h>    // O_RDWR
#include <signal.h>
#include <unistd.h>   // exit

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor and destructor
    MainWindow(QWidget *parent = 0, int w=600, int h=400);
    ~MainWindow();

    /*bool                    connect();

    void openCANPort();
    void sendCANMessage();
    void receiveCANMessage();
    void convertAngles();*/

protected slots:
    // Redraw the scene
   /* void                    onTimer_UpdateDisplay();
    void                    onTimer_Tick();*/

protected:

    // Overload of the resize event
    /*void                    resizeEvent(QResizeEvent *);*/

private:

/*
    HANDLE h;
    TPCANRdMsg pMsgBuff;
    // Layout of the window
    QGridLayout             *gridLayout;
    QWidget                 *gridLayoutWidget;

    // Central widget (where the openGL window is drawn)
    QWidget                 *centralWidget;

    // OpenGL object
    ObjectOpenGL            *Object_GL;

    QTimer *timer_tick;*/
};

#endif // MAINWINDOW_H
