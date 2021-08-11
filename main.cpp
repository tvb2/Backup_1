#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <fstream>
#include <cstdio>
#include "TimeRelayFuncA.h"
#include "TimeRelayFuncB.h"
#include "Relay.h"
#include "SizeStruct.h"
#include <vector>

bool m3150{0};
bool postlube{1};//POSTLUBE
bool ps3200{0};//Header switch
bool controllerActive{0};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
using namespace std;

TimeRelayFuncA kt0140;           //Backup Post Lube OFF cycle
      kt0140.timeSet=9.5*60;         //9.5 minutes
      ResultsData Skt0140;

TimeRelayFuncA kt0141;           //Backup Posl lube continuous
      kt0141.timeSet=3600;           //1 hour
      ResultsData Skt0141;

TimeRelayFuncA kt0142;           //Total postlube
      kt0142.timeSet=3600;           //1 hour
      ResultsData Skt0142;

TimeRelayFuncA kt0143;           //Backup Post Lube ON cycle
      kt0143.timeSet=0.85*3*60;      //153 seconds (0.85 of 3 minutes range)
      ResultsData Skt0143;

TimeRelayFuncA kt0145;           //Fire detected rolldown lube
      kt0145.timeSet=0.2*1*3600;     //720 seconds (0.2 of 1 hour range)
      ResultsData Skt0145;

TimeRelayFuncB kt0144;           //Header pressure high Backup pump off
      kt0144.timeSet=1;              //1 second
      ResultsData Skt0144;

  Relay ka0131;//Controller active
      ka0131.enable=controllerActive;
      ResultsData Ska0131;

  Relay ka0141;//Controller active
      ka0141.enable=1;
      ResultsData Ska0141;

  Relay ka0132;//Controller active
      ka0132.enable=controllerActive;
      ResultsData Ska0132;

  Relay ka0133;//Post lube not required
      ka0133.enable=0;
      ResultsData Ska0133;

  Relay ka0134;//Backup command off
      ka0134.enable=0;
      ResultsData Ska0134;

  Relay ka0135;//AC PRE/POST pump drive
      ResultsData Ska0135;

  Relay ka0136;//Lube oil header pressure high
      ka0136.enable=ps3200;
      ResultsData Ska0136;

  Relay ka0137;//Lube pump inhibit
      ka0137.enable=0;
      ResultsData Ska0137;

  Relay ka0138;//Backup lube oil pump off
      ka0138.enable=1;
      ResultsData Ska0138;

  Relay ka0244;//No fire detected
      ka0244.enable=1;
      ResultsData Ska0244;

int timer_main_sec=kt0142.timeSet;//Total poslube
int timer_program_total=timer_main_sec*1.1;//10% more than Total Postlube
/*Resize structures to be of +10% the size of Total Postlube timer */
    sizeStruct(Skt0140,timer_program_total);
    sizeStruct(Skt0141,timer_program_total);
    sizeStruct(Skt0142,timer_program_total);
    sizeStruct(Skt0143,timer_program_total);
    sizeStruct(Skt0144,timer_program_total);
    sizeStruct(Skt0145,timer_program_total);
    sizeStruct(Ska0131,timer_program_total);
    sizeStruct(Ska0132,timer_program_total);
    sizeStruct(Ska0133,timer_program_total);
    sizeStruct(Ska0134,timer_program_total);
    sizeStruct(Ska0135,timer_program_total);
    sizeStruct(Ska0136,timer_program_total);
    sizeStruct(Ska0137,timer_program_total);
    sizeStruct(Ska0138,timer_program_total);

    //First branch KT0140, KT0141 and KT0142
    if (ka0132.contactsNC() || ka0133.contactsNC())
    {
        if (kt0143.contactsNC())
        {
            kt0140.enable=1;//off cycle
            kt0140.ckIfDN();
        }
        else
        {
            kt0140.enable=0;
            kt0140.ckIfDN();
        }
        kt0141.enable=1;//Backup post lube continuous
        kt0141.ckIfDN();
        kt0142.enable=1;//Total post lube
        kt0142.ckIfDN();
    }
    else
    {
        kt0140.enable=0;//off cycle
        kt0140.ckIfDN();
        kt0141.enable=0;//Backup post lube continuous
        kt0141.ckIfDN();
        kt0142.enable=0;//Total post lube
        kt0142.ckIfDN();
    }
    //Second branch KT0143 - Backup pump post lube On cycle
    if (kt0140.contactsNO())
    {
        kt0143.enable=1;//Backup pump post lube ON cycle
        kt0143.ckIfDN();
    }
    else
    {
        kt0143.enable=0;//Backup pump post lube ON cycle
        kt0143.ckIfDN();
    }
    //KT0144 Function B is always enabled (header pressure high backup pump off)
    kt0144.enable=1;
    //KT0144 controlled by switch input (header pressure high backup pump off)
    if (ka0136.contactsNO() && ka0138.contactsNO())
    {
        kt0144.switchON=1;//KT0144 - header pressure high backup pump off
        kt0144.ckIfDN();
    }
    else
    {
        kt0144.switchON=0;//KT0144 - header pressure high backup pump off
        kt0144.ckIfDN();
    }
    //Fire detected roll down relay KT0145
    if (ka0244.contactsNC())
    {
        kt0145.enable=1;
        kt0145.ckIfDN();
    }
    else
    {
        kt0145.enable=0;
        kt0145.ckIfDN();
    }
    bool acpump1{0}, acpump2{0};
    {
        //KA0135 branch -1 (AC Pre/Post pump drive)
        if (ka0137.contactsNO() && ka0131.contactsNC())
        {
            acpump1=1;
        }
        //KA0135 branch -2 (AC Pre/Post pump drive)
        if (m3150 && ka0131.contactsNO())
        {
            acpump2=1;
        }
        if (acpump1 || acpump2)
            ka0135.enable=1;
        else
            ka0135.enable=0;
    }
    //KA0136 header pressure high
    if (ps3200)
    {
        ka0136.enable=1;
    }
    //KA0137 Lube pump inhibit
    if (kt0145.contactsNO() || kt0142.contactsNO())//Fire detected rolldown lube OR Total postlube
    {
        ka0137.enable=1;
    }
    else
    {
        ka0137.enable=0;
    }
    //KA0138 - Backup lube oil pump off
    bool line1{0},line2{0},line3{0}, line4{0}, line5{0};
    {
        if (ka0134.contactsNO() && ka0132.contactsNO())
        {
            line1=1;
        }
        if (kt0140.contactsNC() && kt0141.contactsNO())
        {
            line2=1;
        }
        if (kt0144.contactsNO() && ka0132.contactsNC())
        {
            line3=1;
        }
        if (line2 && ka0132.contactsNC())
        {
            line4=1;
        }
        if (ka0137.contactsNO() && ka0132.contactsNC())
        {
            line5=1;
        }
        if (line1 || line3 || line4 || line5)
        {
            ka0138.enable=1;
        }
        else
        {
            ka0138.enable=0;
        }
    }
     return app.exec();
}
