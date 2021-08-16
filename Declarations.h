/*Declare ResultsData structure. This will contain data sets for the complete
 simulation for each device */
#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include <cstdio>
#include <vector>
#include <QVector>

struct ResultsData
{
    std::vector<bool>enable{};
    std::vector<int>elapsed{};
    std::vector<bool>NC{};
    std::vector<bool>NO{};
    std::vector<bool>switchStatus{};
    QVector<double>dblEnable{};
    QVector<double>dblNC{};
    QVector<double>dblNO{};
    QVector<double>dblelapsed{};
};

#endif // DECLARATIONS_H
