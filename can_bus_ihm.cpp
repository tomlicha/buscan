#include "can_bus_ihm.h"
#include "ui_can_bus_ihm.h"
#define MPU950 0
#define VL6180x 1
#define DEFAULT_NODE "/dev/pcanusb32"
float phi_rad;
float theta_rad;
float psi_rad;
int vl_data;

CAN_BUS_IHM::CAN_BUS_IHM(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CAN_BUS_IHM)
{
    ui->setupUi(this);
    // Set the window size
    this->setWindowTitle("Object viewer");
    //init angles
    phi_rad=0;theta_rad=0;psi_rad=0;
    // Create a layout in the main window
    centralWidget = new QWidget(this);
    gridLayoutWidget = new QWidget(centralWidget);
    gridLayoutWidget->setGeometry(QRect(0, 0, this->width(), this->height()));
    gridLayout = new QGridLayout(gridLayoutWidget);

    // Create the openGL display for the map
    Object_GL = new ObjectOpenGL(gridLayoutWidget);
    Object_GL->setObjectName(QString::fromUtf8("ObjectOpenGL"));
    Object_GL->setGeometry(QRect(0, 0, this->width(), this->height()));
    //GAUGE
    mSpeedGauge = new QcGaugeWidget;
    mSpeedGauge->addBackground(99);
    QcBackgroundItem *bkg1 = mSpeedGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
    bkg1->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg2 = mSpeedGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1,Qt::gray);
    bkg2->addColor(1.0,Qt::darkGray);

    mSpeedGauge->addArc(55);
    mSpeedGauge->addDegrees(65)->setValueRange(0,255);
    mSpeedGauge->addColorBand(50);

    mSpeedGauge->addValues(80)->setValueRange(0,255);

    mSpeedGauge->addLabel(70)->setText("Km/h");
    QcLabelItem *lab = mSpeedGauge->addLabel(40);
    lab->setText("0");
    mSpeedNeedle = mSpeedGauge->addNeedle(255);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::white);
    mSpeedNeedle->setValueRange(0,255);
    mSpeedGauge->addBackground(7);
    mSpeedGauge->addGlass(88);
    ui->verticalLayout->addWidget(mSpeedGauge);

    // Insert the Open Gl display into the layout
    ui->radian_button->setChecked(true);
    ui->degree_buttton->setChecked(false);
    ui->layout_open_gl->addWidget(Object_GL);
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


     timer_tick -> start(1/*5*/); // in ms
}

CAN_BUS_IHM::~CAN_BUS_IHM()
{
    delete ui;
}

void CAN_BUS_IHM::resizeEvent(QResizeEvent *)
{
    Object_GL->resize(centralWidget->width(),centralWidget->height());
    gridLayoutWidget->setGeometry(QRect(0, 0, centralWidget->width(), centralWidget->height()));
}
//=============================================================================================
// Timer event : repain the Open Gl window
//=============================================================================================
void CAN_BUS_IHM::onTimer_UpdateDisplay()
{

    Object_GL->setAngles(phi_rad, theta_rad, psi_rad);
    Object_GL->updateGL();

}
//=============================================================================================
void CAN_BUS_IHM::openCANPort()
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
void CAN_BUS_IHM::sendCANMessage()
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


 LINUX_CAN_Write_Timeout(h, &msgBuff,0);

}
//===============================================================
void CAN_BUS_IHM::receiveCANMessage()
{


    LINUX_CAN_Read_Timeout(h, &pMsgBuff,1); // Timeout=1ms --> Non Bloquant
if (pMsgBuff.Msg.ID==1){

    int16_t  phi=(int16_t)(pMsgBuff.Msg.DATA[0]|pMsgBuff.Msg.DATA[1]<<8);
    phi_rad = phi;
    //qDebug() << "phi " << QString::number(phi_rad);

    phi_rad=(phi_rad/10.0);


    int16_t  theta=(int16_t)(pMsgBuff.Msg.DATA[2]|pMsgBuff.Msg.DATA[3]<<8);
    theta_rad = theta;
    //qDebug() << "theta " << QString::number(theta_rad);

    theta_rad= (theta_rad/10.0);

    int16_t  psi=(int16_t)(pMsgBuff.Msg.DATA[4]|pMsgBuff.Msg.DATA[5]<<8);
    psi_rad = psi;
   // qDebug() << "psi " << QString::number(psi_rad);
    psi_rad=(psi_rad/10.0);
    if(ui->radian_button->isChecked()){
        ui->phi_display->display(phi*3.14/180);
        ui->theta_display->display(theta*3.14/180);
        ui->psi_display->display(psi*3.14/180);
    }
    else {
        ui->phi_display->display(phi/10);
        ui->theta_display->display(theta/10);
        ui->psi_display->display(psi/10);
    }

}

else if (pMsgBuff.Msg.ID == 3){

    vl_data=pMsgBuff.Msg.DATA[0]|(pMsgBuff.Msg.DATA[1]<<8)|(pMsgBuff.Msg.DATA[2]<<16)|(pMsgBuff.Msg.DATA[3]<<24);

    bool state=pMsgBuff.Msg.DATA[4];
    //on recoie un bool pour decrire l'état du switch
    //0 pour lumiere
    //1 pour distance
    if(state){
        ui->distance_display->setEnabled(true);
        ui->distance_label->setEnabled(true);
        ui->luminosite_display->setEnabled(false);
        ui->luminosite_label->setEnabled(false);
        ui->distance_display->display(float(vl_data/10));
    }
    else if(!state){
        ui->distance_display->setEnabled(false);
        ui->distance_label->setEnabled(false);
        ui->luminosite_display->setEnabled(true);
        ui->luminosite_label->setEnabled(true);
        ui->luminosite_display->display(vl_data);
    }
        //mSpeedNeedle->setCurrentValue(vl_data);
}
else if (pMsgBuff.Msg.ID == 2){
    int speed=pMsgBuff.Msg.DATA[0];
    mSpeedNeedle->setCurrentValue(speed);
}
else if (pMsgBuff.Msg.ID == 4){
    int pressure=pMsgBuff.Msg.DATA[0];
    ui->pression_display->display(pressure);
}
}
//===============================================================

void CAN_BUS_IHM::onTimer_Tick()
{
receiveCANMessage();
}
