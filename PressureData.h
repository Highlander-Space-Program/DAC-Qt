#ifndef PRESSUREDATA_H
#define PRESSUREDATA_H

#include "TelemetryData.h"

class PressureData : public TelemetryData
{
public:
    double pressure;
    double voltage1;
    double voltage2;
};

#endif // PRESSUREDATA_H
