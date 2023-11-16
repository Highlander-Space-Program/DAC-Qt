#include "LabJackSink.h"

#include "LabJackM.h"

LabJackSink::LabJackSink(std::string identifier, int device_type) : device_type_(device_type), identifier_(identifier) {
  stream_callback_ = [](void* args){
    auto stream_args = reinterpret_cast<stream_callback_args*>(args);

    const size_t size = stream_args->scans_per_read * stream_args->num_addresses;
    double arr[size];
    int error, device_scan_backlog, ljm_scan_backlog;
    error = LJM_eStreamRead(stream_args->handle,
                            arr,
                            &device_scan_backlog,
                            &ljm_scan_backlog);
    std::vector<PressureData> data(size);
    for (size_t i = 0; i < size; i++) {
      data[i].label = "PT-01";
      data[i].from_voltage(arr[i]);
    }
    stream_args->channel->broadcast(data, size);
  };
}

LabJackSink::~LabJackSink() {
  LJM_Close(handle_);
}

int LabJackSink::open() {
  return open(identifier_, connection_type_);
}

int LabJackSink::open(const std::string &identifier, int connection_type) {
  int error;
  error = LJM_Open(
          device_type_,
          connection_type,
          identifier.c_str(),
          &handle_);
  if (!error) {
    identifier_ = identifier;
    update_handle_info();
  }
  return error;
}

int LabJackSink::openS(std::string identifier, std::string connection_type) {
  int error;
  error = LJM_OpenS(
          "T7",
          connection_type.c_str(),
          identifier_.c_str(),
          &handle_);
  if (!error) {
    identifier_ = identifier;
    update_handle_info();
  }
  return error;
}

int LabJackSink::start_stream(int scans_per_read, double scan_rate, const std::vector<std::string> &address_list) {
  stream_args_ = {
          handle_,
          static_cast<size_t>(scans_per_read),
          address_list.size(),
          scan_rate,
          pressure_channel,
          std::vector<int>(address_list.size()),
  };

  for (size_t i {0}; i < address_list.size(); i++) {
    int address, type;
    LJM_NameToAddress(address_list[i].c_str(), &address, &type);
    stream_args_.scan_list[i] = address;
  }
  int error {0};
  error = LJM_eStreamStart(stream_args_.handle, stream_args_.scans_per_read, stream_args_.num_addresses, stream_args_.scan_list.data(), &stream_args_.scan_rate);
  if (error) return error;
  error = LJM_SetStreamCallback(handle_, stream_callback_, reinterpret_cast<void*>(&stream_args_));
  return error;
}

int LabJackSink::stop_stream() const {
  return LJM_eStreamStop(handle());
}


int LabJackSink::update_handle_info() {
  return LJM_GetHandleInfo(
          handle_,
          nullptr,
          &connection_type_,
          &serial_number_,
          &ip_address_,
          &port_,
          &max_bytes_per_mb_);
}
