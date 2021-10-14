#include <iostream>
#include <filesystem>
#include <regex>
#include <vector>
#include <fstream>

int main (void)
{
  auto
    is_patched = false,
    is_key_removed = false;
  auto global_error = 0;
  std::vector <std::filesystem::path> config_paths;
  std::filesystem::path base_config_path, eval_path, options_path;
  const char * HOME = std::getenv ("HOME");
  if (HOME == NULL)
  {
    std::cerr
      <<  "User\'s $HOME environment variable"
          "was empty and therefor can not search"
          "for the user\'s .config directory.\n";
    return 1;
  }
  base_config_path = std::string (HOME) + "/.config/JetBrains";
  if (!std::filesystem::exists (base_config_path))
  {
    std::cerr
      << "The JetBrains config directory was not found at: "
      << base_config_path << '\n';
    return 2;
  }
  if (!std::filesystem::is_directory (base_config_path))
  {
    std::cerr
      << base_config_path
      << " is not a directory.\n";
    return 3;
  }
  for (const auto & entry : std::filesystem::directory_iterator (base_config_path))
  {
    if (entry.is_directory ())
    {
      if (std::regex_match (entry.path ().filename (). string (), std::regex ("^CLion.*$")))
        config_paths.push_back (entry.path ());
    }
  }
  if ((int) config_paths.size () == 0)
  {
    std::cerr
      << "No config directories found in "
      << base_config_path
      << '\n';
    return 4;
  }
  for (auto path : config_paths)
  {
    for (const auto & entry : std::filesystem::directory_iterator (path))
    {
      if (std::regex_match (entry.path ().filename (). string (), std::regex ("^eval.*$")))
        eval_path = entry.path ();
      if (std::regex_match (entry.path ().filename (). string (), std::regex ("^options.*$")))
        options_path = entry.path ();
    }
  }
  if (!eval_path.empty ())
  {
    for (const auto & entry : std::filesystem::directory_iterator (eval_path))
    {
      if (entry.is_regular_file ())
      {
        auto key_file = entry.path ().filename (). string ();
        if (std::regex_match (key_file, std::regex ("^.*(.evaluation.key)$")))
        {
          std::cout
            << "Found key file: "
            << key_file
            << "\nAttempting to remove...\n";
          std::error_code ec;
          std::filesystem::remove (entry.path (), ec);
          if (ec.message () != "Success")
          {
            std::cerr
              << "System error: ["
              << ec.value ()
              << "]\nCould not delete "
              << entry
              << '\n';
            global_error = 5;
          }
          else
          {
            is_key_removed = true;
          }
          std::cout
            << "Key file: "
            << key_file
            << " successfully removed...\n";
        }
      }
    }
  }
  if (!options_path.empty ())
  {
    options_path /= "other.xml";
    if  (   std::filesystem::exists (options_path)
        &&  std::filesystem::is_regular_file (options_path))
    {
      std::cout
        << options_path
        << " found, attempting to patch...\n";
      std::string line;
      std::ifstream ifs (options_path);
      std::vector<std::string> lines;
      if (ifs.is_open ())
      {
        while (std::getline (ifs, line))
        {
          if (!std::regex_match (line, std::regex ("^.*evlsprt.*$")))
          {
            lines.push_back (line);
          }
          else
          {
            is_patched = true;
          }
        }
      }
      else
      {
        std::cerr
          << "Could not open file: "
          << options_path
          << " for reading.\n";
        return 6;
      }
      if ((int) lines.size () > 0)
      {
        std::ofstream ofs (options_path);
        if (!ofs.is_open ())
        {
          std::cerr
            << "Could not open file: "
            << options_path
            << " for writing.\n";
          return 7;
        }
        for (auto line : lines)
        {
          ofs << line << '\n';
        }
      }
    }
  }
  std::cout
    <<  ((is_patched)
      ? "JetBrains Clion was patched Successfully."
      : "JetBrains Clion did not need to be patched")
    << '\n'
    <<  ((is_key_removed)
      ? "Evaluation keys were removed Successfully."
      : "There were no evaluation keys to remove.")
    << '\n';
  return global_error;
}
