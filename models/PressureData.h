#ifndef PRESSUREDATA_H
#define PRESSUREDATA_H

#include "TelemetryData.h"

class PressureData : public VoltageData {
public:
PressureData() =default;
PressureData(double min_pressure, double max_pressure_, double min_voltage, double max_voltage)
  : min_pressure_{min_pressure},
  max_pressure_{max_pressure_},
  min_voltage_{min_voltage},
  max_voltage_{max_voltage} {}
virtual ~PressureData() =default;

void pressure(double pressure) { pressure_ = pressure; }
void voltage(double voltage) { voltage_ = voltage; }

double pressure() const { return pressure_; }
double voltage() const { return voltage_; }

virtual double from_voltage(double voltage) {
  return (voltage-min_voltage_)*((max_pressure_-min_pressure_)/(max_voltage_-min_voltage_)) + min_pressure_;
}

private:
  double pressure_ {0.0};
  double voltage_ {0.0};

  // Pressure Transducer operating conditions
  double min_pressure_ {0.0};
  double max_pressure_ {1600.0};
  double min_voltage_ {0.5};
  double max_voltage_ {4.5};
};

class CalibratedPressureData : public PressureData {
public:
  CalibratedPressureData(double m, double b) : m_{m}, b_{b} {}

  double from_voltage(double voltage) override {
    return m_ * voltage + b_;
  }

private:
  // Calibrated scaling equation parameters
  double m_ {0};
  double b_ {0};
};

#endif // PRESSUREDATA_H
