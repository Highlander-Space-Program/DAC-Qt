#ifndef BROADCASTER_HPP
#define BROADCASTER_HPP

#include <vector>
#include <memory>

#include <iostream>

#include "../models/TelemetryData.h"

// BroadcasterBase class declaration
class BroadcasterBase {
public:
    virtual ~BroadcasterBase() {}
    virtual void broadcastBase(TelemetryData* item) = 0;
    virtual void broadcastBase(std::vector<TelemetryData*> items) = 0;
};

// Broadcaster template class declaration
template <typename T>
class Broadcaster : public BroadcasterBase {
private:
  Broadcaster() =default;
  Broadcaster(std::vector<void(*)(T const*)> callbacks) : callbacks_(callbacks) {}
  std::vector<void(*)(const T*)> callbacks_;

public:
  static std::shared_ptr<Broadcaster<T>> getInstance() {
    static std::shared_ptr<Broadcaster<T>> instance(new Broadcaster<T>());
    return instance;
  }

  void subscribe(void(*callback)(const T*)) {
    this->callbacks_.push_back(callback);
  }
  void broadcast(T* item) {
    // if it is the wrong kind of broadcaster, item will be nullptr
    if (!item) {
      return;
    }

    for (auto& callback : this->callbacks_) {
        callback(item);
    }
  }
  void broadcast(std::vector<T*> items) {
    std::cout << "Broadcasting\n";
      for (auto& item : items) {
          broadcast(item);
      }
  }

    // Implementations of the virtual methods from BroadcasterBase will be provided in the .cpp file
  void broadcastBase(TelemetryData* item) override {
      this->broadcast(dynamic_cast<T*>(item));
  }
  void broadcastBase(std::vector<TelemetryData*> items) override {
    for (auto baseItem : items) {
      // This cast is safe only if T is guaranteed to be TelemetryData or derived from it
      T* item = dynamic_cast<T*>(baseItem);
      if (item) { // Check if the dynamic cast succeeded
        std::cout << "Valid Cast";
        broadcast(item);
      } else {
        std::cout << "Invalid Cast";
      }
    }
  }
};

// Include the definition of the getInstance method for all expected specializations
// if you know what types will be used with Broadcaster
#endif // BROADCASTER_HPP
