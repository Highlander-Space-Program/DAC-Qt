#include "ColdFlowSinkStrategy.h"

#include "LabJackM.h"

void ColdFlowSinkStrategy::configure_device(const LabJackSink *sink) {
  LJM_eWriteName(sink->handle(), "AIN6_RANGE", 0.1);
  LJM_eWriteName(sink->handle(), "AIN8_RANGE", 0.1);
  LJM_eWriteName(sink->handle(), "AIN10_RANGE", 0.1);
  LJM_eWriteName(sink->handle(), "AIN6_NEGATIVE_CH", 7);
  LJM_eWriteName(sink->handle(), "AIN8_NEGATIVE_CH", 9);
  LJM_eWriteName(sink->handle(), "AIN10_NEGATIVE_CH", 11);
}
