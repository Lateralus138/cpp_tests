#include "Strings.h"
#include <sstream>
std::string Strings::string_from_string_vector
(std::vector <std::string> _string_vector_)
{
  std::string _string = "";
  auto _size = (int) _string_vector_.size ();
  if (_size > 0)
  {
    for (auto _index = 0; _index < _size; _index++)
    {
      if (_index > 0) _string.push_back (' ');
      _string.append (_string_vector_ [_index]);
    }
  }
  return _string;
}

std::string Strings::wrap_string
(std::string _string_, wrap_data _wrap_data_)
{
  return
      _wrap_data_.left
    + _string_
    + _wrap_data_.right;
}

std::string Strings::wrap
(wrap_data_string _wrap_data_string_)
{
  return
      _wrap_data_string_.left
    + _wrap_data_string_.body
    + _wrap_data_string_.right;
}

void Strings::replace_in_string
(
  std::string & _string_,
  std::string _to_replace_,
  std::string _replace_with_
)
{
    size_t to_replace_pos = _string_.find (_to_replace_);
    while ( to_replace_pos != std::string::npos)
    {
        _string_.replace
        (
          to_replace_pos,
          _to_replace_.size(),
          _replace_with_
        );
        to_replace_pos =
          _string_.find
          (
            _to_replace_,
            to_replace_pos +
            _replace_with_.size()
          );
    }
}

void Strings::delim_to_vector
(
  std::vector<std::string> & _vector_,
  std::string _string_,
  char _delim_,
  bool _skip_empty_
)
{
  std::string line;
  std::stringstream stream (_string_);
  while (std::getline (stream, line, _delim_))
  {
    if (!_skip_empty_ && !line.empty ())
    {
      _vector_.push_back (line);
    }
    else
    {
      if (!line.empty ())
      {
        _vector_.push_back (line);
      }
    }
  }
}

// void Strings::strip_trailing_newline (std::string & _string_)
// {
//
// }
