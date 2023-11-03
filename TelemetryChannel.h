#ifndef TELEMETRYCHANNEL_H
#define TELEMETRYCHANNEL_H

#include <functional>
#include <map>
#include <queue>

template <class T>
class TelemetryMessage {
public:
  T data;
};

template <class T>
class TelemetryChannel
{
public:
  inline void subscribe(std::function<void(const std::vector<T>&, const size_t)> callback) {
    callbacks_.push_back(callback);
  }

  inline void broadcast(const std::vector<T> &buffer, const size_t size) const noexcept {
    for (const auto& callback : callbacks_) {
      callback(buffer, size);
    }
  }

private:
  std::vector<
    std::function<void(const std::vector<T>&, const size_t)>
    > callbacks_;
};

template <class T>
class TelemetrySink {
public:
  TelemetrySink(TelemetryChannel<T>* channel) : channel_{channel} { }
  virtual ~TelemetrySink() =default;
protected:
  TelemetryChannel<T>* channel_ {nullptr};
};

#endif // TELEMETRYCHANNEL_H
