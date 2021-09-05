#include "plotwindow.h"
#include "ui_plotwindow.h"
#include <TimeRelayFuncA.h>
#include <TimeRelayFuncB.h>
#include <Relay.h>
#include "userdata.h"
#include <QString>

/*Defined in main.cpp*/
extern ResultsData Skt0140;           //Backup Post Lube OFF cycle
extern ResultsData Skt0141;           //Backup Posl lube continuous
extern ResultsData Skt0142;           //Total postlube
extern ResultsData Skt0143;           //Backup Post Lube ON cycle
extern ResultsData Skt0145;           //Fire detected rolldown lube
extern ResultsData Skt0144;           //Header pressure high Backup pump off

extern ResultsData Ska0131;           //Controller active
extern ResultsData Ska0141;           //Controller active
extern ResultsData Ska0132;           //Controller active
extern ResultsData Ska0133;           //Post lube not required
extern ResultsData Ska0134;           //Backup command off
extern ResultsData Ska0135;           //AC PRE/POST pump drive
extern ResultsData Ska0136;           //Lube oil header pressure high
extern ResultsData Ska0137;           //Lube pump inhibit
extern ResultsData Ska0138;           //Backup lube oil pump off
extern ResultsData Ska0244;           //No fire detected
extern TimeRelayFuncA kt0140;           //Backup Post Lube OFF cycle
extern TimeRelayFuncA kt0141;           //Backup Posl lube continuous
extern TimeRelayFuncA kt0142;           //Total postlube
extern TimeRelayFuncA kt0143;           //Backup Post Lube ON cycle
extern TimeRelayFuncA kt0145;           //Fire detected rolldown lube
extern TimeRelayFuncB kt0144;           //Header pressure high Backup pump off
extern Relay ka0131;                   //Controller active
extern Relay ka0141;                   //Controller active
extern Relay ka0132;                   //Controller active
extern Relay ka0133;                   //Post lube not required
extern Relay ka0134;                   //Backup command off
extern Relay ka0135;               //AC PRE/POST pump drive
extern Relay ka0136;               //Lube oil header pressure high
extern Relay ka0137;               //Lube pump inhibit
extern Relay ka0138;               //Backup lube oil pump off
extern Relay ka0244;               //No fire detected

extern QVector<double>dbltime;

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
    Left = new QShortcut (this); Left->setKey(Qt::Key_Left);
    connect(Left, SIGNAL(activated()),this,SLOT(slotKeyPressedLeft()));

    Right= new QShortcut (this); Right->setKey(Qt::Key_Right);
    connect(Right, SIGNAL(activated()),this,SLOT(slotKeyPressedRight()));

    PgUp= new QShortcut (this); PgUp->setKey(Qt::Key_PageUp);
    connect(PgUp, SIGNAL(activated()),this,SLOT(slotKeyPressedPgUp()));

    PgDown= new QShortcut (this); PgDown->setKey(Qt::Key_PageDown);
    connect(PgDown, SIGNAL(activated()),this,SLOT(slotKeyPressedPgDown()));
}


PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::on_pltBtn_clicked()
{
/*Backup pump Run plot*/
  /*Adding and setting graph*/
    ui->pltBUpumpRun->addGraph();
    ui->pltBUpumpRun->graph(0)->setData(dbltime, Ska0138.dblEnable);
    ui->pltBUpumpRun->xAxis->setLabel("time");
    ui->pltBUpumpRun->yAxis->setLabel("Backup \n pump");
  /* set axes ranges, so we see all data*/
    ui->pltBUpumpRun->xAxis->setRange(0, UserData::timer_main_sec*1.1);
    ui->pltBUpumpRun->yAxis->setRange(0, 2);
    ui->pltBUpumpRun->yAxis->ticker()->setTickCount(2);
  /* configure left axis text labels*/
    QSharedPointer<QCPAxisTickerText> textTickerPump(new QCPAxisTickerText);
    textTickerPump->addTick(0, "RUN");
    textTickerPump->addTick(1, "STOPPED");
    ui->pltBUpumpRun->yAxis->setTicker(textTickerPump);

  /* Initialize the router*/
          tracerBUpump = new QCPItemTracer(ui->pltBUpumpRun);
          tracerBUpump->setStyle(QCPItemTracer::tsNone);//If you only want to use the tracer position as an anchor for other items, set style to tsNone.
          tracerBUpump->setGraph(ui->pltBUpumpRun->graph(0));

/*PRE/POST pump Run plot*/
    ui->pltACpumpRun->addGraph();
    ui->pltACpumpRun->graph(0)->setData(dbltime, Ska0135.dblEnable);
    ui->pltACpumpRun->xAxis->setLabel("time");
    ui->pltACpumpRun->yAxis->setLabel("AC \n pump");
  // set axes ranges, so we see all data:
    ui->pltACpumpRun->xAxis->setRange(0, UserData::timer_main_sec*1.1);
    ui->pltACpumpRun->yAxis->setRange(0, 2);
    ui->pltACpumpRun->yAxis->ticker()->setTickCount(2);
  // configure left axis text labels:
    ui->pltACpumpRun->yAxis->setTicker(textTickerPump);

    /* Initialize the router*/
            tracerACpump = new QCPItemTracer(ui->pltACpumpRun);
            tracerACpump->setStyle(QCPItemTracer::tsNone);//If you only want to use the tracer position as an anchor for other items, set style to tsNone.
            tracerACpump->setGraph(ui->pltACpumpRun->graph(0));

/*Header Pressure High plot*/
    ui->pltHeaderPressureHi->addGraph();
    ui->pltHeaderPressureHi->graph(0)->setData(dbltime, Ska0136.dblEnable);
    ui->pltHeaderPressureHi->xAxis->setLabel("time");
    ui->pltHeaderPressureHi->yAxis->setLabel("Header \n pressure");
  // set axes ranges, so we see all data:
    ui->pltHeaderPressureHi->xAxis->setRange(0, UserData::timer_main_sec*1.1);
    ui->pltHeaderPressureHi->yAxis->setRange(0, 2);
    ui->pltHeaderPressureHi->yAxis->ticker()->setTickCount(2);
  // configure left axis text labels:
    QSharedPointer<QCPAxisTickerText> textTickerHead(new QCPAxisTickerText);
    textTickerHead->addTick(0, "          LOW");
    textTickerHead->addTick(1, "        HIGH");
    ui->pltHeaderPressureHi->yAxis->setTicker(textTickerHead);

    /* Initialize the router*/
            tracerHeaderPr= new QCPItemTracer(ui->pltHeaderPressureHi);
            tracerHeaderPr->setStyle(QCPItemTracer::tsNone);//If you only want to use the tracer position as an anchor for other items, set style to tsNone.
            tracerHeaderPr->setGraph(ui->pltHeaderPressureHi->graph(0));

/*Fire Detected*/
    ui->pltFireDetected->addGraph();
    ui->pltFireDetected->graph(0)->setData(dbltime, Ska0244.dblEnable);
    ui->pltFireDetected->xAxis->setLabel("time");
    ui->pltFireDetected->yAxis->setLabel("No fire \n detected");
  // set axes ranges, so we see all data:
    ui->pltFireDetected->xAxis->setRange(0, UserData::timer_main_sec*1.1);
    ui->pltFireDetected->yAxis->setRange(0, 2);
    ui->pltFireDetected->yAxis->ticker()->setTickCount(2);
  // configure left axis text labels:
    QSharedPointer<QCPAxisTickerText> textTickerFire(new QCPAxisTickerText);
    textTickerFire->addTick(0, "        FIRE");
    textTickerFire->addTick(1, "   NO FIRE");
    ui->pltFireDetected->yAxis->setTicker(textTickerFire);

    /* Initialize the router*/
            tracerFire= new QCPItemTracer(ui->pltFireDetected);
            tracerFire->setStyle(QCPItemTracer::tsNone);//If you only want to use the tracer position as an anchor for other items, set style to tsNone.
            tracerFire->setGraph(ui->pltFireDetected->graph(0));

/*set up vertical line to be used for movement along the graph*/
    /*taken from https://evileg.com/en/post/94/*/
      verticalLineBUpump = new QCPCurve(ui->pltBUpumpRun->xAxis, ui->pltBUpumpRun->yAxis);
      verticalLineACpump = new QCPCurve(ui->pltACpumpRun->xAxis, ui->pltACpumpRun->yAxis);
      verticalLineHeader= new QCPCurve(ui->pltHeaderPressureHi->xAxis, ui->pltHeaderPressureHi->yAxis);
      verticalLineFire= new QCPCurve(ui->pltFireDetected->xAxis, ui->pltFireDetected->yAxis);
      QPen pen(Qt::red); pen.setWidth(2);
      verticalLineBUpump->setPen(pen); verticalLineACpump->setPen(pen); verticalLineHeader->setPen(pen); verticalLineFire->setPen(pen);

      connect(ui->pltBUpumpRun, &QCustomPlot::mousePress, this, &PlotWindow::slotMousePress);
      connect(ui->pltBUpumpRun, &QCustomPlot::mouseMove, this, &PlotWindow::slotMouseMove);

      connect(ui->pltACpumpRun, &QCustomPlot::mousePress, this, &PlotWindow::slotMousePress);
      connect(ui->pltACpumpRun, &QCustomPlot::mouseMove, this, &PlotWindow::slotMouseMove);

      connect(ui->pltHeaderPressureHi, &QCustomPlot::mousePress, this, &PlotWindow::slotMousePress);
      connect(ui->pltHeaderPressureHi, &QCustomPlot::mouseMove, this, &PlotWindow::slotMouseMove);

      connect(ui->pltFireDetected, &QCustomPlot::mousePress, this, &PlotWindow::slotMousePress);
      connect(ui->pltFireDetected, &QCustomPlot::mouseMove, this, &PlotWindow::slotMouseMove);
    /* creating a vector for the vertical line*/
      QVector<double> x(2) , y(2);
          x[0] = UserData::timer_main_sec/2;
          coordX= UserData::timer_main_sec/2;
          y[0] = 0;
          x[1] = UserData::timer_main_sec/2;
          y[1] = 2;
          verticalLineBUpump->setName("Vertical");      // Set its name
          verticalLineBUpump->setData(x, y);            // And sets the coordinates
          verticalLineACpump->setName("Vertical");      // Set its name
          verticalLineACpump->setData(x, y);            // And sets the coordinates
          verticalLineHeader->setName("Vertical");      // Set its name
          verticalLineHeader->setData(x, y);            // And sets the coordinates
          verticalLineFire->setName("Vertical");      // Set its name
          verticalLineFire->setData(x, y);            // And sets the coordinates

/*replot*/
    ui->pltBUpumpRun->replot();
    ui->pltACpumpRun->replot();
    ui->pltHeaderPressureHi->replot();
    ui->pltFireDetected->replot();

}
/*Replot with new X coordinate. X coordinate will be defined in separate
 * function depending on mouse or keyboard input */
