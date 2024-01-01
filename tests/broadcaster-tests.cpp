#include <gtest/gtest.h>

#include "../broadcast/Broadcaster.h"

void callback(const TelemetryData* data) {
  EXPECT_NE(data, nullptr);
  ASSERT_EQ(data->label, "Test");
}

TEST(BroadcasterTest, ShouldBroadcast) {
  std::shared_ptr<BroadcasterBase> broadcaster = Broadcaster<TelemetryData>::getInstance();
  std::dynamic_pointer_cast<Broadcaster<TelemetryData>>(broadcaster)->subscribe(&callback);
  auto data = new TelemetryData();
  data->label = "Test";

  broadcaster->broadcastBase(data);
}