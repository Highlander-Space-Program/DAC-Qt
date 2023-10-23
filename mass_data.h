#ifndef MASS_DATA_H
#define MASS_DATA_H

#include <string>
#include <chrono>

class Mass_Data
{
public:
    Mass_Data();
    double lc1Voltage1;
    double lc1Voltage2;
    double lc1Pressure;
    std::string Label;
    std::chrono::system_clock * clock = new std::chrono::system_clock();
    std::chrono::system_clock::time_point now = clock->now();
};

#endif // MASS_DATA_H
