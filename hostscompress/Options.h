#pragma once

#include <string>
#include <vector>
#include <regex>

struct Options
{
  std::regex RGX_UINT = std::regex("[0-9]+");
  int urlsPerLine = 9;
  std::string inputFile = "";
  std::string outputFile = "";
  bool isOutputColor = true;
  bool isDiscard = false;
  bool isOutputFile = false;
  int urlStartingLineIndex = 0;
  int url000StartingLineIndex = 0;
  int url127StartingLineIndex = 0;
  bool hasUrl000StartingLineIndex = false;
  bool hasUrl127StartingLineIndex = false;
  bool hasFooterAndHeader = false;
  bool isQuiet = false;
  bool isHelp = false;
  std::vector<std::string> urls000;
  std::vector<std::string> urls127;
  std::vector<std::string> headerContent;
  std::vector<std::string> footerContent;
};
