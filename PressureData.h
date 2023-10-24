#ifndef PRESSUREDATA_H
#define PRESSUREDATA_H

#include "TelemetryDataBase.h"

class PressureData : TelemetryDataBase
{
public:
    double pt1Voltage1;
    double pt1Voltage2;
    double pt1Pressure;
};

#endif // PRESSUREDATA_H
