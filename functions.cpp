#include "functions.h"

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
