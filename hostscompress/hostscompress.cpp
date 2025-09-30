// ╔══════════════════════════════════════════════════════════════════════════════════╗
// ║ Hosts Compress - Aggregate multiple domain names into single lines for local IP  ║
// ║ addresses of 0.0.0.0 and 127.0.0.1.                                              ║
// ║ © 2024 Ian Pride - New Pride Software / Services                                 ║
// ╚══════════════════════════════════════════════════════════════════════════════════╝
#include "pch.h"
extern const std::regex RGX_ISURL_000;
extern const std::regex RGX_URLS000_REPLACE;
extern const std::regex RGX_ISURL_127;
extern const std::regex RGX_URLS127_REPLACE;
const std::regex RGX_UINT("[0-9]+");
#include "Options.h"
#include "HostsFile.h" // Include the new HostsFile class







int main(int argc, const char* argv[])
{
  ProgramError perror;
  Options options;
  auto errorTest = [&](ProgramError& perror) // Changed to capture by reference
  {
    if (perror.getError().value > 0)
    {
      if (!options.isQuiet) perror.print(options.isOutputColor);
      std::exit(perror.getError().value);
    }
  };
  ArgumentParser argumentParser(argc, argv, 1);
  const unsigned int PARSEARGUMENTSRESULT = ParseArguments(argumentParser, options, perror);
  if (PARSEARGUMENTSRESULT > 0)
  {
    return PARSEARGUMENTSRESULT;
  }
  if (options.isHelp) return EXIT_SUCCESS;
  const std::string WINDIR = GetWindowsDirectoryAsString(perror, 5, "Could not retrieve the Windows Directory");
  errorTest(perror);
  if (options.inputFile.empty())
  {
    options.inputFile.append(WINDIR);
    options.inputFile.append("\\System32\\drivers\\etc\\hosts");
  }
  std::filesystem::path inputPath(options.inputFile);
  std::filesystem::path outputPath(options.outputFile);
  std::error_code ec;
  const bool INPUTPATHEXISTS = std::filesystem::exists(inputPath, ec);
  if (ec.value() > 0)
  {
    perror.addError(6, ec.message());
    perror.setError(6);
    perror.print(options.isOutputColor);
    return perror.getError().value;
  }
  if (!INPUTPATHEXISTS)
  {
    std::string message(inputPath.string());
    message.append(" does not exist");
    perror.addError(7, message);
    perror.setError(7);
    perror.print(options.isOutputColor);
    return perror.getError().value;
  }
  SetConsoleTitle(L"Hosts Compress");

  // Use the new HostsFile class
  HostsFile hostsFile(options, perror);
  hostsFile.process();
  errorTest(perror); // Check for errors after processing

  return EXIT_SUCCESS;
}