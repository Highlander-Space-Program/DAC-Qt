#ifndef BROADCASTER_HPP
#define BROADCASTER_HPP

#include "TelemetryData.h"
#include "ForceData.h"
#include "PressureData.h"
#include "TemperatureData.h"

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
    std::vector<void(*)(const T*)> callbacks_;
    Broadcaster();
    Broadcaster(std::vector<void(*)(T const*)> callbacks);

public:
    static std::shared_ptr<Broadcaster<T>> getInstance() {
        static std::shared_ptr<Broadcaster<T>> instance(new Broadcaster<T>());
        return instance;
    }
    
    void subscribe(void(*callback)(const T*));
    void broadcast(T* item);
    void broadcast(std::vector<T*> items);

    // Implementations of the virtual methods from BroadcasterBase will be provided in the .cpp file
    void broadcastBase(TelemetryData* item) override;
    void broadcastBase(std::vector<TelemetryData*> items) override;
};

// Include the definition of the getInstance method for all expected specializations
// if you know what types will be used with Broadcaster
#endif // BROADCASTER_HPP
