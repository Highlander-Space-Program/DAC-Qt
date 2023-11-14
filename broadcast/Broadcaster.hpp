#ifndef BROADCASTER_HPP
#define BROADCASTER_HPP

#include "TelemetryDataBase.h"

// BroadcasterBase class declaration
class BroadcasterBase {
public:
    virtual ~BroadcasterBase() {}
    virtual void broadcastBase(TelemetryDataBase* item) = 0;
    virtual void broadcastBase(std::vector<TelemetryDataBase*> items) = 0;
};

// Broadcaster template class declaration
template <typename T>
class Broadcaster : public BroadcasterBase {
private:
    std::vector<void(*)(T*)> callbacks_;
    Broadcaster();
    Broadcaster(std::vector<void(*)(T*)> callbacks);

public:
    static std::shared_ptr<Broadcaster<T>> getInstance() {
        static std::shared_ptr<Broadcaster<T>> instance(new Broadcaster<T>());
        return instance;
    }
    
    void subscribe(void(*callback)(T*));
    void broadcast(T* item);
    void broadcast(std::vector<T*> items);

    // Implementations of the virtual methods from BroadcasterBase will be provided in the .cpp file
    void broadcastBase(TelemetryDataBase* item) override;
    void broadcastBase(std::vector<TelemetryDataBase*> items) override;
};

// Include the definition of the getInstance method for all expected specializations
// if you know what types will be used with Broadcaster
// extern template class Broadcaster<MassData>;
// extern template class Broadcaster<PressureData>;
// extern template class Broadcaster<TemperatureData>;

#endif // BROADCASTER_HPP
