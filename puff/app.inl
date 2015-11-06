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

}
