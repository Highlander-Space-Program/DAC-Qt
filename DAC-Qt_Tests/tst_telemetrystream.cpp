
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../PressureData.h"
#include "../TelemetryChannel.h"

using namespace testing;

TEST(TelemetryStreamTest, ChannelCreateInputBuffer)
{
  TelemetryChannel<TelemetryMessage<PressureData>> channel;
  channel.subscribe([](const std::vector<TelemetryMessage<PressureData>>& buffer, const size_t size) {
    ASSERT_TRUE(true);
  });

  std::vector<TelemetryMessage<PressureData>> buffer;
  TelemetryMessage<PressureData> msg;
  msg.data.pressure = 14;
  buffer.push_back(msg);
  channel.broadcast(buffer, buffer.size());
}
