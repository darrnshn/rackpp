#pragma once

#include <memory>

#include "response.hpp"
#include "environment.hpp"

namespace rackpp
{

class app_interface
{
public:
  virtual ~app_interface() { }
  virtual response call(environment&& env) const = 0;
  virtual std::unique_ptr<app_interface> clone() const = 0;
};

template <class T>
class app_impl : public app_interface
{
public:
  template <typename...Ts>
  app_impl(Ts&&...ts)
    : m_t(std::forward<Ts>(ts)...)
  {
  }

  virtual response call(environment&& env) const override
  {
    return m_t(std::move(env));
  }

  std::unique_ptr<app_interface> clone() const override
  {
    return std::unique_ptr<app_impl<T>>(new app_impl<T>(m_t));
  }

private:
  T m_t;
};

class app
{
public:
  template <typename T>
  app(T t)
    : m_base(std::unique_ptr<app_impl<T>>(new app_impl<T>(std::move(t))))
  {
  }

  app(app&& other) noexcept
    : m_base(std::move(other.m_base))
  {
  }

  void swap(app& other) noexcept
  {
    std::swap(m_base, other.m_base);
  }

  app& operator=(app other)
  {
    swap(other);
    return *this;
  }

  response operator()(environment&& env) const
  {
    return m_base->call(std::move(env));
  }

private:
  std::unique_ptr<app_interface> m_base;
};

}
