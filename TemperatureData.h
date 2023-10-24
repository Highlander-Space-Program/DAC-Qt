#ifndef TEMPERATUREDATA_H
#define TEMPERATUREDATA_H

#include "TelemetryDataBase.h"

class TemperatureData : public TelemetryDataBase
{
public:
    double tc1Voltage1;
    double tc1Voltage2;
    double tc1Weight;
};

#endif // TEMPERATUREDATA_H
