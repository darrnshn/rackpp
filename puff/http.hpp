#pragma once

namespace puff
{
  enum class verbs
  {
    GET, POST, PUT, DELETE, PATCH, NUM_VERBS
  };

  using http = verbs;
}
