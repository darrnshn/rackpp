# include "gtest/gtest.h"
#include "rack.hpp"

struct MockHandler
{
  template <class Callback>
  void run(Callback callback)
  {
    rackpp::environment env;
    resp = callback(std::move(env));
  }

  rackpp::response resp;
};

struct MockMiddleware
{
  MockMiddleware(const rackpp::app& app, char exclaim = '!')
    : app(app), exclaim(exclaim)
  {
  }

  rackpp::response operator()(rackpp::environment&& env) const
  {
    auto resp = app(std::move(env));
    return {resp.status_code(), resp.headers(), resp.body() + exclaim};
  }

  const rackpp::app& app;
  char exclaim;
};

struct MockApp
{
  rackpp::response operator()(rackpp::environment&& env) const
  {
    return {200, {{"foo", "bar"}}, "hello world"};
  }
};

TEST(Rack, CanRunSingleApp)
{
  rackpp::rack<MockHandler> rack;
  rack.run<MockApp>();

  EXPECT_EQ(200, rack.handler().resp.status_code());
  EXPECT_EQ("hello world", rack.handler().resp.body());
}

TEST(Rack, CanRunMiddleware)
{
  rackpp::rack<MockHandler> rack;
  rack.use<MockMiddleware>();
  rack.run<MockApp>();

  EXPECT_EQ(200, rack.handler().resp.status_code());
  EXPECT_EQ("hello world!", rack.handler().resp.body());
}

TEST(Rack, CanRunMiddlewareWithParameters)
{
  rackpp::rack<MockHandler> rack;
  rack.use<MockMiddleware>('?');
  rack.run<MockApp>();

  EXPECT_EQ(200, rack.handler().resp.status_code());
  EXPECT_EQ("hello world?", rack.handler().resp.body());
}
