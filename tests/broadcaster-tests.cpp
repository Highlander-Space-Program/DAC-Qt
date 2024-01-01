#include <gtest/gtest.h>

#include "../broadcast/Broadcaster.h"
#include "../broadcast/Sink.h"
#include "../models/ForceData.h"

class BroadcasterTest : public testing::Test{
protected:
  void SetUp() override {
    data.label = "Test";
    forceData.label = "Force Test";
    broadcaster->subscribe(callback);
    forceBroadcaster->subscribe(forceCallback);
  }

  std::shared_ptr<Broadcaster<TelemetryData>> broadcaster = Broadcaster<TelemetryData>::getInstance();
  std::shared_ptr<Broadcaster<ForceData>> forceBroadcaster = Broadcaster<ForceData>::getInstance();

  TelemetryData data;
  ForceData forceData;

  static void callback(const TelemetryData* data) {
    EXPECT_NE(data, nullptr);
    ASSERT_EQ(data->label, "Test");
  }
  static void forceCallback(const ForceData* data) {
    EXPECT_NE(data, nullptr);
    ASSERT_EQ(data->label, "Force Test");
  }
};

TEST_F(BroadcasterTest, ShouldBroadcast) {
  broadcaster->broadcastBase(&data);
}

TEST_F(BroadcasterTest, SinkShouldSend) {
  Sink sink({broadcaster});
  sink.sendData({&data});
}

TEST_F(BroadcasterTest, SinkShouldSendTyped) {
  Sink sink({forceBroadcaster});
  sink.sendData({&forceData});
}
