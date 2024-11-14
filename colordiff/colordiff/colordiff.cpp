// ╔═════════════════════════════════════════════════════════════════════════════╗
// ║ Color Difference - Get the distance from one hexadecimal color to another.  ║
// ║ © 2024 Ian Pride - New Pride Software/Services                              ║
// ╚═════════════════════════════════════════════════════════════════════════════╝

#include "stdafx.h"

// Regular expression switch/argument compilations and their unary predicate function
// counterparts (std::find_if) for use in querying arguments in my argument parser class.
std::regex HELPREGEX("^/([\\?]|[hH]|[hH][eE][lL][pP])$");
static bool HelpRegex(const std::string& str) { return std::regex_match(str, HELPREGEX); }
std::regex MINUREGEX("^/([mM]|[mM][iI][nN][uU][eE][nN][dD])$");
static bool MinuRegex(const std::string& str) { return std::regex_match(str, MINUREGEX); }
std::regex VERBREGEX("^/([vV]|[vV][eE][rR][bB][oO][sS][eE])$");
static bool VerbRegex(const std::string& str) { return std::regex_match(str, VERBREGEX); }
std::regex MINIREGEX("^/([nN]|[mM][iI][nN][iI][mM][uU][mM])$");
static bool MiniRegex(const std::string& str) { return std::regex_match(str, MINIREGEX); }
std::regex MAXIREGEX("^/([xX]|[mM][iI][nN][uU][eE][nN][dD])$");
static bool MaxiRegex(const std::string& str) { return std::regex_match(str, MAXIREGEX); }

//static long long CheckIfStringIsHexAndConvertToLongThenCheckIfIs24BitValue(std::string& value)
static long long CheckIfStringIsHexAndConvertToLongThenCheckIfIs24BitValue(std::string_view value)
{
  if (!Globals::IsHexadecimalString(value)) return static_cast<long long>(-2);
  long long iValue = static_cast<long long>(std::stoll(std::string(value), NULL, 16));
  if ((iValue < 0x000000) || (iValue > 0xffffff)) return static_cast<long long>(-3);
  return iValue;
}

//static int minuendCheckAndAdd(std::string& value, Options& options)
static int minuendCheckAndAdd(std::string_view value, Options& options)
{
  long long check = CheckIfStringIsHexAndConvertToLongThenCheckIfIs24BitValue(value);
  if (check >= 0) options.minuend = check;
  return static_cast<int>((check < 0) ? (check * -1) : 0);
}

static int subtrahendsCheckAndAdd(std::string& value, Options& options)
{
  long long check = CheckIfStringIsHexAndConvertToLongThenCheckIfIs24BitValue(value);
  if (check >= 0) options.subtrahends.push_back(check);
  return static_cast<int>((check < 0) ? (check * -1) : 0);
}

