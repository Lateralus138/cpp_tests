#include "stdafx.h"
#include "utils.h"
namespace InvertColorUtils {
	bool is24BitValue(const int& value) {
		return (value & ~0xFFFFFF) == 0;
	}
	bool isHexValue(const std::string& str) {
		std::string_view s = str;
		if (!s.empty() && s.front() == '#') s.remove_prefix(1);
		if (s.size() >= 2 && s.substr(0, 2) == "0x") s.remove_prefix(2);
		if (s.empty() || s.size() > 6) return false;
		for (char ch : s) {
			if (!std::isxdigit(static_cast<unsigned char>(ch))) return false;
		}
		return true;
	}
	std::map<std::string, std::string> colorIntToRGBStrings(const int& colorInt) {
		std::map<std::string, std::string> rgb = {
			{"red", std::to_string((colorInt >> 16) & 0xFF)},
			{"green", std::to_string((colorInt >> 8) & 0xFF)},
			{ "blue", std::to_string((colorInt & 0xFF))}
		};
		return rgb;
	}
	std::string intColorToHexString(const int& value, bool& uppercase) {
		std::array<char, 7> buffer{};
		auto [ptr, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), value, 16);
		if (ec != std::errc()) {
			return "";
		}
		std::string hexStr(buffer.data(), ptr);
		if (hexStr.length() < 6) {
			hexStr.insert(0, 6 - hexStr.length(), '0');
		}
		if (uppercase) {
			std::transform(hexStr.begin(), hexStr.end(), hexStr.begin(), [](unsigned char c) { return std::toupper(c); });
		}
		return hexStr;
	}
}