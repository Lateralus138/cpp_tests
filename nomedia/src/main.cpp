#include "pch.h"
int main(int argc, const char *argv[])
{
  Bench::start();
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
        const bool ISDIRECTORY = IsDirectory(*iter, params, 3, true);
        if (!ISDIRECTORY)
        {
          params.error_value = 4;
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
  if (params.error_value > 0)
  {
    return params.error_value;
  }
  if (params.paths.empty())
  {
    params.paths.push_back("./");
  }
  // TODO Continue program...
  for (std::vector<std::filesystem::path>::iterator iter = params.paths.begin(); iter != params.paths.end(); ++iter)
  {
    bool hasNoMedia = false;
    if (switches.isRecurse)
    {
      for (const std::filesystem::directory_entry &entry : std::filesystem::recursive_directory_iterator(*iter))
      {
        const bool ISFILE = IsFile(entry, params, 9, false);
        if (!ISFILE) continue;
        if (!switches.isForce)
        {
          const std::filesystem::path file(entry);
          if (file.stem() == ".nomedia")
          {
            hasNoMedia = true;
          }
        }
      }
    }
    else
    {
      for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(*iter))
      {
        const bool ISFILE = IsFile(entry, params, 9, false);
        if (!ISFILE) continue;
        if (!switches.isForce)
        {
          const std::filesystem::path file(entry);
          if (file.stem() == ".nomedia")
          {
            hasNoMedia = true;
          }
        }
      }
    }
    if (!hasNoMedia)
    {
      std::cout
          << ".nomedia doesn't exist in: "
          << (*iter) << std::endl;
    }
    else
    {
      std::cout
          << ".nomedia exists in: "
          << (*iter) << std::endl;
    }
  }
  Bench::stop();
  Bench::print_duration("Program duration: ", "\n", Bench::Start, Bench::Stop);
  return params.error_value;
}
