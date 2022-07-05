#pragma once
#ifndef BENCH_H
#define BENCH_H

#include <iostream>
#include <chrono>

namespace Bench
{
  extern std::chrono::time_point<std::chrono::system_clock> Start;
  extern std::chrono::time_point<std::chrono::system_clock> Stop;
  extern void start();
  extern void stop();
  extern std::string format_duration(
      std::chrono::time_point<std::chrono::system_clock> start_,
      std::chrono::time_point<std::chrono::system_clock> stop_);
  extern void print_duration(
      std::string pre, std::string post,
      std::chrono::time_point<std::chrono::system_clock> start_,
      std::chrono::time_point<std::chrono::system_clock> stop_);
};

#endif
