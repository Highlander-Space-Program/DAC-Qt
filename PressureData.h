#ifndef PRESSUREDATA_H
#define PRESSUREDATA_H

#include "TelemetryData.h"

class PressureData : public TelemetryData
{
public:

  explicit PressureData(double voltage) { this->from_voltage(voltage); }

  void from_voltage(double voltage) {
    voltage_ = voltage;
    pressure_ = voltage_to_pressure(voltage);
  }

  void pressure(double pressure) { pressure_ = pressure; }
  void voltage(double voltage) { voltage_ = voltage; }

  double pressure() const { return pressure_; }
  double voltage() const { return voltage_; }

  static constexpr double voltage_to_pressure(double voltage) {
    constexpr double min_pressure = 0.0,
            max_pressure = 1600.0,
            min_voltage = 0.5,
            max_voltage = 4.5;
    return (voltage-min_voltage)*((max_pressure-min_pressure)/(max_voltage-min_voltage)) + min_pressure;
  }
private:
  double pressure_ {0.0};
  double voltage_ {0.0};
};

#endif // PRESSUREDATA_H
