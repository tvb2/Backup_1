#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plotwindow.h"

#include "TimeRelayFuncA.h"
#include "TimeRelayFuncB.h"
#include "Relay.h"
#include "SizeStruct.h"
#include "backupeval.h"

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
bool postlube{1};//POSTLUBE
bool ps3200{0};//Header switch
int timer_program_total{0};//10% more than Total Postlube
int time1Fire{0}, time1HeadPress{0};
int time2Fire{50000}, time2HeadPress{50000};


/*function to re-initialize class objects for new calculation*/
void initialize(){
    kt0140=TimeRelayFuncA();           //Backup Post Lube OFF cycle
    kt0141=TimeRelayFuncA();           //Backup Posl lube continuous
    kt0142=TimeRelayFuncA();           //Total postlube
    kt0143=TimeRelayFuncA();           //Backup Post Lube ON cycle
    kt0145=TimeRelayFuncA();           //Fire detected rolldown lube
    kt0144=TimeRelayFuncB();           //Header pressure high Backup pump off
    ka0131=Relay();                   //Controller active
    ka0141=Relay();                   //Controller active
    ka0132=Relay();                   //Controller active
    ka0133=Relay();                   //Post lube not required
    ka0134=Relay();                   //Backup command off
    ka0135=Relay();               //AC PRE/POST pump drive
    ka0136=Relay();               //Lube oil header pressure high
    ka0137=Relay();               //Lube pump inhibit
    ka0138=Relay();               //Backup lube oil pump off
    ka0244=Relay();               //No fire detected
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCalculate_clicked()
{
    //Get user inputs and set timer presets. Recalculate from hours and minutes into seconds
    UserData::timer_main_sec=3600*(ui->totalPostlubeRangeHRS->text().toInt())*(ui->totalPostlubeDial->text().toFloat());
    UserData::roll_down_timer_sec=3600*(ui->rollDownTimeRangeHRS->text().toInt())*(ui->rollDownTimeDial->text().toFloat());
    UserData::post_lube_cont_sec=3600*(ui->postLubeContRangeHRS->text().toInt())*(ui->postLubeContDial->text().toFloat());
    UserData::post_lube_on_cycle=60*(ui->postLubeONRangeMinutes->text().toInt())*(ui->postLubeOnDial->text().toFloat());
    UserData::post_lube_off_cycle=60*(ui->postLubeOffRangeMin->text().toInt())*(ui->postLubeOffDial->text().toFloat());
    UserData::header_press_high_sec=ui->headerHighRangeSec->text().toInt()*ui->headerHighDial->text().toInt();
    UserData::fireDetected=ui->ckBxFireDetected->isChecked();
    time1Fire=ui->time1Fire->text().toInt();
    time2Fire=ui->time2Fire->text().toInt();

    UserData::controllerActive=ui->ckBxControllerActive->isChecked();

    //checked when header pressure is low
    UserData::ps3200=ui->ckBxHeaderLo->isChecked();
    time1HeadPress=ui->time1Header->text().toInt();
    time2HeadPress=ui->time2Header->text().toInt();

    //Initialize class objects (needed for 2nd 3rd... calculation
    initialize();

    //Backup Post Lube OFF cycle
          kt0140.timeSet=UserData::post_lube_off_cycle;         //570 sec, 9.5 minutes
    //Backup Post lube continuous
          kt0141.timeSet=UserData::post_lube_cont_sec;           //1 hour
    //Total postlube
          kt0142.timeSet=UserData::timer_main_sec; //defined by user
    //Backup Post Lube ON cycle
          kt0143.timeSet=UserData::post_lube_on_cycle;      //153 seconds (0.85 of 3 minutes range)
    //Fire detected rolldown lube
          kt0145.timeSet=UserData::roll_down_timer_sec;     //720 seconds (0.2 of 1 hour range)
    //Header pressure high Backup pump off
          kt0144.timeSet=UserData::header_press_high_sec;              //1 second
    //Controller active
          ka0131.enable=UserData::controllerActive;
    //Controller active
          ka0141.enable=1;
    //Controller active
          ka0132.enable=UserData::controllerActive;
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
          ka0244.enable=!(UserData::fireDetected);//reverse logic when KA0244 is Enabled, there is no fire detected

    //10% more than Total Postlube
          timer_program_total=static_cast<int>(kt0142.timeSet*1.1);

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
    if (UserData::fireDetected){
        if (program_timer>=time1Fire && program_timer<time2Fire)
            ka0244.enable=0;
        else
            ka0244.enable=1;
    }
    if (UserData::ps3200){
        if (program_timer>=time1HeadPress && program_timer<time2HeadPress)
                    ka0136.enable=0;
                else
                    ka0136.enable=1;
    }else if (!UserData::ps3200) ka0136.enable=1;

    //evaluate simulation
    BackupEval(program_timer);
}
    plotWindow = new PlotWindow(this);
    plotWindow->show();
}

