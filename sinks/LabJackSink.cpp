#include "LabJackSink.h"

#include <utility>

#include "LabJackM.h"
#include "LabJackSinkStrategy.h"

const char* LabJackException::what() const noexcept {
  char* buffer = new char[LJM_STRING_MAX_SIZE];
  LJM_ErrorToString(error_, buffer);
  return buffer;
}

LabJackSink::LabJackSink() {
  stream_callback_ = [](void* args){
    auto stream_args = reinterpret_cast<stream_callback_args*>(args);

    const size_t size = stream_args->scans_per_read * stream_args->strategy->address_list().size();
    std::vector<double> arr(size); // Use std::vector for dynamic allocation
    int error, device_scan_backlog, ljm_scan_backlog;
    error = LJM_eStreamRead(stream_args->handle,
                            arr.data(), // Pass pointer to the underlying array
                            &device_scan_backlog,
                            &ljm_scan_backlog);
    if (error) { throw LabJackException(error); }

    stream_args->strategy->process(arr.data(), stream_args);
  };
}

LabJackSink::~LabJackSink() {
  if (is_open_) {
    LJM_Close(handle_);
  }
}

void LabJackSink::open(int device_type, const std::string &identifier, int connection_type) {
  int error = LJM_Open(
          device_type,
          connection_type,
          identifier.c_str(),
          &handle_);
  if (error) { throw LabJackException(error); }
  identifier_ = identifier;
  is_open_ = true;
  update_handle_info();
}

void LabJackSink::openS(const std::string &device_type,
                       const std::string &identifier,
                       const std::string &connection_type) {
  int error = LJM_OpenS(
          device_type.c_str(),
          connection_type.c_str(),
          identifier.c_str(),
          &handle_);
  if (error) { throw LabJackException(error); }
  identifier_ = identifier;
  is_open_ = true;
  update_handle_info();
}

void LabJackSink::start_stream(int scans_per_read,
                              double scan_rate,
                              std::shared_ptr<LabJackSinkStrategy> strategy) {
  strategy->configure_device(this);

  const size_t num_addresses = strategy->address_list().size();
  int* scan_list = new int[num_addresses];
  for (size_t i {0}; i < num_addresses; i++) {
    int address, type;
    LJM_NameToAddress(strategy->address_list()[i].c_str(), &address, &type);
    scan_list[i] = address;
  }
  stream_args_ = {
          handle_,
          static_cast<size_t>(scans_per_read),
          scan_rate,
          std::move(strategy),
  };
  int error = LJM_eStreamStart(stream_args_.handle,
                           static_cast<int>(stream_args_.scans_per_read),
                           static_cast<int>(num_addresses),
                           scan_list,
                           &scan_rate);
  if (error) { throw LabJackException(error); }

  error = LJM_SetStreamCallback(handle_, stream_callback_, reinterpret_cast<void*>(&stream_args_));
  if (error) { throw LabJackException(error); }
}

void LabJackSink::stop_stream() const {
  int error = LJM_eStreamStop(handle());
  if (error) { throw LabJackException(error); }
}

void LabJackSink::update_handle_info() {
  int error = LJM_GetHandleInfo(
          handle_,
          &device_type_,
          &connection_type_,
          &serial_number_,
          &ip_address_,
          &port_,
          &max_bytes_per_mb_);
  if (error) { throw LabJackException(error); }
}
