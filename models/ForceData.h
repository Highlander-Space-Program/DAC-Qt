#ifndef FORCEDATA_H
#define FORCEDATA_H

#include "TelemetryData.h"

class ForceData : public VoltageData
{
public:
  ForceData() =default;
  ForceData(double rated_load, double sensitivity, double excitation) :
   rated_load_{rated_load}, sensitivity_{sensitivity}, excitation_{excitation} {}
  virtual ~ForceData() =default;

  double force() const { return force_; }
  double voltage() const { return voltage_; }
  double rated_load() const { return rated_load_; }
  double sensitivity() const { return sensitivity_; }
  double excitation() const { return excitation_; }
  double offset() const  {return offset_; }

  void force(double force) { force_ = force; }
  void voltage(double voltage) { voltage_ = voltage; };
  void rated_load(double rated_load) { rated_load_ = rated_load; }
  void sensitivity(double sensitivity) { sensitivity_ = sensitivity; }
  void excitation(double excitation) { excitation_ = excitation; }
  void offset(double offset) { offset_ = offset; }

  double from_voltage(double voltage) override {
    return rated_load_ * voltage / (sensitivity_ * excitation_);
  }

private:
  double force_ {0.0};
  double voltage_ {0.0};

  double rated_load_ {1000};
  double sensitivity_ {0.002};
  double excitation_ {5};

  double offset_ {0};
};

#endif // FORCEDATA_H
