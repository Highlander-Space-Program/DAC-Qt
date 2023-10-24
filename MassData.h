#ifndef MASSDATA_H
#define MASSDATA_H

#include "TelemetryDataBase.h"

class MassData : public TelemetryDataBase
{
public:
    double lc1Voltage1;
    double lc1Voltage2;
    double lc1Pressure;
};

#endif // MASSDATA_H
