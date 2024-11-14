#include "stdafx.h"
#include "Globals.h"
extern struct Options options;
extern struct Errors errors;
namespace Globals
{
  unsigned int UINT_MAX_ENSURE = (unsigned int) - 1;
  //bool IsHexadecimalString(const std::string& string)
  bool IsHexadecimalString(std::string_view string)
  {
    std::string string_ = std::string(string);
    StripHexadecimalPrefix(string_);
    if ((string_.empty()) || (string_.size() > 16)) return false;
    return (string_.find_first_not_of("0123456789abcdefABCDEF", 0) == std::string::npos);
  }
  std::map<std::string, int> HexToRGB(int hex)
  {
    std::map<std::string, int> RGB =
    {
      {"Red", ((hex >> 0x00000010) & 0xff)},
      {"Green", ((hex >> 0x00000008) & 0xff)},
      {"Blue", (hex & 0xff)}
    };
    return RGB;
  }
  void StripHexadecimalPrefix(std::string& string)
  {
    StringReplace(string, "#", "");
    StringReplace(string, "0x", "");
  }
  void StringReplace(std::string& haystack, const std::string& needle, const std::string& replace)
  {
    size_t position = 0;
    while ((position = haystack.find(needle, position)) != std::string::npos)
    {
      haystack.replace(position, needle.size(), replace);
      position += replace.size();
    }
  }
  bool ValueInRange(const long long int& value_, const long long int& min_, const long long int& max_)
  {
    return ((value_ >= min_) && (value_ <= max_));
  }
  double ColorDiff(int colorA, int colorB)
  {
    std::map<std::string, int> ca = HexToRGB(colorA);
    std::map<std::string, int> cb = HexToRGB(colorB);
    return std::sqrt(
      std::pow(std::abs(ca["Red"] - cb["Red"]), 2) +
      std::pow(std::abs(ca["Green"] - cb["Green"]), 2) +
      std::pow(std::abs(ca["Blue"] - cb["Blue"]), 2)
    );
  }
  std::string IntToHexString(const int& number, const int& width, const std::string & prefix)
  {
    std::string hex_string = prefix;
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(width) << std::hex << number;
    hex_string.append(ss.str());
    return hex_string;
  }
  bool IsStringInt(const std::string& string)
  {
    std::istringstream iss(string);
    int i;
    return (iss >> i && iss.eof());
  }
}