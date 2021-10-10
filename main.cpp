#include "functions.h"
#include <iostream>
#include <filesystem>
#include <regex>
#include <fstream>

struct error
{
  int error = 0;
  std::string message = "";
};

int main (int argc, char * argv [])
{
  auto
    is_verbose = true,
    is_monochrome = false,
    is_help = false;
  std::string main_name = "main";
  std::vector <std::string>
    extra_cpp_names_vec,
    extra_class_names_vec,
    project_branches_string_vec
    {
      "/src",
      "/src/include",
      "/src/lib"
    },
    project_files_string_vec
    {
      "/makefile",
      "/src/[PLACEHOLDER].cpp"
    };
  error _error_;
  auto project_path = std::filesystem::current_path ();
  std::vector <std::filesystem::path>
    project_branches_path_vec,
    project_files_path_vec;
  if (argc > 1)
  {
    std::vector <std::string> args (argv + 1, argv + argc);
    argc--;
    auto skip = false;
    auto is_match = [args] (std::regex _regex_, int _index_)
    {
      return std::regex_match (args [_index_], _regex_);
    };
    auto has_next_arg = [argc] (int _index_)
    {
      return (!((_index_ + 1) > (argc - 1)));
    };
    for (auto i = 0; i < argc; i++)
    {
      // bool has_next_arg = (!((i + 1) > (argc - 1)));
      // auto has_next_arg = [argc, i] () { return (!((i + 1) > (argc - 1))); };
      // auto is_match = [args, i] (std::regex _regex_)
      // {
      //   return std::regex_match (args [i], _regex_);
      // };
      if (skip)
      {
        skip = false;
        continue;
      }
      if (is_match (std::regex ("^-([hH]|-[hH][eE][lL][pP])$"), i))
      {
        is_help = true;
        continue;
      }
      if (is_match (std::regex ("^-([qQ]|-[qQ][uU][iI][eE][tT])$"), i))
      {
        is_verbose = false;
        continue;
      }
      if (is_match (std::regex("^-([mM]|-[mM][oO][nN][oO][cC][hH][rR][oO][mM][eE])$"), i))
      {
        is_monochrome = true;
        continue;
      }
      if (is_match (std::regex("^-([pP]|-[pP][aA][tT][hH])$"), i))
      {
        skip = true;
        if (!has_next_arg (i))
        {
          _error_.error = 1;
          _error_.message = "Argument was not provided for the \'";
          _error_.message.append (args [i]);
          _error_.message.append ("\' parameter.");
          continue;
        }
        auto working_string = args [i + 1];
        if (working_string.length () > 1)
        {
          if (working_string.back () == '/')
          {
            working_string.pop_back ();
          }
        }
        project_path = std::filesystem::path (working_string);
        continue;
      }
      if (is_match (std::regex("^-([nN]|-[nN][aA][mM][eE])$"), i))
      {
        skip = true;
        if (!has_next_arg (i))
        {
          _error_.error = 2;
          _error_.message = "Argument was not provided for the \'";
          _error_.message.append (args [i]);
          _error_.message.append ("\' parameter.");
          continue;
        }
        main_name = args [i + 1];
        if (main_name.empty ())
        {
          _error_.error = 3;
          _error_.message = "The provided main file name was an empty string.";
        }
        continue;
      }
      if (is_match (std::regex("^-([xX]|-[eE][xX][tT][rR][aA]-[sS][rR][cC])$"), i))
      {
        skip = true;
        if (!has_next_arg (i))
        {
          _error_.error = 4;
          _error_.message = "Argument was not provided for the \'";
          _error_.message.append (args [i]);
          _error_.message.append ("\' parameter.");
          continue;
        }
        auto working_string_string = args [i + 1];
        if (working_string_string.empty ())
        {
          _error_.error = 5;
          _error_.message = "The provided extra source file list was empty.";
        }
        string_to_vector (working_string_string, extra_cpp_names_vec, ",");
        for (auto & str : extra_cpp_names_vec)
        {
          if (str.empty () || std::regex_match (str, std::regex ("^[\\s]+$")))
          {
            _error_.error = 6;
            _error_.message = "Extra source file name is empty.";
          }
        }
        continue;
      }
      if (is_match (std::regex("^-([cC]|-[cC][lL][aA][sS][sS]-[fF][iI][lL][eE][sS])$"), i))
      {
        skip = true;
        if (!has_next_arg (i))
        {
          _error_.error = 7;
          _error_.message = "Argument was not provided for the \'";
          _error_.message.append (args [i]);
          _error_.message.append ("\' parameter.");
          continue;
        }
        auto working_string_string = args [i + 1];
        if (working_string_string.empty ())
        {
          _error_.error = 8;
          _error_.message = "The provided extra class file list was empty.";
        }
        string_to_vector (working_string_string, extra_class_names_vec, ",");
        for (auto & str : extra_class_names_vec)
        {
          if (str.empty () || std::regex_match (str, std::regex ("^[\\s]+$")))
          {
            _error_.error = 9;
            _error_.message = "Extra class file name is empty.";
          }
        }
        continue;
      }
    }
  }
  (void) argv; (void) argc;
  auto wrap_with_color = [is_monochrome]
  (
    std::string _string_,
    std::string _color_string_
  )
  {
    return
    (
      ((!is_monochrome)?"\x1b[":"") +
      ((!is_monochrome)?_color_string_:"") +
      ((!is_monochrome)?"m":"") +
      _string_ +
      ((!is_monochrome)?"\x1b[0m":"")
    );
  };
  if (is_help)
  {
    const std::string EMPTY_LINE (50, ' ');
    // auto wrap_with_color = [is_monochrome]
    // (
    //   std::string _string_,
    //   std::string _color_string_
    // )
    // {
    //   return
    //   (
    //     ((!is_monochrome)?"\x1b[":"") +
    //     ((!is_monochrome)?_color_string_:"") +
    //     ((!is_monochrome)?"m":"") +
    //     _string_ +
    //     ((!is_monochrome)?"\x1b[0m":"")
    //   );
    // };
    std::cout
      << EMPTY_LINE
      << "\n  \'mkcppproj\' - Create a basic cpp project tree   "
      << EMPTY_LINE
      << "\n  "
      << wrap_with_color ("USAGE", "32")
      << ":                                          "
      << "\n    mkcppproj ["
      << wrap_with_color ("OPTIONS", "34")
      << " ["
      << wrap_with_color ("ARGUMENTS", "35")
      << "]...]...         \n"
      << EMPTY_LINE
      << "\n  "
      << wrap_with_color ("OPTIONS", "34")
      << ":                                        "
      << "\n    -h, --help        This help screen            "
      << "\n    -q, --quiet       All errors are non-verbose  "
      << "\n    -m, --monochrome  No color in output          "
      << "\n    -p, --path        "
      << wrap_with_color ("PATH", "35")
      << " to project             "
      << "\n    -n, --name        "
      << wrap_with_color ("NAME", "35")
      << " of the main source     "
      << "\n                      file without the extension  "
      << "\n    -x, --extra-src   Comma [,] delimitied "
      << wrap_with_color ("LIST", "35")
      << "\n   "
      << "\n                      of extra source files       "
      << "\n                      without the extension       "
      << "\n    -c, --class-files Comma [,] delimitied "
      << wrap_with_color ("LIST", "35")
      << "   "
      << "\n                      of extra class/header files "
      << "\n                      without the extensions      "
      << EMPTY_LINE
      << std::endl;
    if (_error_.error > 0 && is_verbose)
    {
        std::cerr
          << ((!is_monochrome)?"\x1b[91m":"")
          << _error_.message
          << ((!is_monochrome)?"\x1b[0m":"")
          << std::endl;
    }
    return _error_.error;
  }
  if (_error_.error == 0)
  {
    std::error_code error_fs;
    auto working_main = project_files_string_vec [1];
    working_main.replace (working_main.find ("[PLACEHOLDER]"), 13, main_name);
    project_files_string_vec [1] = working_main;
    for (auto branch : project_branches_string_vec)
    {
      project_branches_path_vec.push_back
      (
        project_path.c_str () + branch
      );
    }
    for (auto path : project_branches_path_vec)
    {
      if (std::filesystem::exists (path, error_fs))
      {
        if (!std::filesystem::is_directory (path, error_fs))
        {
          _error_.error = 12;
          _error_.message = path;
          _error_.message.append (" already exists, but is not a directory.");
          break;
        }
        else
        {
          if (error_fs.message () != "Success")
          {
            _error_.error = 11;
            _error_.message = error_fs.message ();
            break;
          }
        }
        continue;
      }
      else
      {
        if (error_fs.message () != "Success")
        {
          _error_.error = 10;
          _error_.message = error_fs.message ();
          break;
        }
      }
    }
  }
  if (_error_.error == 0)
  {
    std::string pp  =  project_path.c_str ();
    if (extra_cpp_names_vec.size () > 0)
    {
      for (auto elem : extra_cpp_names_vec)
      {
        std::string working_string  =  "/src/";
        working_string.append (elem);
        working_string.append (".cpp");
        project_files_string_vec.push_back (working_string);
      }
    }
    if (extra_class_names_vec .size () > 0)
    {
      for (auto elem : extra_class_names_vec)
      {
        std::string
          working_string1  =  "/src/include/",
          working_string2  =  working_string1;
        working_string1.append (elem);
        working_string2.append (elem);
        working_string1.append (".cpp");
        working_string2.append (".h");
        project_files_string_vec.push_back (working_string1);
        project_files_string_vec.push_back (working_string2);
      }
    }
    for (auto elem : project_files_string_vec)
    {
      project_files_path_vec.push_back (pp + elem);
    }
  }
  if (_error_.error == 0)
  {
    std::error_code error_fs;
    for (auto elem : project_files_path_vec)
    {
      if (std::filesystem::exists (elem, error_fs))
      {
        if (!std::filesystem::is_regular_file (elem, error_fs))
        {
          _error_.error = 15;
          _error_.message = elem;
          _error_.message.append (" already exists, but is not a regular file.");
          break;
        }
        else
        {
          if (error_fs.message () != "Success")
          {
            _error_.error = 14;
            _error_.message = error_fs.message ();
            break;
          }
        }
        continue;
      }
      else
      {
        if (error_fs.message () != "Success")
        {
          _error_.error = 13;
          _error_.message = error_fs.message ();
          break;
        }
      }
    }
  }
  if (_error_.error == 0)
  {
    std::error_code error_fs;
    for (auto path : project_branches_path_vec)
    {
      if (!std::filesystem::exists (path, error_fs))
      {
        std::filesystem::create_directories (path, error_fs);
        if (error_fs.value () > 0)
        {
          _error_.error = 17;
          _error_.message = error_fs.message ();
          break;
        }
      }
      else
      {
        if (error_fs.message () != "Success")
        {
          _error_.error = 16;
          _error_.message = error_fs.message ();
          break;
        }
      }
    }
  }
  if (_error_.error == 0)
  {
    std::error_code error_fs;
    for (auto file : project_files_path_vec)
    {
      if (!std::filesystem::exists (file, error_fs))
      {
        std::ofstream f_s (file);
        if (!f_s.is_open ())
        {
          _error_.error = 19;
          _error_.message = file;
          _error_.message.append (" was not created.");
          break;
        }
      }
      else
      {
        if (error_fs.message () != "Success")
        {
          _error_.error = 18;
          _error_.message = error_fs.message ();
          break;
        }
      }
    }
  }
  if (_error_.error > 0 && is_verbose)
  {
      std::cerr
        << ((!is_monochrome)?"\x1b[91m":"")
        << _error_.message
        << ((!is_monochrome)?"\x1b[0m":"")
        << std::endl;
  }
  return _error_.error;
}
