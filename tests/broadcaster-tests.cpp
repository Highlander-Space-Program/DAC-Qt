#include <gtest/gtest.h>

#include "../broadcast/Broadcaster.h"
#include "../broadcast/Sink.h"
#include "../models/ForceData.h"

class BroadcasterTest : public testing::Test{
protected:
  std::shared_ptr<Broadcaster<TelemetryData>> broadcaster = Broadcaster<TelemetryData>::getInstance();
  std::shared_ptr<Broadcaster<ForceData>> forceBroadcaster = Broadcaster<ForceData>::getInstance();
};

TEST_F(BroadcasterTest, ShouldBroadcast) {
  TelemetryData data;
  data.label = "Test";
  broadcaster->subscribe([](const TelemetryData *data){
    EXPECT_NE(data, nullptr);
    ASSERT_EQ(data->label, "Test");
  });

  broadcaster->broadcastBase(&data);
}

TEST_F(BroadcasterTest, SinkShouldSend) {
  TelemetryData data;
  data.label = "Test";
  broadcaster->subscribe([](const TelemetryData *data){
    EXPECT_NE(data, nullptr);
    ASSERT_EQ(data->label, "Test");
  });
  Sink sink({broadcaster});

  sink.sendData({&data});
}

TEST_F(BroadcasterTest, SinkShouldSendTyped) {
  ForceData forceData;
  forceData.label = "Force Test";
  broadcaster->subscribe([](const TelemetryData *data){
    EXPECT_NE(data, nullptr);
    ASSERT_EQ(data->label, "Force Test");
  });

  Sink sink({forceBroadcaster});
  sink.sendData({&forceData});
}
