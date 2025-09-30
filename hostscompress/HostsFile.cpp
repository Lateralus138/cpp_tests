#include "pch.h"
#include "HostsFile.h"
#include "Functions.h" // For GetHostsOutput, CompressUrls, etc.
#include <fstream>
#include <iostream>
#include <sstream>

const std::regex RGX_ISURL_000(R"(^0.0.0.0[\s]+(?!(0.0.0.0$|127.0.0.1$|local$|localhost$|localhost.localdomain$)).*)");
const std::regex RGX_URLS000_REPLACE(R"(^(0.0.0.0)[\s]+)");
const std::regex RGX_ISURL_127(R"(^127.0.0.1[\s]+(?!(0.0.0.0$|127.0.0.1$|local$|localhost$|localhost.localdomain$)).*)");
const std::regex RGX_URLS127_REPLACE(R"(^(127.0.0.1)[\s]+)");



HostsFile::HostsFile(Options& options, ProgramError& perror)
    : _options(options), _perror(perror)
{
}

void HostsFile::read()
{
    // Logic from ReadHostsToVector
    std::ifstream inputFileStream(_options.inputFile);
    if (inputFileStream.is_open())
    {
        for (std::string line; std::getline(inputFileStream, line);)
        {
            _lines.push_back(line);
        }
        inputFileStream.close();
    }
    else
    {
        std::string message = "Could not open file: ";
        message.append(_options.inputFile);
        message.append(" for reading");
        _perror.addError(15, message);
        _perror.setError(15);
    }
}

void HostsFile::parse()
{
    PrintMessage(
        std::vector<std::string>
        {
            "Reading \"",
            (_options.isOutputColor ? "\x1b[93m" : ""),
            std::filesystem::absolute(std::filesystem::path(_options.inputFile)).string(),
            (_options.isOutputColor ? "\x1b[m" : ""),
            "\" content...\n"
        },
        _options
    );

    bool hasUrls = false;
    for (const auto& line : _lines)
    {
        if (std::regex_match(line, RGX_ISURL_000))
        {
            hasUrls = true;
            _urls000.push_back(std::regex_replace(line, RGX_URLS000_REPLACE, ""));
        }
        else if (std::regex_match(line, RGX_ISURL_127))
        {
            hasUrls = true;
            _urls127.push_back(std::regex_replace(line, RGX_URLS127_REPLACE, ""));
        }
        else
        {
            if (hasUrls)
            {
                _footer.push_back(line);
            }
            else
            {
                _header.push_back(line);
            }
        }
    }
}


void HostsFile::_compressUrls(const std::string& ip, const std::vector<std::string>& urls)
{
    if (urls.empty())
    {
        PrintMessage(
            std::vector<std::string>
            {
                "No urls found for [",
                (_options.isOutputColor ? "\x1b[91m" : ""),
                ip,
                (_options.isOutputColor ? "\x1b[m" : ""),
                "]...\n"
            },
            _options
        );
        return;
    }

    PrintMessage(
        std::vector<std::string>
        {
            "Found urls for [",
            (_options.isOutputColor ? "\x1b[92m" : ""),
            ip,
            (_options.isOutputColor ? "\x1b[m" : ""),
            "]; Compressing...\n"
        },
        _options
    );

    for (int index = 0; index <= (int)(urls.size() - _options.urlsPerLine); index += _options.urlsPerLine)
    {
        std::stringstream ss;
        ss << ip << ' ';
        for (int index2 = 0; index2 < _options.urlsPerLine; index2++)
        {
            const int nIndex = (index + index2);
            ss << urls[nIndex];
            if (index2 < (_options.urlsPerLine - 1)) ss << ' ';
        }
        _compressedLines.push_back(ss.str());
    }
    int leftOver = (int)(urls.size() - (_compressedLines.size() * _options.urlsPerLine));
    if (leftOver > 0)
    {
        std::stringstream ss;
        ss << ip << " ";
        for (int index = (int)(_compressedLines.size() * _options.urlsPerLine); index < (int)urls.size(); index++)
        {
            ss << urls[index];
            if (index < ((int)urls.size() - 1))
            {
                ss << ' ';
            }
        }
        _compressedLines.push_back(ss.str());
    }
    if (!_options.isQuiet)
    {
        std::cout
            << "Compressed ["
            << (_options.isOutputColor ? "\x1b[93m" : "")
            << std::to_string((int)urls.size())
            << (_options.isOutputColor ? "\x1b[m" : "")
            << "] urls to ["
            << (_options.isOutputColor ? "\x1b[92m" : "")
            << std::to_string((int)urls.size() / _options.urlsPerLine)
            << (_options.isOutputColor ? "\x1b[m" : "")
            << "] lines...\n";
    }
}

void HostsFile::compress()
{
    PrintMessage(
        std::vector<std::string>
        {
            "Compiling urls for [",
            (_options.isOutputColor ? "\x1b[93m" : ""),
            "0.0.0.0",
            (_options.isOutputColor ? "\x1b[m" : ""),
            "]...\n"
        },
        _options
    );
    _compressUrls("0.0.0.0", _urls000);

    PrintMessage(
        std::vector<std::string>
        {
            "Compiling urls for [",
            (_options.isOutputColor ? "\x1b[93m" : ""),
            "127.0.0.1",
            (_options.isOutputColor ? "\x1b[m" : ""),
            "]...\n"
        },
        _options
    );
    _compressUrls("127.0.0.1", _urls127);
}

void HostsFile::write()
{
    std::string outputData;

    if ((!_options.isDiscard) && (!_header.empty()))
    {
        for (const auto& line : _header)
        {
            if (!outputData.empty()) outputData.push_back('\n');
            outputData.append(line);
        }
    }

    for (const auto& line : _compressedLines)
    {
        if (!outputData.empty()) outputData.push_back('\n');
        outputData.append(line);
    }

    if ((!_options.isDiscard) && (!_footer.empty()))
    {
        for (const auto& line : _footer)
        {
            if (!outputData.empty()) outputData.push_back('\n');
            outputData.append(line);
        }
    }

    if (_options.isOutputFile)
    {
        std::ofstream ofs(_options.outputFile, std::fstream::trunc);
        if (ofs.is_open())
        {
            ofs << outputData;
            ofs.close();
            PrintMessage(
                std::vector<std::string>
                {
                    "Compressed data has been successfully written to:\n\"",
                    (_options.isOutputColor ? "\x1b[92m" : ""),
                    std::filesystem::absolute(std::filesystem::path(_options.outputFile)).string(),
                    (_options.isOutputColor ? "\x1b[m" : ""),
                    "\"...\n"
                },
                _options
            );
        }
        else
        {
            std::string message = "Could not open file: ";
            message.append(_options.outputFile);
            message.append(" for writing");
            _perror.addError(16, message);
            _perror.setError(16);
        }
    }
    else
    {
        std::cout << outputData;
    }
}

void HostsFile::process()
{
    read();
    if (_perror.getError().value > 0) return;

    parse();
    compress();
    write();
}
