#pragma once
#include <vector>
#include <string>
class ArgumentParser {
public:
	ArgumentParser(int argc, char* argv[]);
	~ArgumentParser() = default;
	std::string getExecutableName() const;
	void setSwitchPair(std::string shortName, std::string longName);
	void addSwitch(std::string name, std::string description);
	void addSwitch(std::string name, std::string description, bool hasParam);
	void addSwitch(std::string name, std::string description, bool hasParam, bool throwIfNotSet);
	int parse();
	int getErrorCode() const;
	bool isSwitchSet(std::string name) const;
	void printHelp(std::string header, bool hasNonSwitchArguments) const;
	std::string getSwitchValue(std::string name) const;
	std::string getArgvValue(size_t index) const;
	size_t getArgumentCount() const;
	const std::vector<std::string>& getArguments() const;

private:
	std::string executableName;
	int argc;
	int errorCode = 0;
	struct AddedSwitch {
		std::string name;
		std::string description;
		std::string prefix;
		std::string value;
		std::string pair;
		bool hasParam = false;
		bool isSet = false;
		bool throwIfNotSet = false;
		AddedSwitch(std::string name, std::string description, std::string prefix);
		AddedSwitch(std::string name, std::string description, std::string prefix, bool hasParam);
		AddedSwitch(std::string name, std::string description, std::string prefix, bool hasParam, bool throwIfNotSet);
	};
	std::vector<std::string> argv;
	std::vector<std::string> arguments;
	std::vector<AddedSwitch> switches;
	std::string formatSwitchList() const;
	std::string formatSwitchLine(bool hasNonSwitchArguments) const;
};

