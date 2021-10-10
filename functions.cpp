#include "functions.h"
#include <iostream>

void string_to_vector
(
  std::string _string_,
  std::vector <std::string> & _vector_,
  std::string _delim_
)
{
  size_t delim_pos = 0;
  while ((delim_pos = _string_.find (_delim_)) != std::string::npos)
  {
    _vector_.push_back (_string_.substr(0, delim_pos));
    _string_.erase (0, delim_pos + _delim_.length());
  }
  _vector_.push_back (_string_);
}

int return_function (error _error_, bool _verb_, bool _mono_)
{
  if (_error_.error > 0 && _verb_)
  {
      std::cerr
        << ((!_mono_)?"\x1b[91m":"")
        << _error_.message
        << ((!_mono_)?"\x1b[0m":"")
        << std::endl;
  }
  return _error_.error;
}
