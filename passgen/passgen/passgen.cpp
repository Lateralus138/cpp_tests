// ╔═══════════════════════════════════════════════════════════════════════════════╗
// ║ Password Generator (passgen) - Generate strong random passwords with various  ║
// ║ options.                                                                      ║
// ║ © 2024 Ian Pride - New Pride Software / Services                              ║
// ╚═══════════════════════════════════════════════════════════════════════════════╝
#include "stdafx.h"
void CheckOptionsAndSetOption(ArgumentParser& args, Options& options, std::vector<std::string>& option_vector, int set)
{
  if (args.optionsExist(option_vector))
    options.passwordIndex += set;
}
void SetOptionIsFull(Options& options, bool is, int value)
{
  options.passwordIsFull = is;
  options.passwordIndex = value;
}
void SetIsSpecialCompatible(Options& options, bool is)
{
  options.passwordIsSpecialCompatible = is;
  int inc = ((options.passwordIndex & 8) ? 8 : 0);
  if (is) options.passwordIndex += 8;
  else options.passwordIndex -= inc;
}
void SetIsSpecialExtended(Options& options, bool is)
{
  options.passwordIsSpecialExtended = is;
  int inc = ((options.passwordIndex & 16) ? 16 : 0);
  if (is) options.passwordIndex += 16;
  else options.passwordIndex -= inc;
}
void SetIsSpecialFull(Options& options, bool is)
{
  options.passwordIsSpecialFull = is;
  int inc = ((options.passwordIndex & 32) ? 32 : 0);
  if (is) options.passwordIndex += 32;
  else options.passwordIndex -= inc;
}
auto IsASwitch = [](std::string& option)
{
  return
  (
    Globals::ValueInVector(Globals::LENGOPTS, option) ||
    Globals::ValueInVector(Globals::UPPCOPTS, option) ||
    Globals::ValueInVector(Globals::LOWCOPTS, option) ||
    Globals::ValueInVector(Globals::DIGIOPTS, option) ||
    Globals::ValueInVector(Globals::SPCCOPTS, option) ||
    Globals::ValueInVector(Globals::SPCEOPTS, option) ||
    Globals::ValueInVector(Globals::SPCFOPTS, option)
  );
};
bool NonDefaultArgOptionsExist(ArgumentParser& args)
{
  return
    args.optionsExist(Globals::UPPCOPTS) || args.optionsExist(Globals::LOWCOPTS) ||
    args.optionsExist(Globals::DIGIOPTS) || args.optionsExist(Globals::SPCCOPTS) ||
    args.optionsExist(Globals::SPCEOPTS) || args.optionsExist(Globals::SPCFOPTS);
}
int ParseArguments(ArgumentParser& args, Options& options)
{
  if (NonDefaultArgOptionsExist(args))
  {
    SetOptionIsFull(options, false, 0);
  }
  if (args.optionsExist(Globals::HELPOPTS))
  {
    std::cout << Globals::HELPMESSAGE;
    return -1;
  }
  if (args.optionsExist(Globals::LENGOPTS))
  {
    std::string option = args.getOptions(Globals::LENGOPTS);
    if (option.empty() || IsASwitch(option)) return 1;
    try
    {
      options.passwordLength = std::stoi(option);
    }
    catch (std::invalid_argument const& error)
    {
      std::cerr << error.what() << '\n';
      return 2;
    }
  }
  CheckOptionsAndSetOption(args, options, Globals::UPPCOPTS, 1);
  CheckOptionsAndSetOption(args, options, Globals::LOWCOPTS, 2);
  CheckOptionsAndSetOption(args, options, Globals::DIGIOPTS, 4);
  if (args.optionsExist(Globals::SPCCOPTS))
  {
    SetIsSpecialCompatible(options, true);
    SetIsSpecialExtended(options, false);
    SetIsSpecialFull(options, false);
  }
  if (args.optionsExist(Globals::SPCEOPTS))
  {
    SetIsSpecialExtended(options, true);
    SetIsSpecialCompatible(options, false);
    SetIsSpecialFull(options, false);
  }
  if (args.optionsExist(Globals::SPCFOPTS))
  {
    SetIsSpecialFull(options, true);
    SetIsSpecialCompatible(options, false);
    SetIsSpecialExtended(options, false);
  }
  if (args.optionsExist(Globals::FULLOPTS))
  {
    SetOptionIsFull(options, true, 39);
    return EXIT_SUCCESS;
  }
  if (args.optionsExist(Globals::EXTDOPTS))
  {
    SetOptionIsFull(options, true, 23);
    return EXIT_SUCCESS;
  }
  if (args.optionsExist(Globals::COMPOPTS))
  {
    SetOptionIsFull(options, true, 15);
    return EXIT_SUCCESS;
  }
  return EXIT_SUCCESS;
}
int main(int argc, const char* argv[])
{
  SetConsoleTitle(L"Password Generator");
  std::srand(static_cast<unsigned int>(GetTickCount64()));
  Options options = { 12, true, false, false, false, 15 };
  Errors errors =
  { {
      {1, "No value provided for [/l, /length]."},
      {2, "Passed value is not an integer."}
  } };
  ArgumentParser args(argc, argv, 1);
  const int PARSED = ParseArguments(args, options);
  if (PARSED == -1) return EXIT_SUCCESS;
  if (PARSED > 0) return Globals::PrintError(PARSED, errors);
  errno_t errt = {};
  for (int index = 0; index < options.passwordLength; index++)
  {
    unsigned int number = {};
    errt = rand_s(&number);
    const int randCharIndex = number % (Globals::CHARSMAP[options.passwordIndex].length()) + 0;
    //const int randCharIndex = rand_s(&number) % (Globals::CHARSMAP[options.passwordIndex].length()) + 0;
    Globals::PASSWORD.push_back(Globals::CHARSMAP[options.passwordIndex][randCharIndex]);
  }
  std::cout << Globals::PASSWORD << '\n';
  return EXIT_SUCCESS;
}
