// ------------------------------------------------
// 'upgg'
// Copyright © 2022
// Ian Pride @ New Pride Software/Services
// Sun 22 May 2022 10:54:10 PM UTC
// All Rights Reserved
// ------------------------------------------------
#include <iostream>
#include <unistd.h>
#include <errno.h>
// #include <stdio.h>
#include <sys/wait.h>
#include <csignal>
// #include <vector>
// #include <regex>
#include <filesystem>
#include <map>

using namespace std;

void signal_handler_ctrl_c(int signum)
{
  map<int, char> signals
  {
    {2, 'c'},
    {20, 'z'}
  };
  cerr
    << "\nCtrl+" << signals[signum] << " was activated.\n";
  exit(signum);
}
int main()
{
  cout << "\x1b]0;UPGG\007" << flush;
  signal(SIGINT, signal_handler_ctrl_c);
  signal(SIGTSTP, signal_handler_ctrl_c);
  const string
    process_path_string = "/home/flux/.local/bin/updates",
    process_path_args   = "";
  filesystem::path process_path (process_path_string);
  if (!filesystem::exists(process_path))
  {
    cerr << process_path << " does not exist.\n";
    return 1;
  }
  if (!filesystem::is_regular_file(process_path))
  {
    cerr << process_path << " is not a valid file.\n";
    return 3;
  }
  char * argsCmdA[] =
  {
    const_cast<char*>(process_path_string.c_str()),
    NULL
  };
  int sysResult;
  pid_t pid;
  pid = fork();
  if (pid >= 0)
  {
    if (pid == 0)
    {
      return execvp(argsCmdA[0], argsCmdA);
    }
    else
    {
      waitpid(pid,&sysResult, 0);
      if (WEXITSTATUS(sysResult))
      {
        string message = "Error: [";
        message.append(to_string(WEXITSTATUS(sysResult)));
        message.append("] in command: [");
        message.append(process_path_string);
        message.push_back(' ');
        message.append(process_path_args);
        message.append("]\n");
        cerr << message;
      }
      return WEXITSTATUS(sysResult);
    }
  }
  else
  {
    cerr << "Program failed to fork.\n";
    return 4;
  }
  return EXIT_SUCCESS;
}
