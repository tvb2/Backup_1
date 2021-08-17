#include "plotwindow.h"
#include "ui_plotwindow.h"
#include <TimeRelayFuncA.h>
#include <TimeRelayFuncB.h>
#include <Relay.h>
#include "userdata.h"

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

extern int timer_main_sec;

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::on_pltBtn_clicked()
{
/*Backup pump Run plot*/
    ui->pltBUpumpRun->addGraph();
    ui->pltBUpumpRun->graph(0)->setData(dbltime, Ska0138.dblEnable);
    ui->pltBUpumpRun->xAxis->setLabel("time");
    ui->pltBUpumpRun->yAxis->setLabel("Backup \n pump");
    // set axes ranges, so we see all data:
    ui->pltBUpumpRun->xAxis->setRange(0, UserData::timer_main_sec*1.1);
    ui->pltBUpumpRun->yAxis->setRange(0, 2);
    ui->pltBUpumpRun->replot();
/*PRE/POST pump Run plot*/
    ui->pltACpumpRun->addGraph();
    ui->pltACpumpRun->graph(0)->setData(dbltime, Ska0135.dblEnable);
    ui->pltACpumpRun->xAxis->setLabel("time");
    ui->pltACpumpRun->yAxis->setLabel("AC \n pump");
    // set axes ranges, so we see all data:
    ui->pltACpumpRun->xAxis->setRange(0, UserData::timer_main_sec*1.1);
    ui->pltACpumpRun->yAxis->setRange(0, 2);
    ui->pltACpumpRun->replot();
/*Header Pressure High plot*/
    ui->pltHeaderPressureHi->addGraph();
    ui->pltHeaderPressureHi->graph(0)->setData(dbltime, Ska0136.dblEnable);
    ui->pltHeaderPressureHi->xAxis->setLabel("time");
    ui->pltHeaderPressureHi->yAxis->setLabel("Header \n pressure");
    // set axes ranges, so we see all data:
    ui->pltHeaderPressureHi->xAxis->setRange(0, UserData::timer_main_sec*1.1);
    ui->pltHeaderPressureHi->yAxis->setRange(0, 2);
    ui->pltHeaderPressureHi->replot();
/*Fire Detected*/
    ui->pltFireDetected->addGraph();
    ui->pltFireDetected->graph(0)->setData(dbltime, Ska0244.dblEnable);
    ui->pltFireDetected->xAxis->setLabel("time");
    ui->pltFireDetected->yAxis->setLabel("No fire \n detected");
    // set axes ranges, so we see all data:
    ui->pltFireDetected->xAxis->setRange(0, UserData::timer_main_sec*1.1);
    ui->pltFireDetected->yAxis->setRange(0, 2);
    ui->pltFireDetected->replot();
}

