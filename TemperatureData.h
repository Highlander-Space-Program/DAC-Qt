#ifndef TEMPERATUREDATA_H
#define TEMPERATUREDATA_H

#include "TelemetryDataBase.h"

class TemperatureData : public TelemetryDataBase
{
public:
    double weight;
    double voltage1;
    double voltage2;
};

#endif // TEMPERATUREDATA_H
