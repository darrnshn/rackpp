#pragma once

#include <bitset>

#include "http.hpp"
#include "request.hpp"

namespace puff
{

template <class Callback>
class route
{
public:
  route(const http& verb, const std::string& pattern, const Callback& callback)
    : m_verbs(1U << static_cast<std::size_t>(verb))
    , m_pattern(pattern)
    , m_callback(callback)
  {
  }

  bool supports_verb(const http& verb)
  {
    return m_verbs.test(static_cast<std::size_t>(verb));
  }

  bool matches(const request& req)
  {
    return supports_verb(req.verb()) && m_pattern == req.url();
  }

private:
  std::bitset<static_cast<std::size_t>(http::NUM_VERBS)> m_verbs;
  std::string m_pattern;
  Callback m_callback;
};

template <class Callback>
  route<Callback>
    make_route(const http& verb, const std::string& pattern,
               const Callback& callback)
{
  return route<Callback>(verb, pattern, callback);
}

}
