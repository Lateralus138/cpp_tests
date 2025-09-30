#pragma once

#include "Options.h"
#include "ProgramError.h"
#include <filesystem>
#include <string>
#include <vector>

class HostsFile
{
    friend class HostsFileTest; // Declare HostsFileTest as a friend class
public:
    HostsFile(Options& options, ProgramError& perror);

    void process();

private:
    void read();
    void write();
    void parse();
    void compress();

    Options& _options;
    ProgramError& _perror;
    std::vector<std::string> _lines;
    std::vector<std::string> _header;
    std::vector<std::string> _footer;
    std::vector<std::string> _urls000;
    std::vector<std::string> _urls127;
    std::vector<std::string> _compressedLines;

    void _compressUrls(const std::string& ip, const std::vector<std::string>& urls);
};