#include "pch.h"
int main(int argc, const char *argv[])
{
  std::vector<std::string> pipeVector;
  if (!isatty(STDIN_FILENO))
  {
    VectorFromPipe(pipeVector, true);
    if (!pipeVector.empty())
    {
      for (std::vector<std::string>::iterator iter = pipeVector.begin(); iter != pipeVector.end(); ++iter)
      {
        const bool exists = PathExists(*iter, params, 1, true);
        if (!exists)
        {
          params.error_value = 2;
          return params.error_value;
        }
        params.paths.push_back(*iter);
      }
    }
  }
  if (argc > 1)
  {
    const bool ARGPARSERRESULT = ArgParser(argc, argv, params, switches);
    if (!ARGPARSERRESULT)
    {
      return params.error_value;
    }
  }
  if (switches.isHelp)
  {
    return params.error_value;
  }

  // TODO Continue program...
  for (std::vector<std::filesystem::path>::iterator iter = params.paths.begin(); iter != params.paths.end(); ++iter)
  {
    std::cout << (*iter).native().c_str() << std::endl;
  }
  return params.error_value;
}
