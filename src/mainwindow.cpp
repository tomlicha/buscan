#include "mainwindow.h"
#define DEFAULT_NODE "/dev/pcanusb32"
//=============================================================================================
// Constructor of the main window
// Create window properties, menu etc ...
//=============================================================================================
//float phi_rad;
//float theta_rad;
//float psi_rad;
MainWindow::MainWindow(QWidget *parent,int w, int h)
    : QMainWindow(parent)
{
    // Set the window size
    this->resize(w,h);
    this->setWindowTitle("Object viewer");

    // Create a layout in the main window
    /*centralWidget = new QWidget(this);
    gridLayoutWidget = new QWidget(centralWidget);
    gridLayoutWidget->setGeometry(QRect(0, 0, this->width(), this->height()));
    gridLayout = new QGridLayout(gridLayoutWidget);

    // Create the openGL display for the map
    Object_GL = new ObjectOpenGL(gridLayoutWidget);
    Object_GL->setObjectName(QString::fromUtf8("ObjectOpenGL"));
    Object_GL->setGeometry(QRect(0, 0, this->width(), this->height()));

    // Insert the Open Gl display into the layout
    gridLayout->addWidget(Object_GL, 0, 0, 1, 1);
    setCentralWidget(centralWidget);

    // Create the menubar
    QMenu *FileMenu = menuBar()->addMenu("&File");
    FileMenu->addSeparator();
    FileMenu->addAction("Quit", qApp, SLOT (quit()), QKeySequence(tr("Ctrl+Q")));

    // Add menu items
    QMenu *ViewMenu = menuBar()->addMenu("&View");
    ViewMenu->addAction("Front view",       Object_GL, SLOT (FrontView()),  QKeySequence(tr("Ctrl+f")));
    ViewMenu->addAction("Rear view",        Object_GL, SLOT (RearView()),   QKeySequence(tr("Ctrl+e")));
    ViewMenu->addAction("Left view",        Object_GL, SLOT (LeftView()),   QKeySequence(tr("Ctrl+l")));
    ViewMenu->addAction("Right view",       Object_GL, SLOT (RightView()),  QKeySequence(tr("Ctrl+r")));
    ViewMenu->addAction("Top view",         Object_GL, SLOT (TopView()),    QKeySequence(tr("Ctrl+t")));
    ViewMenu->addAction("Bottom view",      Object_GL, SLOT (BottomView()), QKeySequence(tr("Ctrl+b")));
    FileMenu->addSeparator();
    ViewMenu->addAction("Isometric",        Object_GL, SLOT (IsometricView()), QKeySequence(tr("Ctrl+i")));

    // Timer (used for repainting the GL Window every 50 ms)
    QTimer *timerDisplay = new QTimer();
    timerDisplay->connect(timerDisplay, SIGNAL(timeout()),this, SLOT(onTimer_UpdateDisplay()));
    timerDisplay->start(50);

    openCANPort();

    timer_tick = new QTimer();
    QWidget::connect( timer_tick, SIGNAL(timeout()), this, SLOT(onTimer_Tick()));


     timer_tick -> start(5); // in ms*/

}
//=============================================================================================
MainWindow::~MainWindow()
{}
//=============================================================================================
// On resize event, the items in the window are resized
//=============================================================================================
/*void MainWindow::resizeEvent(QResizeEvent *)
{
    Object_GL->resize(centralWidget->width(),centralWidget->height());
    gridLayoutWidget->setGeometry(QRect(0, 0, centralWidget->width(), centralWidget->height()));
}
//=============================================================================================
// Timer event : repain the Open Gl window
//=============================================================================================
void MainWindow::onTimer_UpdateDisplay()
{

    Object_GL->setAngles(phi_rad, theta_rad, psi_rad);
    Object_GL->updateGL();

}
//=============================================================================================
void MainWindow::openCANPort()
{
    const char *szDevNode = DEFAULT_NODE;

    h=LINUX_CAN_Open(szDevNode, O_RDWR);
    if (!h)
        {
            printf("can't open %s\n", szDevNode);
        }
    CAN_Init(h, CAN_BAUD_500K,  CAN_INIT_TYPE_ST);         // BTR0BTR1	bitrate code in hex (default=0x1c (500 kbps))
    CAN_Status(h); // Clear Status

}
//===============================================================
void MainWindow::sendCANMessage()
{
    TPCANMsg msgBuff;

    msgBuff.ID      =   0x4;
    msgBuff.MSGTYPE =   MSGTYPE_STANDARD;
    msgBuff.LEN     =   8;

    /*msgBuff.DATA[0] =   send_box_0->text().toInt();
    msgBuff.DATA[1] =   send_box_1->text().toInt();
    msgBuff.DATA[2] =   send_box_2->text().toInt();
    msgBuff.DATA[3] =   send_box_3->text().toInt();
    msgBuff.DATA[4] =   send_box_4->text().toInt();
    msgBuff.DATA[5] =   send_box_5->text().toInt();
    msgBuff.DATA[6] =   send_box_6->text().toInt();
    msgBuff.DATA[7] =   send_box_7->text().toInt();*/

/*
 LINUX_CAN_Write_Timeout(h, &msgBuff,0);

}
//===============================================================
void MainWindow::receiveCANMessage()
{


    LINUX_CAN_Read_Timeout(h, &pMsgBuff,1); // Timeout=1ms --> Non Bloquant

    int16_t  phi=(int16_t)(pMsgBuff.Msg.DATA[0]|pMsgBuff.Msg.DATA[1]<<8);
    phi_rad = phi;
    qDebug() << "phi " << QString::number(phi_rad);

    phi_rad=(phi_rad/10.0);

    int16_t  theta=(int16_t)(pMsgBuff.Msg.DATA[2]|pMsgBuff.Msg.DATA[3]<<8);
    theta_rad = theta;
    qDebug() << "theta " << QString::number(theta_rad);

    theta_rad= (theta_rad/10.0);

    int16_t  psi=(int16_t)(pMsgBuff.Msg.DATA[4]|pMsgBuff.Msg.DATA[5]<<8);
    psi_rad = psi;
    qDebug() << "psi " << QString::number(psi_rad);
    psi_rad=(psi_rad/10.0);


}
//===============================================================

void MainWindow::onTimer_Tick()
{
receiveCANMessage();
}

*/