// Unique argument parsing function for use in my argument parser class.
// Creating different parser functions for each program allows my argument class
// to stay small and generic.
static int ParseArguments(ArgumentParser& args, Options& options)
{
  if (args.optionExistsByPredicate(HelpRegex, true))
  {
    std::string message =
      "\n  Color Difference - Get the distance between two 24 bit colors from 0"
      "\n  to 441.672955930063722007616888732."
      "\n\n  colordiff [SWITCHES] [PARAMETERS <VALUE>] <VALUES>"
      "\n\n  @PARAMETERS"
      "\n    /m, /minuend  Initial hexadecimal color value to test. Ensures"
      "\n                  this value is used, otherwise the first value passed"
      "\n                  to the program is used."
      "\n\n  @SWITCHES"
      "\n    /h, /help     This help message."
      "\n    /v, /verbose  Detailed output."
      "\n    /n, /minimum  Return the minimum value only if multiple subtrahends"
      "\n                  are passed."
      "\n    /x, /maximum  Return the maximum value only if multiple subtrahends"
      "\n                  are passed."
      "\n                  If both of the minimum and maximum switches are passed"
      "\n                  to the program then the minimum option is used."
      "\n\n  @VALUES"
      "\n    Hexadecimal   Any number of 24 bit color values provided in"
      "\n                  hexadecimal format."
      "\n\n";
    std::cout << message;
    return -1;
  }
  if (args.optionExistsByPredicate(MinuRegex, false))
  {
    std::string value = args.getOptionByPredicate(MinuRegex, true);
    int check = minuendCheckAndAdd(value, options);
    if (check > 0) return check;
  }
  if (args.optionExistsByPredicate(VerbRegex, true))
    options.verbose = true;
  if (args.optionExistsByPredicate(MaxiRegex, true))
  {
    options.maximum = true;
    options.minimum = false;
  }
  if (args.optionExistsByPredicate(MiniRegex, true))
  {
    options.minimum = true;
    options.maximum = false;
  }
  std::vector<std::string> temp = args.getArgs();
  if (temp.size() == 0) return 1;
  if (options.minuend < 0)
  {
    int check = minuendCheckAndAdd(temp[0], options);
    if (check > 0) return check;
    temp.erase(temp.begin());
  }
  if (temp.size() == 0) return 1;
  for (std::string& item : temp)
  {
    int check = subtrahendsCheckAndAdd(item, options);
    if (check > 0) return check;
  }
  return EXIT_SUCCESS;
}

int main(int argc, const char* argv[])
{
  Options options = {false, false , false, -1};
  Errors errors =
  { {
    {1, "Not enough arguments passed to the program."},
    {2, "Value is not a valid hexadecimal value."},
    {3, "Hexadecimal value is not a valid 24 bit color (0x000000 - 0xFFFFFF, 0-16777215)."}
  } };
  if (argc < 2)
  {
    std::cerr << errors.messages[1] << '\n';
    return 1;
  }
  ArgumentParser args(argc, argv, 1);
  const int PARSED = ParseArguments(args, options);
  if (PARSED == -1) return EXIT_SUCCESS;
  if (PARSED > 0)
  {
    std::cerr << errors.messages[PARSED] << '\n';
    return PARSED;
  }
  std::vector<std::pair<std::string, double>> diffValues;
  const std::string minuendString = Globals::IntToHexString(static_cast<int>(options.minuend), 6, "0x");
  for (const long long& number : options.subtrahends)
  {
    const std::string subtrahendString = Globals::IntToHexString(static_cast<int>(number), 6, "0x");
    diffValues.push_back
    (
      std::make_pair(minuendString + " - " + subtrahendString,
        Globals::ColorDiff
        (
          static_cast<int>(options.minuend),
          static_cast<int>(number))
      )
    );
  }
  double minOrMax = 0;
  if (options.minimum)
  {
    class std::_Vector_iterator<class std::_Vector_val<struct std::_Simple_types<struct std::pair<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char> >, double> > > > min = std::min_element
    (
      std::begin(diffValues),
      std::end(diffValues),
      [](const auto& left, const auto& right) { return left.second < right.second; }
    );
    minOrMax = min->second;
  }
  if (options.maximum)
  {
    class std::_Vector_iterator<class std::_Vector_val<struct std::_Simple_types<struct std::pair<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char> >, double> > > > max = std::max_element
    (
      std::begin(diffValues),
      std::end(diffValues),
      [](const auto& left, const auto& right) { return left.second < right.second; }
    );
    minOrMax = max->second;
  }
  auto verb = [options](const std::string& key)
  {
      return (options.verbose ? key + ": " : "");
  };
  for (const auto& [key, value] : diffValues)
  {
    if (options.minimum || options.maximum)
    {
      if (value == minOrMax)
      {
        std::cout << verb(key) << std::setprecision(30) << value << '\n';
        break;
      }
    }
    else
    {
      std::cout << verb(key) << std::setprecision(30) << value << '\n';
    }
  }
  return EXIT_SUCCESS;
}
