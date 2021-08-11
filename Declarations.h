/*Declare some structures and variables here to be used in other source and header files*/
#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include <cstdio>
#include <vector>

struct ResultsData
{
    std::vector<bool>enable{};
    std::vector<int>elapsed{};
    std::vector<bool>NC{};
    std::vector<bool>NO{};
    std::vector<bool>switchStatus{};
};
#endif // DECLARATIONS_H
