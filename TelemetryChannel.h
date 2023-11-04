#ifndef TELEMETRYCHANNEL_H
#define TELEMETRYCHANNEL_H

#include <functional>
#include <vector>

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

#endif // TELEMETRYCHANNEL_H
