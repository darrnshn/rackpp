#pragma once

#include "config.hpp"
#include "http.hpp"
#include "route.hpp"

namespace puff
{

class app
{
public:
  app(const std::string& name = "app");
  app(const puff::config& cfg);

  const std::string& name() const;

  const puff::config& config() const;

  template <class Callback>
  route<Callback> get(const std::string& pattern, const Callback& callback);

private:
  std::string m_name;
  puff::config m_config;
};

using simple_app = app;

}

#include "app.inl"
