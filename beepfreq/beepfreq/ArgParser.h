#pragma once
#ifndef ARGPARSER_H
#define ARGPARSER_H
#include <regex>
#include <vector>
struct Parameters
{
  int error_value;
  int beep_frequency;
  int beep_duration;
  Parameters(int error_value, int beep_frequency, int beep_duration) :
    error_value(error_value),
    beep_frequency(beep_frequency),
    beep_duration(beep_duration) {}
  Parameters()
  {
    error_value = 0;
    beep_frequency = 10000;
    beep_duration = 1000;
  }
  bool operator==(const Parameters& other) const
  {
    return  error_value == other.error_value &&
      beep_frequency == other.beep_frequency &&
      beep_duration == other.beep_duration;
  }
};
struct Regex
{
  std::regex help;
  std::regex frequency;
  std::regex duration;
  std::regex integer;
  Regex(const std::regex& help, const std::regex& frequency, const std::regex& duration) :
    help(help),
    frequency(frequency),
    duration(duration),
    integer(integer) {}
  Regex()
  {
    help =
      std::regex("^/([\?]|[hH]|[hH][eE][lL][pP])$");
    frequency =
      std::regex("^/([fF]|[fF][rR][eE][qQ][uU][eE][nN][cC][yY])$");
    duration =
      std::regex("^/([dD]|[dD][uU][rR][aA][tT][iI][oO][nN])$");
    integer =
      std::regex("^[0-9]+$");
  }
  bool operator==(const Regex& other) const = default;
};
void ArgParser(int argc, const char* argv[], Parameters& params);
void NextArgTest(int index, const std::vector<std::string>& args, int iferror);
#endif // !ARGPARSER_H

