#include "Broadcaster.hpp"

#include <iostream>
#include <vector>

// Explicit instantiation of the Broadcaster template for expected types
template <typename T>
Broadcaster<T>::Broadcaster() {}

template <typename T>
Broadcaster<T>::Broadcaster(std::vector<void(*)(const T*)> callbacks) : callbacks_(callbacks) {}

template <typename T>
void Broadcaster<T>::subscribe(void(*callback)(T const*)) {
    this->callbacks_.push_back(callback);
}

template <typename T>
void Broadcaster<T>::broadcast(T* item) {
  // if it is the wrong kind of broadcaster, item will be nullptr
  if (!item) {
    return;
  }

  std::cout << "Broadcasting data: " << item->voltage2 << '\n';
    for (auto& callback : this->callbacks_) {
        callback(item);
    }
}

template <typename T>
void Broadcaster<T>::broadcast(std::vector<T*> items) {
  std::cout << "Broadcasting\n";
    for (auto& item : items) {
        broadcast(item);
    }
}

template <typename T>
void Broadcaster<T>::broadcastBase(TelemetryDataBase* item) {
    // This cast is safe only if T is guaranteed to be TelemetryDataBase or derived from it

    this->broadcast(dynamic_cast<T*>(item));
}

template <typename T>
void Broadcaster<T>::broadcastBase(std::vector<TelemetryDataBase*> items) {
    for (auto baseItem : items) {
        // This cast is safe only if T is guaranteed to be TelemetryDataBase or derived from it
        T* item = dynamic_cast<T*>(baseItem);
        if (item) { // Check if the dynamic cast succeeded
            std::cout << "Valid Cast";
            broadcast(item);
        } else {
            std::cout << "Invalid Cast";
        }
    }
}

// If other methods of the template class Broadcaster need to be defined outside of the header,
// their definitions would follow here, using the same template <typename T> prefix.
template class Broadcaster<MassData>;
template class Broadcaster<PressureData>;
template class Broadcaster<TemperatureData>;
