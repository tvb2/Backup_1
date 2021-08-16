#include "mainwindow.h"
#include <QApplication>
#include <QVector>

#include <iostream>
#include <fstream>
#include <cstdio>
#include "TimeRelayFuncA.h"
#include "TimeRelayFuncB.h"
#include "Relay.h"
#include "SizeStruct.h"
#include "backupeval.h"
#include <vector>

/*Declare here in order to be able to use these in plot *.cpp file*/
ResultsData Skt0140;           //Backup Post Lube OFF cycle
ResultsData Skt0141;           //Backup Posl lube continuous
ResultsData Skt0142;           //Total postlube
ResultsData Skt0143;           //Backup Post Lube ON cycle
ResultsData Skt0145;           //Fire detected rolldown lube
ResultsData Skt0144;           //Header pressure high Backup pump off

ResultsData Ska0131;           //Controller active
ResultsData Ska0141;           //Controller active
ResultsData Ska0132;           //Controller active
ResultsData Ska0133;           //Post lube not required
ResultsData Ska0134;           //Backup command off
ResultsData Ska0135;           //AC PRE/POST pump drive
ResultsData Ska0136;           //Lube oil header pressure high
ResultsData Ska0137;           //Lube pump inhibit
ResultsData Ska0138;           //Backup lube oil pump off
ResultsData Ska0244;           //No fire detected

TimeRelayFuncA kt0140;           //Backup Post Lube OFF cycle
TimeRelayFuncA kt0141;           //Backup Posl lube continuous
TimeRelayFuncA kt0142;           //Total postlube
TimeRelayFuncA kt0143;           //Backup Post Lube ON cycle
TimeRelayFuncA kt0145;           //Fire detected rolldown lube
TimeRelayFuncB kt0144;           //Header pressure high Backup pump off
Relay ka0131;                   //Controller active
Relay ka0141;                   //Controller active
Relay ka0132;                   //Controller active
Relay ka0133;                   //Post lube not required
Relay ka0134;                   //Backup command off
Relay ka0135;               //AC PRE/POST pump drive
Relay ka0136;               //Lube oil header pressure high
Relay ka0137;               //Lube pump inhibit
Relay ka0138;               //Backup lube oil pump off
Relay ka0244;               //No fire detected

QVector<double>dbltime;

bool m3150{1};
bool postlube{0};//POSTLUBE
bool ps3200{0};//Header switch
extern bool controllerActive;
extern bool fireDetected;
extern int timer_main_sec;//Total poslube
int timer_program_total{0};//10% more than Total Postlube

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
//Backup Post Lube OFF cycle
      kt0140.timeSet=9.5*60;         //9.5 minutes
//Backup Post lube continuous
      kt0141.timeSet=3600;           //1 hour
//Total postlube
      kt0142.timeSet=timer_main_sec; //defined by user
//Backup Post Lube ON cycle
      kt0143.timeSet=0.85*3*60;      //153 seconds (0.85 of 3 minutes range)
//Fire detected rolldown lube
      kt0145.timeSet=0.2*1*3600;     //720 seconds (0.2 of 1 hour range)
//Header pressure high Backup pump off
      kt0144.timeSet=1;              //1 second
//Controller active
      ka0131.enable=controllerActive;
//Controller active
      ka0141.enable=1;
//Controller active
      ka0132.enable=controllerActive;
//Post lube not required
      ka0133.enable=0;
//Backup command off
      ka0134.enable=0;
//AC PRE/POST pump drive
      ka0135.enable=0;
//Lube oil header pressure high
      ka0136.enable=ps3200;
//Lube pump inhibit
      ka0137.enable=0;
//Backup lube oil pump off
      ka0138.enable=1;
//No fire detected
      ka0244.enable=!fireDetected;//reverse logic when KA0244 is Enabled, there is no fire detected

    BackupEval();
     return app.exec();
}
