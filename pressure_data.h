#ifndef PRESSURE_DATA_H
#define PRESSURE_DATA_H
#include <string>
#include <chrono>

class Pressure_Data
{
public:
    Pressure_Data();
    double pt1Voltage1;
    double pt1Voltage2;
    double pt1Pressure;
    std::string Label;
    std::chrono::system_clock * clock = new std::chrono::system_clock();
    std::chrono::system_clock::time_point now = clock->now();
};

#endif // PRESSURE_DATA_H
