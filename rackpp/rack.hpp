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

namespace detail
{

// From http://stackoverflow.com/questions/10766112/c11-i-can-go-from-multiple-args-to-tuple-but-can-i-go-from-tuple-to-multiple
// as a work around for GCC not supporting variadic lambda captures yet.
template <typename T, typename Tuple, bool Done, int Total, int... N>
struct construct_impl
{
  static T construct(Tuple&& args)
  {
    return construct_impl<T, Tuple, Total == 1 + sizeof...(N), Total, N..., sizeof...(N)>::construct(std::forward<Tuple>(args));
  }
};

template <typename T, typename Tuple, int Total, int... N>
struct construct_impl<T, Tuple, true, Total, N...>
{
  static T construct(Tuple&& args)
  {
    return T{std::get<N>(std::forward<Tuple>(args))...};
  }
};

template <typename T, typename Tuple>
T construct(Tuple&& args)
{
  using ttype = typename std::decay<Tuple>::type;
  return detail::construct_impl<T, Tuple, 0 == std::tuple_size<ttype>::value, std::tuple_size<ttype>::value>::construct(std::forward<Tuple>(args));
}

}

template <class Handler>
class rack
{
public:
  rack(const Handler& handler = Handler{})
    : m_handler(handler)
  {
  }

  template <class App, typename...Ts>
  void use(Ts&&...ts)
  {
    auto tuple = std::forward_as_tuple(ts...);
    m_constructors.push_back([tuple](const rackpp::app& app)
    {
      auto full_tuple = std::tuple_cat(std::make_tuple(std::ref(app)), tuple);
      return rackpp::app{detail::construct<App>(full_tuple)};
    });
  }

  template <class App, typename...Ts>
  void run(Ts&&...ts)
  {
    // Construct all the apps
    std::vector<rackpp::app> apps;
    apps.reserve(m_constructors.size() + 1);
    apps.emplace_back(App{std::forward<Ts>(ts)...});

    for (auto it = m_constructors.rbegin(); it != m_constructors.rend(); ++it)
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
  using constructor = std::function<rackpp::app(const rackpp::app&)>;

  Handler m_handler;
  std::vector<constructor> m_constructors;
};

}
