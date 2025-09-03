#pragma once
namespace InvertColorUtils {
	bool is24BitValue(const int& value);
	bool isHexValue(const std::string& str);
	std::map<std::string, std::string> colorIntToRGBStrings(const int& colorInt);
	std::string intColorToHexString(const int& value, bool& uppercase);
}