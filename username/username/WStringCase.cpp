#include "WStringCase.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
WStringCase::WStringCase(std::wstring _wstring)
{
  setString(_wstring);
}
void WStringCase::setString(std::wstring _wstring)
{
  wstring_ = _wstring;
}
std::wstring WStringCase::getString()
{
  return wstring_;
}
std::wstring WStringCase::upper()
{
  std::transform(wstring_.begin(), wstring_.end(), wstring_.begin(),
    [](wchar_t chr) { return (wchar_t)std::toupper(chr); });
  return wstring_;
}
std::wstring WStringCase::lower()
{
  std::transform(wstring_.begin(), wstring_.end(), wstring_.begin(),
    [](wchar_t chr) { return (wchar_t)std::tolower(chr); });
  return wstring_;
}
std::wstring WStringCase::title()
{
  std::wstringstream wstream(wstring_);
  std::istream_iterator<std::wstring, wchar_t> begin(wstream);
  std::istream_iterator<std::wstring, wchar_t> end;
  std::vector<std::wstring> wstrings(begin, end);
  std::wstring wresult;
  for (int index = 0; index < (int)wstrings.size(); index++)
  {
    std::wstring temp = wstrings[index];
    std::transform(temp.begin(), (temp.begin() + 1), temp.begin(),
      [](wchar_t chr) { return (wchar_t)std::toupper(chr); });
    if (index > 0)
    {
      wresult.push_back(' ');
    }
    wresult.append(temp);
  }
  return wresult;
}