#include "Sink.hpp"
#include "Broadcaster.hpp"
#include "TelemetryDataBase.h"

Sink::Sink() {}

Sink::Sink(std::vector<std::shared_ptr<BroadcasterBase>> broadcasters) : broadcasters(broadcasters) {}

int Sink::sendData(std::vector<TelemetryDataBase*> data) {
    for (auto& dbData : data) {
        for (auto& broadcaster : broadcasters) {
            broadcaster->broadcastBase(dbData);
        }
    }
    return 0; // Assuming sendData is always successful for this example
}
