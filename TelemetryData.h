#ifndef TELEMETRYDATA_H
#define TELEMETRYDATA_H

#include <string>
#include <chrono>

class TelemetryData {
public:
  std::string label;
  std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();
};

#endif // TELEMETRYDATA_H
