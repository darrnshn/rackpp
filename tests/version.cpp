#include "gtest/gtest.h"
#include "puff.hpp"

TEST(Version, IsUpToDate)
{
  EXPECT_EQ(0, PUFF_MAJOR_VERSION);
  EXPECT_EQ(0, PUFF_MINOR_VERSION);
  EXPECT_EQ(0, PUFF_SUBMINOR_VERSION);
}
