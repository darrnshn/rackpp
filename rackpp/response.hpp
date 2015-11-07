#pragma once

namespace rackpp
{

class response
{
public:
  using status_code_type = unsigned int;
  using headers_type = std::map<std::string, std::string>;

  response() = default;

  response(status_code_type status_code, const headers_type& headers,
           const std::string& body)
    : m_status_code(status_code)
    , m_headers(headers)
    , m_body(body)
  {
  }

  status_code_type status_code() const { return m_status_code; }
  headers_type headers() const { return m_headers; }
  const std::string& body() const { return m_body; }

private:
  status_code_type m_status_code;
  headers_type m_headers;
  std::string m_body;
};

}
