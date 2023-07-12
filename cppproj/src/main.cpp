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
  // TODO Finish program
  const std::string PARENTPATH = params.path_name;
  const std::map<std::string, std::string> CHILDDIRECTORIES =
  {{"source", "src/include"}, {"library", "src/lib"}};
  for (auto const &[key, value] : CHILDDIRECTORIES)
  {
    directories.setNewPath(key, PARENTPATH);
    directories.append(key, value);
  }
  std::map<std::string, std::filesystem::path> paths =
    directories.getPaths();
//  for (std::pair const &[key, value] : paths)
//  {
//    std::cout << value << ": " << std::filesystem::exists(value) << '\n';
//  }
  return EXIT_SUCCESS;
}
