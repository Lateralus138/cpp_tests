#include "cppproj.h"
int main(int argc, const char *argv[])
{
  set_signal_handlers(sighandler);
  Parameters params;
  Switches switches;
  bool ARGSPARSEDNOERROR = true;
  if (argc > 1)
  {
    ARGSPARSEDNOERROR = ArgParser(argc, argv, params, switches);
  }
  if (switches.is_help)
  {
    return EXIT_SUCCESS;
  }
  if (!ARGSPARSEDNOERROR)
  {
    return params.error_value;
  }
  std::string PARENTPATH = params.path_name;
  const std::map<std::string, std::string> DIRECTORIESMAP =
  {{"source", "src"}, {"include", "src/include"}, {"library", "src/lib"}};
  for (auto const &[key, value] : DIRECTORIESMAP)
  {
    directories.setNewPath(key, PARENTPATH);
    directories.append(key, value);
  }
  std::map<std::string, std::filesystem::path> dir_paths = directories.getPaths();
  const std::string MAINFILE = [&dir_paths, params]()
  {
    std::string mainfile = dir_paths["source"].native().c_str();
    mainfile.push_back('/');
    mainfile.append(params.main_name);
    mainfile.append(".cpp");
    return mainfile;
  }
  ();
  files.setNewPath("main", MAINFILE);
  auto class_file = [&dir_paths](std::string class_name, std::string extension)
  {
    std::string classfile = dir_paths["include"].native().c_str();
    classfile.push_back('/');
    classfile.append(class_name);
    classfile.push_back('.');
    classfile.append(extension);
    return classfile;
  };
  params.class_names.push_back("pch");
  for (const std::string class_name : params.class_names)
  {
    std::string class_name_h    = class_name;
    std::string class_name_cpp  = class_name_h;
    class_name_h.append("_h");
    class_name_cpp.append("_cpp");
    files.setNewPath(class_name_h, class_file(class_name, "h"));
    files.setNewPath(class_name_cpp, class_file(class_name, "cpp"));
  }
  files.setNewPath("make", PARENTPATH);
  files.append("make", "Makefile");
  if (switches.prebuild_script)
  {
    files.setNewPath("prebuild", PARENTPATH);
    files.append("prebuild", "prebuild");
  }
  std::map<std::string, std::filesystem::path> file_paths = files.getPaths();
  globals.pch_content_create(params);
  globals.makefile_content_create(params);
  for (std::pair const [key, value] : dir_paths)
  {
    if (key == "source") continue;
    std::string temp_message = "Checking if ";
    const std::string path = value.native().c_str();
    temp_message.append(path);
    temp_message.append(" exists...\n");
    std::cout << temp_message;
    temp_message.clear();
    const bool dir_exists = PathExists(value, params, 7);
    if (params.error_value > 0)
    {
      return params.error_value;
    }
    temp_message.append(path);
    StringAppendIf(dir_exists, temp_message,
                   " already exists and does not need to be created...\n",
                   " does not exist; attempting to create directory...\n");
    std::cout << temp_message;
    temp_message.clear();
    if (dir_exists) continue;
    const bool dir_created = CreateDirectory(value, params, 8);
    if (params.error_value > 0)
    {
      return params.error_value;
    }
    temp_message.append(path);
    temp_message.append(" was created successfully...\n");
    std::cout << temp_message;
    temp_message.clear();
  }
  for (std::pair const [key, value] : file_paths)
  {
    std::string temp_message = "Checking if ";
    const std::string path = value.native().c_str();
    temp_message.append(path);
    temp_message.append(" exists...\n");
    std::cout << temp_message;
    temp_message.clear();
    const bool file_exists = PathExists(value, params, 9);
    if (params.error_value > 0)
    {
      return params.error_value;
    }
    temp_message.append(path);
    StringAppendIf(file_exists, temp_message,
                   " already exists and does not need to be created...\n",
                   " does not exist; attempting to create file...\n");
    std::cout << temp_message;
    temp_message.clear();
    if (file_exists) continue;
    std::string content;
    if (key == "main")
    {
      content = globals.main_content;
    }
    else if (key == "make")
    {
      content = globals.makefile_content;
    }
    else if (key == "pch_h")
    {
      content = globals.pch_content;
    }
    else if ((switches.prebuild_script) && (key == "prebuild"))
    {
      content = globals.prebuild_content;
    }
    else
    {
      bool delim_found = false;
      size_t delim_pos = key.find('_');
      delim_found = (delim_pos != std::string::npos);
      if (!delim_found)
      {
        continue;
      }
      std::string ext_ = key.substr(delim_pos);
      if (ext_ == "_h")
      {
        content = globals.class_header_content_create(key);
      }
      else
      {
        content = globals.class_source_content_create(value.stem().native().c_str());
      }
    }
    CreateFile(value, content, params, 10);
    if (params.error_value > 0)
    {
      return params.error_value;
    }
  }
  return params.error_value;
}
