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
int ParseArguments(ArgumentParser& args, Options& options)
{
  std::vector<std::string> HELPOPTS = { "/?", "/h", "/help", "/H", "/HELP" };
  std::vector<std::string> LENGOPTS = { "/l", "/length", "/L", "/LENGTH" };
  std::vector<std::string> COMPOPTS = { "/c", "/compatible", "/C", "/COMPATIBLE" };
  std::vector<std::string> EXTDOPTS = { "/e", "/extended", "/E", "/EXTENDED" };
  std::vector<std::string> FULLOPTS = { "/f", "/full", "/F", "/FULL" };
  std::vector<std::string> UPPCOPTS = { "/uc", "/uppercase", "/UC", "/UPPERCASE" };
  std::vector<std::string> LOWCOPTS = { "/lc", "/lowercase", "/LC", "/LOWERCASE" };
  std::vector<std::string> DIGIOPTS = { "/d", "/digits", "/D", "/DIGITS" };
  std::vector<std::string> SPCCOPTS = { "/sc", "/specialcompatible", "/SC", "/SPECIALCOMPATIBLE" };
  std::vector<std::string> SPCEOPTS = { "/se", "/specialextended", "/SE", "/SPECIALEXTENDED" };
  std::vector<std::string> SPCFOPTS = { "/sf", "/specialfull", "/SF", "/SPECIALFULL" };
  auto IsASwitch = [HELPOPTS, LENGOPTS, UPPCOPTS, LOWCOPTS, DIGIOPTS, SPCCOPTS, SPCEOPTS, SPCFOPTS](std::string& option)
  {
    return
    (
      Globals::ValueInVector(LENGOPTS, option) ||
      Globals::ValueInVector(UPPCOPTS, option) ||
      Globals::ValueInVector(LOWCOPTS, option) ||
      Globals::ValueInVector(DIGIOPTS, option) ||
      Globals::ValueInVector(SPCCOPTS, option) ||
      Globals::ValueInVector(SPCEOPTS, option) ||
      Globals::ValueInVector(SPCFOPTS, option)
    );
  };
  if
  (
    args.optionsExist(UPPCOPTS) || args.optionsExist(LOWCOPTS) ||
    args.optionsExist(DIGIOPTS) || args.optionsExist(SPCCOPTS) ||
    args.optionsExist(SPCEOPTS) || args.optionsExist(SPCFOPTS)
  )
  {
    options.passwordIsFull = false;
    options.passwordIndex = 0;
  }
  if (args.optionsExist(HELPOPTS))
  {
    std::string message =
      "\n  Password Generator - Generate strong random passwords with various options."
      "\n  The default password style consists of uppercase, lowercase, digits, and"
      "\n  a few basic compatible special characters that work in most cases. This"
      "\n  program provides additional switches to allow an extended or full list of"
      "\n  special characters. You can also specify the use of only one type of"
      "\n  character and/or digit and mix and match."
      "\n\n  passgen [SWITCHES] [OPTIONS <ARGUMENT>]"
      "\n\n  @OPTIONS"
      "\n    /l, /length             The length of the password. Defaults to 12."
      "\n\n  @SWITCHES"
      "\n    /?, /h, /help           This help message."
      "\n    /c, /compatible         Full password with compatible special characters."
      "\n                            This is the default style and this switch is only"
      "\n                            necessary to override any previous options."
      "\n                            Compatible characters: " + Globals::CHARSSPECIALCOM +
      "\n    /e, /extended           Full password with extended characters."
      "\n                            If this switch is provided it overrides everthing"
      "\n                            except the /c, /compatible switch."
      "\n                            Extended characters: " + Globals::CHARSSPECIALEXT +
      "\n    /f, /full               Full password with all characters."
      "\n                            If this switch is provided it overrides everthing"
      "\n                            except the /c, /compatible and /e, /extended"
      "\n                            switches."
      "\n                            Full characters: " + Globals::CHARSSPECIALFUL +
      "\n    /uc, /uppercase         Use uppercase characters. This switch can be used"
      "\n                            with other singular types."
      "\n    /lc, /lowercase         Use lowercase characters. This switch can be used"
      "\n                            with other singular types."
      "\n    /d, /digits             Use digits/integers. This switch can be used"
      "\n                            with other singular types."
      "\n    /sc, /specialcompatible Use special compatible characters. This switch can"
      "\n                            be used with other singular types. Only one type of"
      "\n                            special character set can be used and the last"
      "\n                            /s* switch provided overrides other /s* switches."
      "\n    /se, /specialextended   Use special extended characters. This switch can"
      "\n                            be used with other singular types."
      "\n    /sf, /specialfull       Use special full characters. This switch can be"
      "\n                            used with other singular types."
      "\n\n";
    std::cout << message;
    return -1;
  }
  if (args.optionsExist(LENGOPTS))
  {
    std::string option = args.getOptions(LENGOPTS);
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
  CheckOptionsAndSetOption(args, options, UPPCOPTS, 1);
  CheckOptionsAndSetOption(args, options, LOWCOPTS, 2);
  CheckOptionsAndSetOption(args, options, DIGIOPTS, 4);
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
  if (args.optionsExist(SPCCOPTS))
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
      options.passwordIsSpecialFull = false;
      options.passwordIndex -= 32;
    }
  }
  if (args.optionsExist(SPCEOPTS))
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
      options.passwordIsSpecialFull = false;
      options.passwordIndex -= 32;
    }
  }
  if (args.optionsExist(SPCFOPTS))
  {
    options.passwordIsSpecialFull = true;
    options.passwordIndex += 32;
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
  if (args.optionsExist(FULLOPTS))
  {
    options.passwordIsFull = true;
    options.passwordIndex = 39;
    return EXIT_SUCCESS;
  }
  if (args.optionsExist(EXTDOPTS))
  {
    options.passwordIsFull = true;
    options.passwordIndex = 23;
    return EXIT_SUCCESS;
  }
  if (args.optionsExist(COMPOPTS))
  {
    options.passwordIsFull = true;
    options.passwordIndex = 15;
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
