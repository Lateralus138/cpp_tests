#include "ParseArgs.h"
#include <iostream>
#include <regex>
const std::regex R_HELP("^-([hH]|-[hH][eE][lL][pP])$");
void ParseArgs::parse(int min, int max)
{
  for (int i = min; i < max; i++)
  {
    std::string str = argV[i];
    if (std::regex_match(str, R_HELP))
    {
      std::cout << "HELP\n";
      std::exit(0);
    }
  }
}
