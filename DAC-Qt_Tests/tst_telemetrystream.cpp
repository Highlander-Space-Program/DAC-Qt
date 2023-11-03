
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../PressureData.h"
#include "../TelemetryChannel.h"

using namespace testing;

TEST(TelemetryStreamTest, ChannelCreateInputBuffer)
{
  TelemetrySink<PressureData> sink(50);
  TelemetryChannel<PressureData> channel;

  sink.register_channel(&channel);
  std::vector<TelemetryMessage<PressureData>*> buffer = channel.get_input_buffer(&sink);

  ASSERT_THAT(buffer.size(), Eq(50));
}

TEST(TelemetryStreamTest, ChannelCallsSubscriberCallback) {
  bool is_called = false;

  TelemetrySink<double> sink(1);
  TelemetryChannel<double> channel;
  channel.subscribe([&is_called](TelemetryChannel<double> *channel, const size_t size) {
    auto it = channel->get_read_iterator();
    double num = (*it)->data;
    std::cout << num << ' ';
    EXPECT_DOUBLE_EQ(num, 14.0);
    is_called = true;
  });
  sink.register_channel(&channel);
  std::vector<TelemetryMessage<double>*> &buffer = channel.get_input_buffer(&sink);
  buffer[0] = new TelemetryMessage<double>;
  buffer[0]->data = 14.0;
  channel.clear_buffer(&sink);
  buffer[0] = new TelemetryMessage<double>;
  buffer[0]->data = 15.0;
  channel.clear_buffer(&sink);

  ASSERT_THAT(is_called, Eq(true));
}
