#ifndef FORCEDATA_H
#define FORCEDATA_H

#include "TelemetryData.h"

class ForceData : public TelemetryData
{
public:
    double mass;
    double voltage1;
    double voltage2;
};

#endif // FORCEDATA_H
