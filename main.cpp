#include "mainwindow.h"
#include <QApplication>
#include <QVector>
//just a comment
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

     return app.exec();
}
