#pragma once
#ifndef ARGPARSER_H
#define ARGPARSER_H
#include <regex>
struct Regex
{
  std::regex help;
  std::regex resolution;
  std::regex width;
  std::regex height;
  std::regex dpi;
  std::regex format;
  Regex(const std::regex& help, const std::regex& resolution, const std::regex& width, const std::regex& height, const std::regex& dpi, const std::regex& format)
    : help(help), resolution(resolution), width(width), height(height), dpi(dpi), format(format)
  {
  }
  Regex()
  {
    help =
      std::regex("^/([\?]|[H]|[hH][eE][lL][pP])$");
    resolution =
      std::regex("^/([rR]|[rR][eE][sS][oO][lL][uU][tT][iI][oO][nN])$");
    width =
      std::regex("^/([wW]|[wW][iI][dD][tT][hH])$");
    height =
      std::regex("^/([h]|[hH][eE][iI][gG][hH][tT])$");
    dpi =
      std::regex("^/([dD]|[dD][pP][iI])$");
    format =
      std::regex("^/([fF]|[fF][oO][rR][mM][aA][tT])$");
  };
};
struct Switches
{
  bool formatted;
  bool width;
  bool height;
  bool dpi;
  Switches(bool formatted, bool width, bool height, bool dpi)
    : formatted(formatted), width(width), height(height), dpi(dpi)
  {
  }
  Switches()
  {
    formatted = false;
    width = true;
    height = true;
    dpi = true;
  };
};
void ArgParser(int argc, const char* argv[], Switches& switches);
#endif // !ARGPARSER_H
