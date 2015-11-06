namespace puff
{

class config
{
public:
  friend class config_builder;
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

private:
  config m_config;
};

config_builder default_config()
{
  return config_builder{};
}

}
