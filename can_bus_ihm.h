#ifndef CAN_BUS_IHM_H
#define CAN_BUS_IHM_H

#include <QMainWindow>
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
#include "qcgaugewidget.h"

namespace Ui {
class CAN_BUS_IHM;
}

class CAN_BUS_IHM : public QMainWindow
{
    Q_OBJECT

public:
        explicit CAN_BUS_IHM(QWidget *parent = 0);
        ~CAN_BUS_IHM();
        bool                    connect();

        void openCANPort();
        void sendCANMessage();
        void receiveCANMessage();
        void convertAngles();

    protected slots:
        // Redraw the scene
        void                    onTimer_UpdateDisplay();
        void                    onTimer_Tick();

    protected:

        // Overload of the resize event
        void                    resizeEvent(QResizeEvent *);

    private:


        HANDLE h;
        TPCANRdMsg pMsgBuff;
        // Layout of the window
        QGridLayout             *gridLayout;
        QWidget                 *gridLayoutWidget;

        // Central widget (where the openGL window is drawn)
        QWidget                 *centralWidget;

        // OpenGL object
        ObjectOpenGL            *Object_GL;

        QTimer *timer_tick;
        QcGaugeWidget *mSpeedGauge;
         QcNeedleItem *mSpeedNeedle;

private:
    Ui::CAN_BUS_IHM *ui;
};

#endif // CAN_BUS_IHM_H
