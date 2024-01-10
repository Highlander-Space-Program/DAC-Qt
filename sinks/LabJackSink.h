#ifndef DAC_QT_LABJACKSINK_H
#define DAC_QT_LABJACKSINK_H

#include <map>

#include "broadcast/Sink.h"

class LabJackSinkStrategy;

class LabJackException : public std::exception {
public:
  LabJackException(int error) : error_{error} { }
  const char* what() const noexcept override;
  const int error_;
};
class LabJackSink : public Sink {
public:
  LabJackSink();
  virtual ~LabJackSink();

  void open(int device_type, const std::string &identifier, int connection_type);
  void openS(const std::string &device_type, const std::string &identifier, const std::string &connection_type);

  void start_stream(int scans_per_read, double scan_rate, std::shared_ptr<LabJackSinkStrategy> strategy);
  void stop_stream() const;

  // Accessors
  int device_type() const noexcept { return device_type_; }
  std::string identifier() const noexcept { return identifier_; }
  int handle() const noexcept { return handle_; }
  int connection_type() const noexcept { return connection_type_; }
  int serial_number() const noexcept { return serial_number_; }
  int ip_address() const noexcept { return ip_address_; }
  int port() const noexcept { return port_; }
  int max_bytes_per_mb() const noexcept { return max_bytes_per_mb_; }

  struct stream_callback_args {
    int handle;
    size_t scans_per_read;
    double scan_rate;
    std::shared_ptr<LabJackSinkStrategy> strategy;
  };

private:
  stream_callback_args stream_args_;

  void (*stream_callback_)(void*);

  void update_handle_info();

private:
  bool is_open_ = false;
  std::string identifier_;
  int handle_;
  int connection_type_;
  int serial_number_;
  int ip_address_;
  int port_;
  int max_bytes_per_mb_;
  int device_type_;
};

#endif //DAC_QT_LABJACKSINK_H
