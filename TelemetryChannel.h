#ifndef TELEMETRYCHANNEL_H
#define TELEMETRYCHANNEL_H

#include <functional>
#include <map>
#include <queue>

template <class T> class TelemetryChannel;

template <class T>
class TelemetryMessage {
public:
  T data;
};

template <class T>
class TelemetrySink {
public:
  virtual ~TelemetrySink() =default;
  virtual size_t get_buffer_size() const noexcept;
  void resgister_channel(const TelemetryChannel<T>& channel) { channel_ = channel; }
private:
  TelemetryChannel<T>& channel_;
};

template <class T>
class TelemetryChannel
{
public:
  TelemetryChannel() {
    write_ = read_ = message_queue_.begin();
  }

  /* Output */

  inline void subscribe(std::function<void(const TelemetryMessage<T>*,
                        const size_t size)> callback) {
    callbacks_.push_back(callback);
  }

  /* Input */

  inline std::vector<const TelemetryMessage<T>&> register_sink(const TelemetrySink<T>& sink) {
    buffers_[sink].resize(sink.get_buffer_size());
    return buffers_[sink];
  }
  inline std::vector<const TelemetryMessage<T>&> get_sink_buffer(const TelemetrySink<T>& sink) { return buffers_[sink]; }
  inline void clear_buffer(const TelemetrySink<T>& sink) {
    auto buffer = buffers_[sink];
    std::move(buffer.begin(), buffer.end(), write_);
  }

  // Approximately 3x the storage needed for 60 seconds of data at 1 MHz (wanted something arbitrarily large)
  static constexpr size_t default_queue_size =1'000'000*sizeof(TelemetryMessage<double>)*60*3;

private:
  std::vector<
    std::function<void(const TelemetryMessage<T>&)>
    > callbacks_;

  // TODO guaranteed deretministic buffer or double buffering
  std::vector<const TelemetryMessage<T>&> message_queue_;
  typename std::vector<const TelemetryMessage<T>&>::iterator write_, read_;

  std::map<
    const TelemetrySink<T>*,
    std::vector<const TelemetryMessage<T>&>
    > buffers_;
};

#endif // TELEMETRYCHANNEL_H
