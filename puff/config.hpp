namespace puff
{

class config
{
public:
  config()
    : m_mode("development")
  {

  }

  const std::string& mode() const
  {
    return m_mode;
  }

  friend class config_builder;

private:
  std::string m_mode;
};

bool operator==(const config& a, const config& b)
{
  return true;
}

class config_builder
{
public:
  operator config() const
  {
    return m_config;
  }

  config_builder& mode(const std::string& val)
  {
    m_config.m_mode = val;
    return *this;
  }

private:
  config m_config;
};

config_builder default_config()
{
  return config_builder{};
}

}
