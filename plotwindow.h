#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include "Declarations.h"
#include <qcustomplot.h>

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
    void slotMousePress(QMouseEvent * event);
    void slotMouseMove(QMouseEvent * event);

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
};

#endif // PLOTWINDOW_H