void PlotWindow::replot()
{
    // Prepare the X axis coordinates on the vertical transfer linea
    QVector<double> x(2), y(2);
    x[0] = coordX;
    y[0] = -50;
    x[1] = coordX;
    y[1] = 50;

    // Sets the new coordinates
    verticalLineBUpump->setData(x, y); verticalLineACpump->setData(x, y);
    verticalLineHeader->setData(x, y); verticalLineFire->setData(x, y);

    // According to the X coordinate mouse clicks define the next position for the tracer
    tracerBUpump->setGraphKey(coordX); tracerACpump->setGraphKey(coordX);
    tracerHeaderPr->setGraphKey(coordX); tracerFire->setGraphKey(coordX);

    //Define displayed value for each plot as a word rather than a number (only two states are
    //possible for each plot)
    QString BUstatus="N/A"; QString ACstatus="N/A"; QString Headstatus="N/A"; QString Firestatus="N/A";
    tracerBUpump->position->value()==1?BUstatus="STOPPED":BUstatus="RUNNING";
    tracerACpump->position->value()==1?ACstatus="STOPPED":ACstatus="RUNNING";
    tracerHeaderPr->position->value()==1?Headstatus="Pressure is high":Headstatus="Pressure is low";
    tracerFire->position->value()==1?Firestatus="Fire not detected":Firestatus="Fire detected";

    // Output the coordinates of the point of the graph, where the router is setted in QLineEdit
    ui->lnBUpumpCoords->setText("time (sec): " + QString::number(tracerBUpump->position->key()) +
                          " status: " + BUstatus);
    ui->lnACpumpCoords->setText("time (sec): " + QString::number(tracerBUpump->position->key()) +
                          " status: " + ACstatus);
    ui->lnHeaderPrCoords->setText("time (sec): " + QString::number(tracerBUpump->position->key()) +
                          " status: " + Headstatus);
    ui->lnFireCoords->setText("time (sec): " + QString::number(tracerBUpump->position->key()) +
                          " status: " + Firestatus);
    /*replot*/
        ui->pltBUpumpRun->replot();
        ui->pltACpumpRun->replot();
        ui->pltHeaderPressureHi->replot();
        ui->pltFireDetected->replot();
}
/*
 Original function taken from https://evileg.com/en/post/94/
 and modified as per my needs
*/
void PlotWindow::slotMousePress(QMouseEvent *event)
{    // Find X coordinate on the graph where the mouse being clicked
    coordX = ui->pltBUpumpRun->xAxis->pixelToCoord(event->pos().x());

    replot();
}
void PlotWindow::slotMouseMove(QMouseEvent *event)
{
    if(QApplication::mouseButtons()) slotMousePress(event);
}

/*Move tracer 1 point left or right on keyboard arrows press and 10 points on PgUp or PgDown buttons press*/
void PlotWindow::slotKeyPressedLeft()
{
    coordX-=1;
    replot();
}

void PlotWindow::slotKeyPressedRight()
{
    coordX +=1;
    replot();
}
void PlotWindow::slotKeyPressedPgUp()
{
    coordX-=10;
    replot();
}
void PlotWindow::slotKeyPressedPgDown()
{
    coordX+=10;
    replot();
}

