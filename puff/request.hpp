#pragma once

namespace puff
{

class request
{
public:
  request(const puff::verb& verb, const std::string& url)
    : m_verb(verb), m_url(url)
  {
  }

  const puff::verb& verb() const { return m_verb; }
  const std::string& url() const { return m_url; }

private:
  puff::verb m_verb;
  std::string m_url;
};

}
