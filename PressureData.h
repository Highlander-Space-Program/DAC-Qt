#ifndef PRESSUREDATA_H
#define PRESSUREDATA_H

#include <string>
#include <chrono>

class PressureData
{
public:
    PressureData();
    double pt1Voltage1;
    double pt1Voltage2;
    double pt1Pressure;
    std::string Label;
    std::chrono::system_clock *clock = new std::chrono::system_clock();
    std::chrono::system_clock::time_point now = clock->now();
};

#endif // PRESSUREDATA_H
