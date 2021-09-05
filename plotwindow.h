#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include "Declarations.h"
#include <qcustomplot.h>
#include <QShortcut>
#include <QKeyEvent>

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();

private slots:
    void on_pltBtn_clicked();
    void slotMousePress(QMouseEvent *event);
    void slotMouseMove(QMouseEvent * event);
    void slotKeyPressedLeft();
    void slotKeyPressedRight();
    void slotKeyPressedPgUp();
    void slotKeyPressedPgDown();

private:
    Ui::PlotWindow *ui;
    QCPCurve *verticalLineBUpump,
    *verticalLineACpump,
    *verticalLineHeader,
    *verticalLineFire;
    QCPItemTracer *tracerBUpump,
    *tracerACpump,
    *tracerHeaderPr,
    *tracerFire;
    QShortcut *Left, *Right, *PgUp, *PgDown;
    double coordX{0};
    void replot();
};

#endif // PLOTWINDOW_H
