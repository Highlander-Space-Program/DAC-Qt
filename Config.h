#ifndef DAC_QT_CONFIG_H
#define DAC_QT_CONFIG_H

#include <string>

class Config {
public:
  class LabJackConfig {
  public:
    std::string identifier;
    std::string device_type;
    std::string connection_type;
  };
  class InfluxConfig {
  public:
    std::string protocol;
    std::string address;
    std::string port;
    std::string token;
    std::string db;
  };

  LabJackConfig labjack;
  InfluxConfig influx;
};

#endif //DAC_QT_CONFIG_H
