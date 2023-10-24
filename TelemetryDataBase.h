#ifndef TELEMETRYDATABASE_H
#define TELEMETRYDATABASE_H

#include <string>
#include <chrono>

class TelemetryDataBase {
public:
  std::string label;
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
};

#endif // TELEMETRYDATABASE_H
