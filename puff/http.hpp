#pragma once

namespace puff
{
  enum class verb
  {
    GET, POST, PUT, DELETE, PATCH, NUM_VERBS
  };

  using http = verb;
}
