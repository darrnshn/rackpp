namespace puff
{

class app
{
public:
  app(const std::string& name = "app");

  const std::string& name() const;

private:
  std::string m_name;
};

using simple_app = app;

}

#include "app.inl"
