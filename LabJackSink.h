#ifndef LABJACKSINK_H
#define LABJACKSINK_H

#include <string>

#include "TelemetryChannel.h"
#include "PressureData.h"

class LabJackSink {
public:
  LabJackSink(std::string identifier="ANY", int device_typ=0);
  virtual ~LabJackSink();

  // TODO
  TelemetryChannel<PressureData>* pressure_channel;

  int open();
  int open(const std::string &identifier, int connection_type=0) ;
  int openS(std::string identifier, std::string connection_type);

  int start_stream(int scans_per_read, double scan_rate, const std::vector<std::string> &address_list);
  int stop_stream() const;

  // Accessors
  const int device_type() const noexcept { return device_type_; }
  std::string identifier() const noexcept { return identifier_; }
  int handle() const noexcept { return handle_; }
  int connection_type() const noexcept { return connection_type_; }
  int serial_number() const noexcept { return serial_number_; }
  int ip_address() const noexcept { return ip_address_; }
  int port() const noexcept { return port_; }
  int max_bytes_per_mb() const noexcept { return max_bytes_per_mb_; }

protected:
  struct stream_callback_args {
    int handle;
    size_t scans_per_read;
    size_t num_addresses;
    double scan_rate;
    TelemetryChannel<PressureData>* channel; // TODO
    std::vector<int> scan_list;
  };
  stream_callback_args stream_args_;

  void (*stream_callback_)(void*);

  int update_handle_info();

protected:
  std::string identifier_;
  int handle_;
  int connection_type_;
  int serial_number_;
  int ip_address_;
  int port_;
  int max_bytes_per_mb_;

private:
  int device_type_;
};

#endif //LABJACKSINK_H
