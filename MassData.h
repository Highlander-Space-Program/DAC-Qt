#ifndef MASSDATA_H
#define MASSDATA_H

#include "TelemetryData.h"

class MassData : public TelemetryData
{
public:
    double mass;
    double voltage1;
    double voltage2;
};

#endif // MASSDATA_H
