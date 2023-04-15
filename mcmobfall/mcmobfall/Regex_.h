#pragma once
#ifndef REGEX__H
#define REGEX__H
#include <regex>
struct Regex
{
  std::regex UINT;
  std::regex HELP;
  std::regex HEALTH;
  std::regex HEARTS;
};
#endif // !REGEX_H
