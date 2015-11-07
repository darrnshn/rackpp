#pragma once

#define RACKPP_VERSION 0

#define RACKPP_MAJOR_VERSION    (RACKPP_VERSION / 100000)
#define RACKPP_MINOR_VERSION    (RACKPP_VERSION / 100 % 1000)
#define RACKPP_SUBMINOR_VERSION (RACKPP_VERSION % 100)

#include <utility>
#include <functional>

#include "app.hpp"
#include "environment.hpp"
#include "response.hpp"

namespace rackpp
{

template <class Handler>
class rack
{
public:
  rack(const Handler& handler = Handler{})
    : m_handler(handler)
  {
  }

  template <class App>
  void use()
  {
    m_constructs.push_back([](const rackpp::app& app)
    {
      return rackpp::app{App{app}};
    });
  }

  template <class App>
  void run()
  {
    // Construct all the apps
    std::vector<rackpp::app> apps;
    apps.reserve(m_constructs.size() + 1);
    apps.emplace_back(App{});

    for (auto it = m_constructs.rbegin(); it != m_constructs.rend(); ++it)
    {
      // The construct function will give each app a reference to the previous
      // app. Since we've reserved enough capacity, it is guaranteed that these
      // references will be valid until the end of this function.
      apps.push_back((*it)(apps.back()));
    }

    m_handler.run([&apps](environment&& env)
    {
      return apps.back()(std::move(env));
    });
  }

  const Handler& handler() const { return m_handler; }

private:
  using construct = std::function<rackpp::app(const rackpp::app&)>;

  Handler m_handler;
  std::vector<construct> m_constructs;
};

}
