#ifndef MASSDATA_H
#define MASSDATA_H

#include "TelemetryDataBase.h"

class MassData : public TelemetryDataBase
{
public:
    double mass;
    double voltage1;
    double voltage2;
};

#endif // MASSDATA_H
