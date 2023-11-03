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

template <class T> class TelemetrySink;

template <class T>
class TelemetryChannel
{
public:
  TelemetryChannel() : message_queue_(default_queue_size) {
    message_queue_.resize(50);
    write_ = message_queue_.begin();
    read_ = message_queue_.begin();
  }

  /* Output */

  inline void subscribe(std::function<void(TelemetryChannel<T>*, const size_t)> callback) {
    callbacks_.push_back(callback);
  }
  inline typename std::vector<TelemetryMessage<T>*>::const_iterator get_read_iterator() { return read_; }

  /* Input */

  inline void create_input_buffer(const TelemetrySink<T>* sink) {
    buffers_[sink].resize(sink->get_buffer_size());
  }
  inline std::vector<TelemetryMessage<T>*>& get_input_buffer(const TelemetrySink<T>* sink) { return buffers_[sink]; }
  inline void clear_buffer(const TelemetrySink<T>* sink, size_t size = 0) {
    auto buffer = get_input_buffer(sink);
    if (size == 0) {
      size = buffer.size();
    }

    std::move(buffer.begin(), buffer.begin()+size, write_);

    for (const auto &callback: callbacks_) {
      callback(this, size);
    }

    write_ += size;
    read_ += size;
  }

  // Approximately 3x the storage needed for 60 seconds of data at 1 kHz (wanted something arbitrarily large)
  static constexpr size_t default_queue_size = 1000*sizeof(TelemetryMessage<double>)*60*3;

private:
  std::vector<
    std::function<void(TelemetryChannel<T>*, const size_t)>
    > callbacks_;

  // TODO guaranteed deterministic buffer or double buffering
  std::vector<TelemetryMessage<T>*> message_queue_;
  typename std::vector<TelemetryMessage<T>*>::const_iterator read_;
  typename std::vector<TelemetryMessage<T>*>::iterator write_;

  std::map<
    const TelemetrySink<T>*,
    std::vector<TelemetryMessage<T>*>
    > buffers_;
};

template <class T>
class TelemetrySink {
public:
  TelemetrySink(const size_t buffer_size) : buffer_size_{buffer_size} { }
  virtual ~TelemetrySink() =default;
  virtual size_t get_buffer_size() const noexcept { return buffer_size_; }
  virtual TelemetryChannel<T>* get_channel() const noexcept { return channel_; }
  void register_channel(TelemetryChannel<T>* channel) {
    channel->create_input_buffer(this);
    channel_ = channel;
  }
private:
  size_t buffer_size_;
  TelemetryChannel<T>* channel_ {nullptr};
};


#endif // TELEMETRYCHANNEL_H
