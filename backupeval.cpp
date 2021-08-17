#include "backupeval.h"
#include <TimeRelayFuncA.h>
#include <TimeRelayFuncB.h>
#include <Declarations.h>
#include "SizeStruct.h"
#include <Relay.h>

/*Defined in mainwindow.cpp*/
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

extern bool m3150;
extern bool postlube;//POSTLUBE
extern bool ps3200;//Header switch
extern bool controllerActive;
extern int timer_main_sec;//Total poslube
extern int timer_program_total;//10% more than Total Postlube

void BackupEval()
{
    timer_program_total=static_cast<int>(kt0142.timeSet*1.1);//10% more than Total Postlube

    /*Resize structures to be of +10% the size of Total Postlube timer */
        sizeStruct(Skt0140,timer_program_total);
        sizeStruct(Skt0141,timer_program_total);
        sizeStruct(Skt0142,timer_program_total);
        sizeStruct(Skt0143,timer_program_total);
        sizeStruct(Skt0144,timer_program_total);
        sizeStruct(Skt0145,timer_program_total);
        sizeStruct(Ska0131,timer_program_total);
        sizeStruct(Ska0141,timer_program_total);
        sizeStruct(Ska0132,timer_program_total);
        sizeStruct(Ska0133,timer_program_total);
        sizeStruct(Ska0134,timer_program_total);
        sizeStruct(Ska0135,timer_program_total);
        sizeStruct(Ska0136,timer_program_total);
        sizeStruct(Ska0137,timer_program_total);
        sizeStruct(Ska0138,timer_program_total);
        sizeStruct(Ska0244,timer_program_total);
        dbltime.resize(timer_program_total);
    for (int program_timer=0;program_timer<timer_program_total;++program_timer)
{
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
    //Create output
            //Backup Post Lube OFF cycle
              Skt0140.NO[program_timer]=kt0140.contactsNO();
              Skt0140.NC[program_timer]=kt0140.contactsNC();
              Skt0140.elapsed[program_timer]=kt0140.elapsed;
              Skt0140.dblNO[program_timer]=kt0140.contactsNO();
              Skt0140.dblNC[program_timer]=kt0140.contactsNC();
              Skt0140.dblelapsed[program_timer]=kt0140.elapsed;

            //Backup Posl lube continuous
              Skt0141.NO[program_timer]=kt0141.contactsNO();
              Skt0141.NC[program_timer]=kt0141.contactsNC();
              Skt0141.dblNO[program_timer]=kt0141.contactsNO();
              Skt0141.dblNC[program_timer]=kt0141.contactsNC();

            //Total postlube
              Skt0142.NO[program_timer]=kt0142.contactsNO();
              Skt0142.NC[program_timer]=kt0142.contactsNC();
              Skt0142.dblNO[program_timer]=kt0142.contactsNO();
              Skt0142.dblNC[program_timer]=kt0142.contactsNC();

            //Backup Post Lube ON cycle
              Skt0143.NO[program_timer]=kt0143.contactsNO();
              Skt0143.NC[program_timer]=kt0143.contactsNC();
              Skt0143.dblNO[program_timer]=kt0143.contactsNO();
              Skt0143.dblNC[program_timer]=kt0143.contactsNC();

            //Header pressure high Backup pump off
              Skt0144.NO[program_timer]=kt0144.contactsNO();
              Skt0144.NC[program_timer]=kt0144.contactsNC();
              Skt0144.dblNO[program_timer]=kt0144.contactsNO();
              Skt0144.dblNC[program_timer]=kt0144.contactsNC();

            //Fire detected rolldown lube
              Skt0145.NO[program_timer]=kt0145.contactsNO();
              Skt0145.NC[program_timer]=kt0145.contactsNC();
              Skt0145.dblNO[program_timer]=kt0145.contactsNO();
              Skt0145.dblNC[program_timer]=kt0145.contactsNC();

            //Controller active
              Ska0131.NO[program_timer]=ka0131.contactsNO();
              Ska0131.NC[program_timer]=ka0131.contactsNC();
              Ska0131.enable[program_timer]=ka0131.enable;
              Ska0131.dblNO[program_timer]=ka0131.contactsNO();
              Ska0131.dblNC[program_timer]=ka0131.contactsNC();
              Ska0131.dblEnable[program_timer]=ka0131.enable;

            //Controller active
              Ska0132.NO[program_timer]=ka0132.contactsNO();
              Ska0132.NC[program_timer]=ka0132.contactsNC();
              Ska0132.enable[program_timer]=ka0132.enable;
              Ska0132.dblNO[program_timer]=ka0132.contactsNO();
              Ska0132.dblNC[program_timer]=ka0132.contactsNC();
              Ska0132.dblEnable[program_timer]=ka0132.enable;

            //Controller active
              Ska0141.NO[program_timer]=ka0141.contactsNO();
              Ska0141.NC[program_timer]=ka0141.contactsNC();
              Ska0141.enable[program_timer]=ka0141.enable;
              Ska0141.dblNO[program_timer]=ka0141.contactsNO();
              Ska0141.dblNC[program_timer]=ka0141.contactsNC();
              Ska0141.dblEnable[program_timer]=ka0141.enable;

            //Post lube not required
              Ska0133.NO[program_timer]=ka0133.contactsNO();
              Ska0133.NC[program_timer]=ka0133.contactsNC();
              Ska0133.enable[program_timer]=ka0133.enable;
              Ska0133.dblNO[program_timer]=ka0133.contactsNO();
              Ska0133.dblNC[program_timer]=ka0133.contactsNC();
              Ska0133.dblEnable[program_timer]=ka0133.enable;

            //Backup command off
              Ska0134.NO[program_timer]=ka0134.contactsNO();
              Ska0134.NC[program_timer]=ka0134.contactsNC();
              Ska0134.enable[program_timer]=ka0134.enable;
              Ska0134.dblNO[program_timer]=ka0134.contactsNO();
              Ska0134.dblNC[program_timer]=ka0134.contactsNC();
              Ska0134.dblEnable[program_timer]=ka0134.enable;

            //AC PRE/POST pump drive
              Ska0135.NO[program_timer]=ka0135.contactsNO();
              Ska0135.NC[program_timer]=ka0135.contactsNC();
              Ska0135.enable[program_timer]=ka0135.enable;
              Ska0135.dblNO[program_timer]=ka0135.contactsNO();
              Ska0135.dblNC[program_timer]=ka0135.contactsNC();
              Ska0135.dblEnable[program_timer]=ka0135.enable;

            //Lube oil header pressure high
              Ska0136.NO[program_timer]=ka0136.contactsNO();
              Ska0136.NC[program_timer]=ka0136.contactsNC();
              Ska0136.enable[program_timer]=ka0136.enable;
              Ska0136.dblNO[program_timer]=ka0136.contactsNO();
              Ska0136.dblNC[program_timer]=ka0136.contactsNC();
              Ska0136.dblEnable[program_timer]=ka0136.enable;

            //Lube pump inhibit
              Ska0137.NO[program_timer]=ka0137.contactsNO();
              Ska0137.NC[program_timer]=ka0137.contactsNC();
              Ska0137.enable[program_timer]=ka0137.enable;
              Ska0137.dblNO[program_timer]=ka0137.contactsNO();
              Ska0137.dblNC[program_timer]=ka0137.contactsNC();
              Ska0137.dblEnable[program_timer]=ka0137.enable;

            //Backup lube oil pump off
              Ska0138.NO[program_timer]=ka0138.contactsNO();
              Ska0138.NC[program_timer]=ka0138.contactsNC();
              Ska0138.enable[program_timer]=ka0138.enable;
              Ska0138.dblEnable[program_timer]=ka0138.enable;

            //No fire detected
              Ska0244.NO[program_timer]=ka0244.contactsNO();
              Ska0244.NC[program_timer]=ka0244.contactsNC();
              Ska0244.enable[program_timer]=ka0244.enable;
              Ska0244.dblNO[program_timer]=ka0244.contactsNO();
              Ska0244.dblNC[program_timer]=ka0244.contactsNC();
              Ska0244.dblEnable[program_timer]=ka0244.enable;

dbltime[program_timer]=program_timer;
    }
}
