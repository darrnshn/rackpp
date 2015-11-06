namespace puff
{

app::app(const std::string& name)
  : m_name(name)
{
}

app::app(const puff::config& cfg)
  : m_config(cfg)
{
}

const std::string& app::name() const
{
  return m_name;
}

const puff::config& app::config() const
{
  return m_config;
}

template <class Callback>
route<Callback>
  app::get(const std::string& pattern, const Callback& callback)
  {
    return route<Callback>({ http::GET }, pattern, callback);
  }

}
