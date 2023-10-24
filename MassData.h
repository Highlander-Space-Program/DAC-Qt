#ifndef MASSDATA_H
#define MASSDATA_H

#include <string>
#include <chrono>

class MassData
{
public:
    MassData();
    double lc1Voltage1;
    double lc1Voltage2;
    double lc1Pressure;
    std::string Label;
    std::chrono::system_clock *clock = new std::chrono::system_clock();
    std::chrono::system_clock::time_point now = clock->now();
};

#endif // MASSDATA_H
