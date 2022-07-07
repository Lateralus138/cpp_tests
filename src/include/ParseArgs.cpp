#include "ParseArgs.h"
#include <iostream>
#include <regex>
#include <vector>

//namespace Args
//{
//  struct args
//  {
//    bool formatIsNull = false;
//  };
//};
//  struct args
//  {
//    bool formatIsNull = false;
//  };
args args_;
void ParseArgs::parse(int min, int max)
{
//  using namespace Args;
//  Args::args.formatIsNull = true;
  const std::regex R_HELP   ("^-([hH]|-[hH][eE][lL][pP])$");
  const std::regex R_NULL   ("^-(0|-[nN][uU][lL][lL])$");
  const std::regex R_DELIM  ("^-([dD]|-[dD][eE][lL][iI][mM])$");
  const std::vector<std::string> BOX =
  {
    u8"\u250C", u8"\u2500", u8"\u2510", u8"\u2502",
    u8"\u2514", u8"\u2518", u8"\u251C", u8"\u2524"
  };
  std::string line;
  for (int i = 0; i < 48; i++) line += BOX[1];
  const std::string HELPMESSAGE =
    BOX[0] + line + BOX[2] + "\n" +
    BOX[3] + " lspids - 'List PIDS'                           " + BOX[3] + "\n" +
    BOX[6] + line + BOX[7] + "\n" +
    BOX[3] + " Usage: lspids [OPTIONS]                        " + BOX[3] + "\n" +
    BOX[3] + "   List integer PIDS from the '/proc' directory " + BOX[3] + "\n" +
    BOX[3] + "   in Linux.                                    " + BOX[3] + "\n" +
    BOX[6] + line + BOX[7] + "\n" +
    BOX[3] + " OPTIONS:                                       " + BOX[3] + "\n" +
    BOX[3] + "   -h,--help     This HELP message.             " + BOX[3] + "\n" +
    BOX[3] + "   -0,--null     Output is null terminated.     " + BOX[3] + "\n" +
    BOX[3] + "   -d,--delim    Set a string delimiter to      " + BOX[3] + "\n" +
    BOX[3] + "                 separate output. Defaults to a " + BOX[3] + "\n" +
    BOX[3] + "                 space, but can be any string.  " + BOX[3] + "\n" +
    BOX[6] + line + BOX[7] + "\n" +
    BOX[3] + " Exit Codes: Error codes and their meanings.    " + BOX[3] + "\n" +
    BOX[3] + "   0   No errors.                               " + BOX[3] + "\n" +
    BOX[3] + "   1   Too many arguments passed to the         " + BOX[3] + "\n" +
    BOX[3] + "       program.                                 " + BOX[3] + "\n" +
    BOX[3] + "   2   '/proc' doesn't exist.                   " + BOX[3] + "\n" +
    BOX[3] + "   3   '/proc' is not a directory.              " + BOX[3] + "\n" +
    BOX[3] + "   4   Could not iterate '/proc' for an unknown " + BOX[3] + "\n" +
    BOX[3] + "       reason.                                  " + BOX[3] + "\n" +
    BOX[4] + line + BOX[5] + "\n";
  for (int i = min; i < max; i++)
  {
    std::string str = argV[i];
    if (std::regex_match(str, R_HELP))
    {
      std::cout << HELPMESSAGE;
      std::exit(0);
    }
    if (std::regex_match(str, R_NULL))
    {
      args.formatIsNull = true;
      continue;
    }
  }
}
