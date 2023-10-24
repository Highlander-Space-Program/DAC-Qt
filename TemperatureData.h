#ifndef TEMPERATUREDATA_H
#define TEMPERATUREDATA_H

#include <string>
#include <chrono>

class TemperatureData
{
public:
    TemperatureData();
    double tc1Voltage1;
    double tc1Voltage2;
    double tc1Weight;
    std::string label;
    std::chrono::system_clock *clock = new std::chrono::system_clock();
    std::chrono::system_clock::time_point now = clock->now();
};

#endif // TEMPERATUREDATA_H
