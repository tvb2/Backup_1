#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plotwindow.h"

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
    //Get user input and set total postlube time. Recalculate from hours and minutes into seconds
    UserData::timer_main_sec=3600*(ui->totalPostlubeHours->text().toInt())+60*(ui->totalPostlubeMinutes->text().toInt());
    UserData::fireDetected=ui->ckBxFireDetected->isChecked();
    UserData::controllerActive=ui->ckBxControllerActive->isChecked();
    plotWindow = new PlotWindow(this);
    plotWindow->show();
}

