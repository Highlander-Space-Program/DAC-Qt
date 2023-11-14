#ifndef SINK_H
#define SINK_H

#include <vector>
#include <memory>
#include "Broadcaster.hpp"
#include "TelemetryDataBase.h"

class Sink {
private:
    std::vector<std::shared_ptr<BroadcasterBase>> broadcasters;

public:
    Sink();
    Sink(std::vector<std::shared_ptr<BroadcasterBase>> broadcasters);
    int sendData(std::vector<TelemetryDataBase*> data);
};

#endif // SINK_H
