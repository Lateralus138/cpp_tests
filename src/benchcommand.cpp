// -----------------------------------------------
// 'benchcommand'
// Copyright © 2022
// Ian Pride @ New Pride Software/Services
// Fri 16 Sep 2022 17:19:41 CST
// -----------------------------------------------
#include "Bench.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <wait.h>
#include <csignal>
#include <chrono>
using namespace Bench;

inline void signal_handler(int signum)
{
  if (std::chrono::duration_cast<std::chrono::microseconds>(Start - Stop).count() > 0)
  {
    stop();
    print_duration("\nExecution time: ", "", Bench::Start, Bench::Stop);
  }
  std::cerr << "\nProgram Interrupted by the user.\n";
  std::exit(signum);
}

int main(int argc, char * const argv[])
{
  signal(SIGINT, signal_handler);
  int exit_status = 0;
  if (argc < 2)
  {
    try
    {
      exit_status = 191;
      throw std::runtime_error("Not enough arguments passed to the program.\n");
    }
    catch (std::runtime_error & runtime_err)
    {
      std::cerr << runtime_err.what();
      std::exit(exit_status);
    }
  }
  pid_t fork_pid = fork();
  if (fork_pid == -1)
  {
    try
    {
      exit_status = 191;
      throw std::runtime_error("Could not fork the process for an unknown reason.\n");
    }
    catch (std::runtime_error & runtime_err)
    {
      std::cerr << runtime_err.what();
      std::exit(exit_status);
    }
  }
  if (fork_pid == 0)
  {
    exit_status = execvp(argv[1], &argv[1]);
    return exit_status;
  }
  else
  {
    int status;
    start();
    waitpid(fork_pid, &status, 0);
    stop();
    print_duration("\nExecution time: ", "\n", Bench::Start, Bench::Stop);
    exit_status = (status/256);
  }
  return exit_status;
}