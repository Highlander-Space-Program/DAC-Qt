#ifndef DAC_QT_LABJACKSINKSTRATEGY_H
#define DAC_QT_LABJACKSINKSTRATEGY_H

#include <utility>

#include "LabJackSink.h"
#include "../models/PressureData.h"
#include "../models/TemperatureData.h"
#include "../models/ForceData.h"

class LabJackSinkStrategy {
public:
  virtual ~LabJackSinkStrategy() =default;
  virtual const std::vector<std::string> address_list() const =0;
  virtual const std::vector<std::string> address_labels() const =0;
  virtual void process(const double data[], const LabJackSink::stream_callback_args *args) =0;
};

class InjectorTestStrategy: public LabJackSinkStrategy {
public:
  InjectorTestStrategy(std::shared_ptr<Broadcaster<PressureData>> pressureBroadcaster)
                       : pressureBroadcaster_{std::move(pressureBroadcaster)} { }

  const std::vector<std::string> address_list() const override { return address_list_; }
  const std::vector<std::string> address_labels() const override { return address_labels_; }

  void process(const double data[], const LabJackSink::stream_callback_args *args) override {
    const size_t num_addresses = args->strategy->address_list().size();
    for (size_t i {0}; i < args->scans_per_read*num_addresses; i++) {
      auto* p = new PressureData(data[i]);
      p->label = args->strategy->address_labels()[i%num_addresses];
      pressureBroadcaster_->broadcast(p);
    }
  }

private:
  const std::vector<std::string> address_list_ = {"AIN0", "AIN1"};
  const std::vector<std::string> address_labels_ = {"PT-01", "PT-02"};
  const std::shared_ptr<Broadcaster<PressureData>> pressureBroadcaster_;
};


#endif //DAC_QT_LABJACKSINKSTRATEGY_H
