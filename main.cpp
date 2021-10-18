#include "Strings.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <regex>

using namespace Strings;

int main (int argc, const char * argv [])
{
  std::vector <std::string>
    word_args,
    phrases_vector,
    characters_vector;
  auto
    is_upper = true,
    is_parts = false,
    is_phrases = false,
    is_characters = false;
  std::string phrases, characters;
  if (!isatty (fileno (stdin)))
  {
    std::string line;
    while (std::getline (std::cin, line))
    {
      if (!line.empty ())
      {
        word_args.push_back (line);
      }
    }
  }
  if (argc > 1)
  {
    auto skip = false;
    for (auto _i_ = 1; _i_ < argc; _i_++)
    {
      if (skip) { skip = false; continue; }
      auto error_arguments_passed = [argv, _i_] (int _error_)
      {
        std::cerr
          << "No arguments pass to the "
          << wrap_string (argv [_i_], wrap_data {"\"", "\""})
          << " parameter.\n";
        return _error_;
      };
      auto check_regex = [argv, _i_] (std::string _regex_)
      {
        return std::regex_match (argv [_i_], std::regex (_regex_));
      };
      if (check_regex ("^-([hH]|-[hH][eE][lL][pP])$"))
      {
        // TODO Finish HELP section
        // std::cout << "HELP" << std::endl;
        return 0;
      }
      if (check_regex ("^-([uU]|-[uU][pP][pP][eE][rR])$"))
      {
        is_upper = true;
        continue;
      }
      if (check_regex ("^-([lL]|-[lL][oO][wW][eE][rR])$"))
      {
        is_upper = false;
        continue;
      }
      if (check_regex ("^-([pP]|-[pP][hH][rR][aA][sS][eE][sS])$"))
      {
        if (! ((_i_ + 2) <= argc))
        {
          return error_arguments_passed (1);
        }
        delim_to_vector (phrases_vector, std::string (argv [_i_ + 1]), ',', true);
        if (phrases_vector.empty ())
        {
          return error_arguments_passed (2);
        }
        is_phrases = true;
        is_parts = is_phrases;
        skip = true;
        continue;
      }
      if (check_regex ("^-([cC]|-[cC][hH][aA][rR][aA][cC][tT][eE][rR][sS])$"))
      {
        if (! ((_i_ + 2) <= argc))
        {
          return error_arguments_passed (3);
        }
        delim_to_vector (characters_vector, std::string (argv [_i_ + 1]), ',', true);
        if (characters_vector.empty ())
        {
          return error_arguments_passed (4);
        }
        for (auto elem : characters_vector)
        {
          if (elem.length () > 1)
          {
            std::cerr << "Invalid character length." << std::endl;
            return 5;
          }
        }
        is_characters = true;
        is_parts = is_characters;
        skip = true;
        continue;
      }
      if (!std::string (argv [_i_]).empty ())
      {
        word_args.push_back (argv [_i_]);
      }
    }
  }
  if (!word_args.empty ())
  {
    for (auto word : word_args)
    {
      if (!is_parts)
      {
        std::for_each
        (
          word.begin (),
          word.end (),
          [is_upper, is_phrases](char & chr)
          {
              chr =
              (
                (
                  (is_upper) ?
                  (::toupper (chr)) :
                  (::tolower (chr))
                )
              );
          }
        );
      }
      else
      {
        auto process_vector = [&word, is_upper] (std::vector <std::string> _v_)
        {
          for (auto phrase : _v_)
          {
            for (auto chr : phrase)
            {
              replace_in_string
              (
                word, std::string (1, chr),
                std::string
                (
                  1,
                  (
                    (is_upper) ?
                    std::toupper (chr) :
                    std::tolower (chr)
                  )
                )
              );
            }
          }
        };
        if (is_phrases)
        {
          process_vector (phrases_vector);
        }
        if (is_characters)
        {
          process_vector (characters_vector);
        }
      }
      std::cout << word << std::endl;
    }
  }
  return 0;
}
