#include "gtest/gtest.h"
#include "rack.hpp"

TEST(Version, IsUpToDate)
{
  EXPECT_EQ(0, RACKPP_MAJOR_VERSION);
  EXPECT_EQ(0, RACKPP_MINOR_VERSION);
  EXPECT_EQ(0, RACKPP_SUBMINOR_VERSION);
}
