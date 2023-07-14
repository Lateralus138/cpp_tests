#include "Functions.h"
#include <iostream>
#include <fstream>
bool PathExists(std::filesystem::path path, Parameters &params, int error_code)
{
  bool path_exists;
  try
  {
    path_exists = std::filesystem::exists(path);
  }
  catch (std::filesystem::filesystem_error ferr)
  {
    std::cout << ferr.what() << '\n';
    params.error_value = error_code;
  }
  return path_exists;
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
bool CreateFile(std::filesystem::path path, std::string content, Parameters &params, int error_code)
{
  bool file_created = false;
  std::string message;
  std::ofstream out_file_stream(path.native().c_str());
  if (out_file_stream.is_open())
  {
    out_file_stream << content;
    if (out_file_stream.bad())
    {
      message = "Could not write to ";
      message.append(path);
      message.append(".\n");
      std::cerr << message;
      params.error_value = error_code;
      file_created = false;
    }
    else
    {
      message = path;
      message.append(" created successfully.\n");
      std::cerr << message;
      file_created = true;
    }
    out_file_stream.close();
  }
  else
  {
    message = "Could not open ";
    message.append(path);
    message.append(".\n");
    std::cerr << message;
    params.error_value = error_code;
    file_created = false;
  }
  return file_created;
}
