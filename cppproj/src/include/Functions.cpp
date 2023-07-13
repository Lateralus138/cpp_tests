#include "Functions.h"
#include <iostream>
bool PathExists(std::filesystem::path path, Parameters &params, int error_code)
{
  bool dir_exists;
  try
  {
    dir_exists = std::filesystem::exists(path);
  }
  catch (std::filesystem::filesystem_error ferr)
  {
    std::cout << ferr.what() << '\n';
    params.error_value = error_code;
  }
  return dir_exists;
}
void StringAppendIf(bool test, std::string &variable, std::string if_, std::string else_)
{
  if (test) variable.append(if_);
  else variable.append(else_);
}
bool CreateDirectory(std::filesystem::path path, Parameters &params, int error_code)
{
    bool dir_created;
    try
    {
      dir_created = std::filesystem::create_directories(path);
    }
    catch (std::filesystem::filesystem_error ferr)
    {
      std::cerr << ferr.what() << '\n';
      params.error_value = error_code;
    }
    return dir_created;
}
