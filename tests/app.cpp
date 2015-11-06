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

TEST(App, CanSpecifyConfig)
{
  auto config = puff::default_config();
  puff::simple_app app{config};

  EXPECT_EQ(config, app.config());
}

TEST(App, CanCreateGetRouteToRoot)
{
  puff::simple_app app;
  auto route = app.get("/", []() { return ""; });

  EXPECT_TRUE(route.supports_verb(puff::http::GET));
  EXPECT_FALSE(route.supports_verb(puff::http::POST));
}
