#include <gtest/gtest.h>

#include "../sinks/LabJackSink.h"

TEST(LabJackSinkTest, OpensDevice) {
    LabJackSink sink;
    sink.open(0, "-2", 0);
    ASSERT_EQ(sink.serial_number(), -2);
}
