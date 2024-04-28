#ifndef DAC_QT_COLDFLOWSINKSTRATEGY_H
#define DAC_QT_COLDFLOWSINKSTRATEGY_H

#include "LabJackSinkStrategy.h"

class ColdFlowSinkStrategy : public LabJackSinkStrategy {
public:
  ColdFlowSinkStrategy(std::shared_ptr<PressureData> pt02DataPrototype,
                       std::shared_ptr<PressureData> pt03DataPrototype,
                       std::shared_ptr<PressureData> pt04DataPrototype,
                       std::shared_ptr<PressureData> pt05DataPrototype,
                       std::shared_ptr<PressureData> pt06DataPrototype,
                       std::shared_ptr<ForceData> lc01DataPrototype,
                       std::shared_ptr<ForceData> lc02DataPrototype,
                       std::shared_ptr<ForceData> lc03DataPrototype,
                       std::shared_ptr<Broadcaster<PressureData>> pressureBroadcaster,
                       std::shared_ptr<Broadcaster<ForceData>> forceBroadcaster)
          : pt_prototypes_{std::move(pt02DataPrototype), std::move(pt03DataPrototype), std::move(pt04DataPrototype), std::move(pt05DataPrototype), std::move(pt06DataPrototype)},
            lc_prototypes_{std::move(lc01DataPrototype), std::move(lc02DataPrototype), std::move(lc03DataPrototype)},
            pressure_broadcaster_{std::move(pressureBroadcaster)},
            force_broadcaster_{std::move(forceBroadcaster)} { }

  void configure_device(const LabJackSink *sink) override;

  const std::vector<std::string> address_list() const override { return address_list_; }
  const std::vector<std::string> address_labels() const override { return address_labels_; }

  void process(const double data[], const LabJackSink::stream_callback_args *args) override {
    const size_t num_addresses = args->strategy->address_list().size();
    for (size_t i {0}; i < args->scans_per_read*num_addresses; i+=num_addresses) {
      size_t index {0};
      for (size_t i_p {0}; i_p < num_pts_; i_p++) {
        index = i + i_p;
        auto *p = new PressureData(*pt_prototypes_[i_p]);
        p->voltage(data[index]);
        p->pressure(p->from_voltage(p->voltage()));
        p->label = args->strategy->address_labels()[(index)%num_addresses];
        pressure_broadcaster_->broadcast(p);
      }
      for (size_t i_lc {0}; i < num_lcs_; i++) {
        index = i + num_pts_ + i_lc;
        auto *lc = new ForceData(*lc_prototypes_[i_lc]);
        lc->voltage(data[index]);
        lc->force(lc->from_voltage(lc->voltage()));
        lc->label = args->strategy->address_labels()[(index)%num_addresses];
        force_broadcaster_->broadcast(lc);
      }
    }
  }

private:
  static const size_t num_pts_ = 5;
  static const size_t num_lcs_ = 3;

  const std::vector<std::string> address_list_ = {"AIN0", "AIN1", "AIN2", "AIN3", "AIN12", "AIN6", "AIN8", "AIN10"};
  const std::vector<std::string> address_labels_ = {"PT-02", "PT-03", "PT-04", "PT-05", "PT-06", "LC-01", "LC-02", "LC-03"};
  const std::shared_ptr<Broadcaster<PressureData>> pressure_broadcaster_;
  const std::shared_ptr<Broadcaster<ForceData>> force_broadcaster_;

  std::array<std::shared_ptr<PressureData>, num_pts_> pt_prototypes_;
  std::array<std::shared_ptr<ForceData>, num_lcs_> lc_prototypes_;
};

#endif //DAC_QT_COLDFLOWSINKSTRATEGY_H
