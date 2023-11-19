#ifndef TEMPERATUREDATA_H
#define TEMPERATUREDATA_H

#include "TelemetryData.h"

class TemperatureData : public TelemetryData
{
public:
    double weight;
    double voltage1;
    double voltage2;
};

#endif // TEMPERATUREDATA_H
