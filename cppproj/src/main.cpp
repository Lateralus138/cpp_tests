#include "cppproj.h"
int main(int argc, const char *argv[])
{
  set_signal_handlers(sighandler);
  Parameters params;
  Switches switches;
  bool ARGSPARSEDNOERROR = true;
  if (argc > 1)
  {
    ARGSPARSEDNOERROR = ArgParser(argc, argv, params, switches);
  }
  if (switches.is_help)
  {
    return EXIT_SUCCESS;
  }
  if (!ARGSPARSEDNOERROR)
  {
    return params.error_value;
  }
  Directories directories;
  Files files;
  std::string PARENTPATH = params.path_name;
  const std::map<std::string, std::string> CHILDDIRECTORIES =
  {{"source", "src/include"}, {"library", "src/lib"}};
  for (auto const &[key, value] : CHILDDIRECTORIES)
  {
    directories.setNewPath(key, PARENTPATH);
    directories.append(key, value);
  }
  std::map<std::string, std::filesystem::path> dir_paths =
    directories.getPaths();
  std::error_code dir_ec;
  for (std::pair const [key, value] : dir_paths)
  {
    std::string temp_message = "Checking if ";
    const std::string path = value.native().c_str();
    temp_message.append(path);
    temp_message.append(" exists...\n");
    std::cout << temp_message;
    temp_message.clear();
    const bool dir_exists = PathExists(value, params, 7);
    if (params.error_value > 0)
    {
      return params.error_value;
    }
    temp_message.append(path);
    StringAppendIf(dir_exists, temp_message,
                   " already exists and does not need to be created...\n",
                   " does not exist; attempting to create directory...\n");
    std::cout << temp_message;
    temp_message.clear();
    if (dir_exists) continue;
    const bool dir_created = CreateDirectory(value, params, 8);
    if (params.error_value > 0)
    {
      return params.error_value;
    }
    temp_message.append(path);
    temp_message.append(" was created successfully...\n");
    std::cout << temp_message;
    temp_message.clear();
  }
  return params.error_value;
}
