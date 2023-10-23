#ifndef TEMPERATURE_DATA_H
#define TEMPERATURE_DATA_H

#include <string>
#include <chrono>


class Temperature_Data
{
public:
    Temperature_Data();
    double tc1Voltage1;
    double tc1Voltage2;
    double tc1Weight;
    std::string Label;
    std::chrono::system_clock * clock = new std::chrono::system_clock();
    std::chrono::system_clock::time_point now = clock->now();
};

#endif // TEMPERATURE_DATA_H
