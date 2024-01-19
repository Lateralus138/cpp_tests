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
void SetOptionIsFullTrue(Options& options, int value)
{
  options.passwordIsFull = true;
  options.passwordIndex = value;
}
void SetIsSpecialFull(Options& options, bool is)
{
  options.passwordIsSpecialFull = is;
  if (is) options.passwordIndex += 32;
  else options.passwordIndex -= 32;
}
//std::vector<std::string> HELPOPTS = { "/?", "/h", "/help", "/H", "/HELP" };
//std::vector<std::string> LENGOPTS = { "/l", "/length", "/L", "/LENGTH" };
//std::vector<std::string> COMPOPTS = { "/c", "/compatible", "/C", "/COMPATIBLE" };
//std::vector<std::string> EXTDOPTS = { "/e", "/extended", "/E", "/EXTENDED" };
//std::vector<std::string> FULLOPTS = { "/f", "/full", "/F", "/FULL" };
//std::vector<std::string> UPPCOPTS = { "/uc", "/uppercase", "/UC", "/UPPERCASE" };
//std::vector<std::string> LOWCOPTS = { "/lc", "/lowercase", "/LC", "/LOWERCASE" };
//std::vector<std::string> DIGIOPTS = { "/d", "/digits", "/D", "/DIGITS" };
//std::vector<std::string> SPCCOPTS = { "/sc", "/specialcompatible", "/SC", "/SPECIALCOMPATIBLE" };
//std::vector<std::string> SPCEOPTS = { "/se", "/specialextended", "/SE", "/SPECIALEXTENDED" };
//std::vector<std::string> SPCFOPTS = { "/sf", "/specialfull", "/SF", "/SPECIALFULL" };
////auto IsASwitch = [HELPOPTS, LENGOPTS, UPPCOPTS, LOWCOPTS, DIGIOPTS, SPCCOPTS, SPCEOPTS, SPCFOPTS](std::string& option)
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
int ParseArguments(ArgumentParser& args, Options& options)
{
  //std::vector<std::string> HELPOPTS = { "/?", "/h", "/help", "/H", "/HELP" };
  //std::vector<std::string> LENGOPTS = { "/l", "/length", "/L", "/LENGTH" };
  //std::vector<std::string> COMPOPTS = { "/c", "/compatible", "/C", "/COMPATIBLE" };
  //std::vector<std::string> EXTDOPTS = { "/e", "/extended", "/E", "/EXTENDED" };
  //std::vector<std::string> FULLOPTS = { "/f", "/full", "/F", "/FULL" };
  //std::vector<std::string> UPPCOPTS = { "/uc", "/uppercase", "/UC", "/UPPERCASE" };
  //std::vector<std::string> LOWCOPTS = { "/lc", "/lowercase", "/LC", "/LOWERCASE" };
  //std::vector<std::string> DIGIOPTS = { "/d", "/digits", "/D", "/DIGITS" };
  //std::vector<std::string> SPCCOPTS = { "/sc", "/specialcompatible", "/SC", "/SPECIALCOMPATIBLE" };
  //std::vector<std::string> SPCEOPTS = { "/se", "/specialextended", "/SE", "/SPECIALEXTENDED" };
  //std::vector<std::string> SPCFOPTS = { "/sf", "/specialfull", "/SF", "/SPECIALFULL" };
  //auto IsASwitch = [HELPOPTS, LENGOPTS, UPPCOPTS, LOWCOPTS, DIGIOPTS, SPCCOPTS, SPCEOPTS, SPCFOPTS](std::string& option)
  //{
  //  return
  //  (
  //    Globals::ValueInVector(LENGOPTS, option) ||
  //    Globals::ValueInVector(UPPCOPTS, option) ||
  //    Globals::ValueInVector(LOWCOPTS, option) ||
  //    Globals::ValueInVector(DIGIOPTS, option) ||
  //    Globals::ValueInVector(SPCCOPTS, option) ||
  //    Globals::ValueInVector(SPCEOPTS, option) ||
  //    Globals::ValueInVector(SPCFOPTS, option)
  //  );
  //};
  if
  (
    args.optionsExist(Globals::UPPCOPTS) || args.optionsExist(Globals::LOWCOPTS) ||
    args.optionsExist(Globals::DIGIOPTS) || args.optionsExist(Globals::SPCCOPTS) ||
    args.optionsExist(Globals::SPCEOPTS) || args.optionsExist(Globals::SPCFOPTS)
  )
  {
    options.passwordIsFull = false;
    options.passwordIndex = 0;
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
  //if (args.optionsExist(UPPCOPTS))
  //{
  //  options.passwordIndex += 1;
  //}
  //if (args.optionsExist(LOWCOPTS))
  //{
  //  options.passwordIndex += 2;
  //}
  //if (args.optionsExist(DIGIOPTS))
  //{
  //  options.passwordIndex += 4;
  //}
  if (args.optionsExist(Globals::SPCCOPTS))
  {
    options.passwordIsSpecialCompatible = true;
    options.passwordIndex += 8;
    if (options.passwordIsSpecialExtended)
    {
      options.passwordIsSpecialExtended = false;
      options.passwordIndex -= 16;
    }
    if (options.passwordIsSpecialFull)
    {
      SetIsSpecialFull(options, false);
      //options.passwordIsSpecialFull = false;
      //options.passwordIndex -= 32;
    }
  }
  if (args.optionsExist(Globals::SPCEOPTS))
  {
    options.passwordIsSpecialExtended = true;
    options.passwordIndex += 16;
    if (options.passwordIsSpecialCompatible)
    {
      options.passwordIsSpecialCompatible = false;
      options.passwordIndex -= 8;
    }
    if (options.passwordIsSpecialFull)
    {
      SetIsSpecialFull(options, false);
      //options.passwordIsSpecialFull = false;
      //options.passwordIndex -= 32;
    }
  }
  if (args.optionsExist(Globals::SPCFOPTS))
  {
    SetIsSpecialFull(options, true);
    //options.passwordIsSpecialFull = true;
    //options.passwordIndex += 32;
    if (options.passwordIsSpecialCompatible)
    {
      options.passwordIsSpecialCompatible = false;
      options.passwordIndex -= 8;
    }
    if (options.passwordIsSpecialExtended)
    {
      options.passwordIsSpecialExtended = false;
      options.passwordIndex -= 16;
    }
  }
  if (args.optionsExist(Globals::FULLOPTS))
  {
    SetOptionIsFullTrue(options, 39);
    //options.passwordIsFull = true;
    //options.passwordIndex = 39;
    return EXIT_SUCCESS;
  }
  if (args.optionsExist(Globals::EXTDOPTS))
  {
    SetOptionIsFullTrue(options, 23);
    //options.passwordIsFull = true;
    //options.passwordIndex = 23;
    return EXIT_SUCCESS;
  }
  if (args.optionsExist(Globals::COMPOPTS))
  {
    SetOptionIsFullTrue(options, 15);
    //options.passwordIsFull = true;
    //options.passwordIndex = 15;
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
