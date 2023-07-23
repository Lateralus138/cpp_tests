#include "Pipe.h"
#include <unistd.h>
#include <iostream>
void VectorFromPipe(std::vector<std::string> &vector, bool skipEmpty)
{
  std::string line;
  while (getline(std::cin, line))
  {
    if (line.empty() && skipEmpty)
    {
      continue;
    }
    vector.push_back(line);
  }
  std::cin.clear();
  FILE * tty = freopen("/dev/tty", "r", stdin);
}
