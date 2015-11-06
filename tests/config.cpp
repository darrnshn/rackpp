#include "gtest/gtest.h"
#include "puff.hpp"

TEST(Config, HasDefaultMode)
{
  puff::config cfg = puff::default_config();
  EXPECT_EQ("development", cfg.mode());
}

TEST(Config, CanSetMode)
{
  puff::config cfg = puff::default_config().mode("production");
  EXPECT_EQ("production", cfg.mode());
}
