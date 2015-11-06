#include "gtest/gtest.h"
#include "puff.hpp"

TEST(Route, GenericRouteMatchesExactRequest)
{
  auto route = puff::make_route(puff::http::GET, "/", [](){ return ""; });

  puff::request req{puff::http::GET, "/"};
  EXPECT_TRUE(route.matches(req));
}
