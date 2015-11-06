namespace puff
{

app::app(const std::string& name)
  : m_name(name)
{
}

const std::string& app::name() const
{
  return m_name;
}

}
