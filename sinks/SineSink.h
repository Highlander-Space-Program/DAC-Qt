#ifndef SINESINK_H
#define SINESINK_H

#include "broadcast/Sink.h"
#include "models/PressureData.h"

#include <thread>
#include <cmath>

class SineSink : public Sink {
public:
  SineSink(Broadcaster<PressureData> &broadcaster) : broadcaster_(broadcaster) {
    t_ = std::thread([&](){
      using namespace std::chrono;

      milliseconds step = 10ms;
      uint16_t samples = 10;

      std::vector<PressureData*> data(samples);
      auto ts = high_resolution_clock::now();
      while(!stop_) {
        for (size_t i=0; i<samples; i++, ts += step/samples) {
          milliseconds t = duration_cast<milliseconds>(ts.time_since_epoch());
          double x = std::sin(M_2_PI/(1000ms).count() * (t.count()));

          data[i] = new PressureData();
          data[i]->timestamp = ts + milliseconds(i);
          data[i]->pressure(x);
          data[i]->voltage(x);
        }

        broadcaster_.broadcast(data);
        for (size_t i=0; i<data.size(); i++) {
            delete data[i];
        }
//         data.clear();

        std::this_thread::sleep_for(std::chrono::milliseconds(step));
      }
    });
  }
  ~SineSink() {
    stop_ = true;
    t_.join();
  }

private:
  std::thread t_;
  bool stop_ = false;
  Broadcaster<PressureData> broadcaster_;
};


#endif //SINESINK_H
