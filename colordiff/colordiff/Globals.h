#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H
struct Options
{
  bool verbose;
  bool minimum;
  bool maximum;
  long long minuend;
  std::vector<long long> subtrahends;
};
struct Errors
{
  std::map<int, std::string> messages;
};
namespace Globals
{
  extern unsigned int UINT_MAX_ENSURE;
  bool IsHexadecimalString(std::string_view string);
  std::map<std::string, int> HexToRGB(int hex);
  void StripHexadecimalPrefix(std::string& string);
  void StringReplace(std::string& haystack, const std::string& needle, const std::string& replace);
  bool ValueInRange(const long long int& value_, const long long int& min_, const long long int& max_);
  double ColorDiff(int colorA, int colorB);
  std::string IntToHexString(const int& number, const int& width, const std::string& prefix);
  bool IsStringInt(const std::string& string);
}
#endif // ! GLOBALS_H