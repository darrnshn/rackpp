#include "gtest/gtest.h"
#include "puff.hpp"

TEST(App, HasDefaultName)
{
  puff::simple_app app;
  EXPECT_EQ("app", app.name());
}

TEST(App, CanSpecifyAppName)
{
  puff::simple_app app{"myapp"};
  EXPECT_EQ("myapp", app.name());
}
}
