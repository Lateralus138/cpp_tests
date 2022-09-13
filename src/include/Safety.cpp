#include "Safety.h"
#include <iostream>
namespace Safety
{
  void SystemCheck()
  {
    try
    {
      const bool CHECK = system(NULL);
      if (!CHECK)
      {
        errno = 255;
        throw std::runtime_error("System is not safe to use. Exiting program.\n");
      }
    }
    catch (std::runtime_error & runtime_error)
    {
      std::cerr << runtime_error.what();
      std::exit(int(errno));
    }
  }   
};