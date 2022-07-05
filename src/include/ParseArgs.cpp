#include "ParseArgs.h"
#include <iostream>

void ParseArgs::parse(int min, int max)
{
  for (int i = min; i < max; i++)
  {
    std::cout << argV[i] << std::endl;
  }
}
