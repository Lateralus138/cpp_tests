#include "Bench.h"

namespace Bench
{
  std::chrono::time_point<std::chrono::system_clock> Start;
  std::chrono::time_point<std::chrono::system_clock> Stop;
  void start()
  {
    Bench::Start = std::chrono::high_resolution_clock::now();
  }
  void stop()
  {
    Bench::Stop = std::chrono::high_resolution_clock::now();
  }
  std::string format_duration(
      std::chrono::time_point<std::chrono::system_clock> start_,
      std::chrono::time_point<std::chrono::system_clock> stop_)
  {
    std::string format = "[\x1b[92m";
    auto diff = (stop_ - start_);
    format.append(
        std::to_string(
            std::chrono::duration_cast<std::chrono::microseconds>(diff).count()) +
        "\x1b[32mµs\x1b[m|\x1b[93m");
    format.append(
        std::to_string(
            std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()) +
        "\x1b[33mms\x1b[m|\x1b[95m");
    format.append(
        std::to_string(
            std::chrono::duration_cast<std::chrono::seconds>(diff).count()) +
        "\x1b[35ms\x1b[m]");
    return format;
  }
  void print_duration(
      std::string pre, std::string post,
      std::chrono::time_point<std::chrono::system_clock> start_,
      std::chrono::time_point<std::chrono::system_clock> stop_)
  {
    std::cout << pre + format_duration(start_, stop_) + post;
  }
};
