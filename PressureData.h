#ifndef PRESSUREDATA_H
#define PRESSUREDATA_H

#include "TelemetryData.h"

class PressureData : TelemetryData
{
public:
    double pressure;
    double voltage1;
    double voltage2;
};

#endif // PRESSUREDATA_H
