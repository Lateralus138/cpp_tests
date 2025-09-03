#include "stdafx.h"
#include "ArgumentParser.h"
#include <iostream>
ArgumentParser::ArgumentParser(int argc, char* argv[]) {
	std::string fullPath = std::string(argv[0]);
	size_t lastSlashPos = fullPath.find_last_of("/\\");
	if (lastSlashPos != std::string::npos) {
		this->executableName = fullPath.substr(lastSlashPos + 1);
	}
	else {
		this->executableName = fullPath;
	}
	this->argc = (argc - 1);
	for (int index = 1; index < argc; ++index) {
		this->argv.emplace_back(std::string(argv[index]));
	}
}
std::string ArgumentParser::getExecutableName() const {
	return this->executableName;
}
void ArgumentParser::setSwitchPair(std::string shortName, std::string longName) {
	for (auto& sw : this->switches) {
		if (sw.name == shortName) {
			sw.pair = longName;
		}
		if (sw.name == longName) {
			sw.pair = shortName;
		}
	}
}
void ArgumentParser::addSwitch(std::string name, std::string description) {
	this->switches.emplace_back(
		AddedSwitch(name, description, (name.length() > 1) ? "--" : "-")
	);
}
void ArgumentParser::addSwitch(std::string name, std::string description, bool hasParam) {
	this->switches.emplace_back(
		AddedSwitch(name, description, (name.length() > 1) ? "--" : "-", hasParam)
	);
}
void ArgumentParser::addSwitch(std::string name, std::string description, bool hasParam, bool throwIfNotSet) {
	this->switches.emplace_back(
		AddedSwitch(name, description, (name.length() > 1) ? "--" : "-", hasParam, throwIfNotSet)
	);
}
int ArgumentParser::parse() {
	// Optimized: Single pass over argv, O(N) time, no nested loops/ifs
	int possibleError = 256;
	this->arguments.clear();
	for (size_t index = 0; index < this->argv.size(); ++index) {
		const std::string& arg = this->argv[index];
		bool matchedSwitch = false;
		AddedSwitch* matched = nullptr;

		// Find switch in a single pass (linear search, but no nested loops)
		for (auto& sw : this->switches) {
			if (arg == sw.prefix + sw.name) {
				matchedSwitch = true;
				matched = &sw;
				break;
			}
			// Also match paired switch, if any
			if (!sw.pair.empty() && arg == ((sw.pair.length() > 1) ? "--" : "-") + sw.pair) {
				matchedSwitch = true;
				matched = &sw;
				break;
			}
		}

		if (matchedSwitch && matched) {
			matched->isSet = true;
			if (matched->hasParam) {
				possibleError--;
				bool paramMissing = ((index + 1) >= this->argv.size()) ||
					(this->argv[index + 1].rfind("-", 0) == 0) ||
					(this->argv[index + 1].rfind("--", 0) == 0) ||
					(this->argv[index + 1].empty());
				if (paramMissing) {
					if (matched->throwIfNotSet) {
						this->errorCode = possibleError;
						return static_cast<int>(index);
					} else {
						matched->value = "";
					}
				} else {
					matched->value = this->argv[index + 1];
					++index;
				}
			}
		} else {
			this->arguments.emplace_back(arg);
		}
	}
	return this->errorCode;
}
int ArgumentParser::getErrorCode() const {
	return this->errorCode;
}
bool ArgumentParser::isSwitchSet(std::string name) const {
	for (const auto& sw : this->switches) {
		if (sw.name == name) {
			return sw.isSet;
		}
	}
	return false;
}
void ArgumentParser::printHelp(std::string header, bool hasNonSwitchArguments) const {
	const std::string message =
		'\n' +
		header +
		"\n\nUsage:\n  " +
		this->executableName + ' ' + this->formatSwitchLine(hasNonSwitchArguments) +
		"\n\nSwitches:\n" +
		this->formatSwitchList();
	std::cout << message << '\n';
}
ArgumentParser::AddedSwitch::AddedSwitch(std::string name, std::string description, std::string prefix) {
	this->name = name;
	this->description = description;
	this->prefix = prefix;
}
ArgumentParser::AddedSwitch::AddedSwitch(std::string name, std::string description, std::string prefix, bool hasParam) {
	this->name = name;
	this->description = description;
	this->prefix = prefix;
	this->hasParam = hasParam;
}
ArgumentParser::AddedSwitch::AddedSwitch(std::string name, std::string description, std::string prefix, bool hasParam, bool throwIfNotSet) {
	this->name = name;
	this->description = description;
	this->prefix = prefix;
	this->hasParam = hasParam;
	this->throwIfNotSet = throwIfNotSet;
}
std::string ArgumentParser::formatSwitchList() const {
	std::string result = "";
	for (const auto& sw : this->switches) {
		if (!sw.pair.empty() && sw.name > sw.pair) {
			continue;
		}
		result += "  " + sw.prefix + sw.name;
		if (!sw.pair.empty()) {
			result += ", " + std::string((sw.pair.length() > 1) ? "--" : "-") + sw.pair;
		}
		if (sw.hasParam) {
			result += " <parameter>";
		}
		result += "\n    " + sw.description + "\n";
	}
	return result;
}
std::string ArgumentParser::formatSwitchLine(bool hasNonSwitchArguments) const {
	const size_t newLineSpace = (this->getExecutableName().length() + 3);
	const std::string newLinePadding(newLineSpace, ' ');
	std::string result = "";
	for (size_t index = 0; index < this->switches.size(); ++index) {
		const auto& sw = this->switches[index];
		if (!sw.pair.empty() && sw.name > sw.pair) {
			continue;
		}
		result += "[";
		result += sw.prefix + sw.name;
		if (!sw.pair.empty()) {
			result += " | " + std::string((sw.pair.length() > 1) ? "--" : "-") + sw.pair;
		}
		if (sw.hasParam) {
			result += " <parameter>";
		}
		result += "]";
		if (index < (this->switches.size() - 2)) {
			result += " |\n" + newLinePadding;
		}
	}
	if (hasNonSwitchArguments) {
		if (!result.empty()) {
			result += "\n" + newLinePadding + "<ARGUMENTS>";
		} else {
			result += "<ARGUMENTS>";
		}
		// TODO test aboe if works with no switches and FIXME if not
		//std::string((result.length() > 0) ? "\n" + newLinePadding : " ") +
		//"<ARGUMENTS>"; // Possibly add space if no switches
	}
	return result;
}
std::string ArgumentParser::getSwitchValue(std::string name) const {
	for (const auto& sw : this->switches) {
		if (sw.name == name) {
			return sw.value;
		}
	}
	return "";
}
std::string ArgumentParser::getArgvValue(size_t index) const {
	if (index < this->argv.size()) {
		return this->argv[index];
	}
	return "";
}
size_t ArgumentParser::getArgumentCount() const {
	return this->arguments.size();
}
std::vector<std::string> const& ArgumentParser::getArguments() const {
	return this->arguments;
}