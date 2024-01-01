#ifndef SINK_H
#define SINK_H

#include "Broadcaster.h"
#include "../models/TelemetryData.h"

class Sink {
private:
    std::vector<std::shared_ptr<BroadcasterBase>> broadcasters;

public:
  Sink() =default;
  Sink(std::vector<std::shared_ptr<BroadcasterBase>> broadcasters) : broadcasters(broadcasters) { }
    int sendData(std::vector<TelemetryData*> data) {
      for (auto& dbData : data) {
          for (auto& broadcaster : broadcasters) {
              broadcaster->broadcastBase(dbData);
          }
      }
      return 0; // Assuming sendData is always successful for this example
  }
};

#endif // SINK_H
