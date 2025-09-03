#include "stdafx.h"
#include "utils.h"
static void BuildArgumentParser(ArgumentParser& argParser) {
	const bool noParam = false;
	const bool hasParam = true;
	argParser.addSwitch("h", "This HELP message.");
	argParser.addSwitch("help", "This HELP message.");
	argParser.addSwitch("u", "Output in uppercase hexadecimal format.", noParam);
	argParser.addSwitch("uppercase", "Output in uppercase hexadecimal format.", noParam);
	argParser.addSwitch("f", "Prepend any series of characters to hexadecimal output.", hasParam);
	argParser.addSwitch("format", "Prepend '#' or '0x' to hexadecimal output.", hasParam);
	argParser.addSwitch("rgb", "Output in RGB format instead of hexadecimal.", noParam);
	argParser.setSwitchPair("h", "help");
	argParser.setSwitchPair("u", "uppercase");
	argParser.setSwitchPair("f", "format");
}
static void printRGB(const int& colorInt) {
	const auto rgb = InvertColorUtils::colorIntToRGBStrings(colorInt);
	const std::string rgbMessage =
		rgb.at("red") + " " +
		rgb.at("green") + " " +
		rgb.at("blue");
	std::cout << rgbMessage << std::endl;
}
static void printHex(const int& colorInt, bool& uppercase, const std::string& prefix) {
	const std::string hexedecimalMessage =
		prefix +
		InvertColorUtils::intColorToHexString(colorInt, uppercase);
	std::cout << hexedecimalMessage << std::endl;
}
static void printHex(ArgumentParser& argParser, int invertedColorValue, bool uppercase) {
	const std::string hexadecimalMessagePrefix =
		argParser.isSwitchSet("f") ? argParser.getSwitchValue("f") : "";
	const std::string hexedecimalMessage =
		hexadecimalMessagePrefix +
		InvertColorUtils::intColorToHexString(invertedColorValue, const_cast<bool&>(uppercase));
	std::cout << hexedecimalMessage << std::endl;
}
static int parseArguments(ArgumentParser& argParser) {
	try {
		const int argParseResult = argParser.parse();
		const int errorCode = argParser.getErrorCode();
		if (errorCode != 0) {
			throw std::runtime_error(
				"[" + std::to_string(errorCode) + "]: Error while parsing command line arguments.\n" +
				"Error: Missing parameter for switch '" +
				argParser.getArgvValue(argParseResult) + "'.");
		}
	}
	catch (const std::runtime_error& err) {
		std::cerr << err.what() << '\n';
	}
	return argParser.getErrorCode();
}
int main(int argc, char* argv[]) {
	ArgumentParser argParser(argc, argv);
	BuildArgumentParser(argParser);

	// TODO 
	const int parseResult = parseArguments(argParser);
	if (parseResult != 0) {
		return parseResult;
	}

	if (argParser.isSwitchSet("h") || argParser.isSwitchSet("help")) {
		argParser.printHelp(
			"InvertColor: Invert hexadecmal colors."
			"\nExpected argument value is hexadecimal. The default output"
			"\nvalue is in hexadecimal format, but can be displayed as RGB"
			"\nvalues with the '--rgb' switch.",
			true
		);
		return EXIT_SUCCESS;
	}

	if (argParser.getArgumentCount() == 0) {
		std::cerr << "[1]: No color value provided.\n";
		return 1;
	}

	const bool isRGBOutput = argParser.isSwitchSet("rgb");
	const bool uppercase = argParser.isSwitchSet("u");

	for (const auto& arg : argParser.getArguments()) {
		if (!InvertColorUtils::isHexValue(arg)) {
			std::cerr << "[2]: Invalid color value '" << arg << "'.\n";
			return 2;
		}
		std::string strCopy = arg;
		if (!strCopy.empty() && strCopy[0] == '#') strCopy.erase(0, 1);
		if (strCopy.size() >= 2 && strCopy.substr(0, 2) == "0x") strCopy.erase(0, 2);

		int colorValue = 0;
		try {
			colorValue = std::stoi(strCopy, nullptr, 16);
		} catch (...) {
			std::cerr << "[2]: Invalid color value '" << arg << "'.\n";
			return 2;
		}

		if (!InvertColorUtils::is24BitValue(colorValue)) {
			std::cerr << "[3]: Color value '" << arg << "' is out of range.\n";
			return 3;
		}

		const int invertedColorValue = (~colorValue) & 0xFFFFFF;

		if (isRGBOutput) {
			printRGB(invertedColorValue);
		} else {
			printHex(argParser, invertedColorValue, uppercase);
		}
	}

	return EXIT_SUCCESS;
}
