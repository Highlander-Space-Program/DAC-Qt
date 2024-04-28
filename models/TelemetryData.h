#ifndef TELEMETRYDATA_H
#define TELEMETRYDATA_H

#include <string>
#include <chrono>

class TelemetryData {
public:
  virtual ~TelemetryData() =default;
  std::string label;
  std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();
};

class VoltageData : public TelemetryData {
public:
  virtual ~VoltageData() =default;
  virtual double from_voltage(double voltage) =0;
};

#endif // TELEMETRYDATA_H
