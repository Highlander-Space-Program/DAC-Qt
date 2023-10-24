#ifndef PRESSUREDATA_H
#define PRESSUREDATA_H

#include "TelemetryDataBase.h"

class PressureData : TelemetryDataBase
{
public:
    double pressure;
    double voltage1;
    double voltage2;
};

#endif // PRESSUREDATA_H
