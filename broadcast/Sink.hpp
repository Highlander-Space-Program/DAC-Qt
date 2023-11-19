#ifndef SINK_H
#define SINK_H

#include "Broadcaster.hpp"
#include "TelemetryData.h"

class Sink {
private:
    std::vector<std::shared_ptr<BroadcasterBase>> broadcasters;

public:
    Sink();
    Sink(std::vector<std::shared_ptr<BroadcasterBase>> broadcasters);
    int sendData(std::vector<TelemetryData*> data);
};

#endif // SINK_H
