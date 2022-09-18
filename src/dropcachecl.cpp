// -----------------------------------------------
// 'dropcachecl' - Edit "drop-caches" file
// Copyright © 2022
// Ian Pride @ New Pride Software/Services
// Sat 17 Sep 2022 13:03:04 CST
// -----------------------------------------------
#include <iostream>
#include <fstream>
#include <map>
#include <filesystem>
#include "Globals.h"
#include <pwd.h>
#include <unistd.h>
#include <ctime>
namespace filesys = std::filesystem;
std::chrono::milliseconds time_since_epoch_utc()
{
  std::chrono::time_point currently =
    std::chrono::time_point_cast<std::chrono::milliseconds>
    (
      std::chrono::system_clock::now()
    );
  return currently.time_since_epoch();
}
std::string time_utc()
{
  std::map<int, std::string> days =
  {
    {0, "Sun"}, {1, "Mon"}, {2, "Tue"}, {3, "Wed"},
    {4, "Thu"}, {5, "Fri"}, {6, "Sat"}
  };
  std::map<int, std::string> months =
  {
    {0, "Jan"}, {1, "Feb"}, {2, "Mar"}, {3, "Apr"},
    {4, "May"}, {5, "Jun"}, {6, "Jul"}, {7, "Aug"},
    {8, "Sep"}, {9, "Oct"}, {10, "Nov"}, {11, "Dec"}
  };
  time_t time_raw;
  // struct tm *tm_ptr;
  struct tm tm_ptr;
  time(&time_raw);
  gmtime_r(&time_raw, &tm_ptr);
  // tm_ptr = gmtime(&time_raw);
  const std::string weekday = days[tm_ptr.tm_wday];
  const std::string month = months[tm_ptr.tm_mon];
  const std::string day_of_month(std::to_string(tm_ptr.tm_mday));
  const std::string year = [tm_ptr]()
  {
    return std::to_string((tm_ptr.tm_year) + 1900);
  }();
  const std::string hour = [tm_ptr]()
  {
    std::string hour_string =
        std::to_string(tm_ptr.tm_hour);
    if (hour_string.length() < 2)
    {
      hour_string.insert(0, "0");
    }
    return hour_string;
  }();
  const std::string minute = [tm_ptr]()
  {
    std::string hour_string =
        std::to_string(tm_ptr.tm_min);
    if (hour_string.length() < 2)
    {
      hour_string.insert(0, "0");
    }
    return hour_string;
  }();
  const std::string second = [tm_ptr]()
  {
    std::string hour_string =
        std::to_string(tm_ptr.tm_sec);
    if (hour_string.length() < 2)
    {
      hour_string.insert(0, "0");
    }
    return hour_string;
  }();
  const std::string meridiem = [tm_ptr]()
  {
    return ((int(tm_ptr.tm_hour) < 12)?"AM":"PM");
  }();
  std::string time;
  time.append(weekday);       time.push_back(' ');
  time.append(day_of_month);  time.push_back(' ');
  time.append(month);         time.push_back(' ');
  time.append(year);          time.push_back(' ');
  time.append(hour);          time.push_back(':');
  time.append(minute);        time.push_back(':');
  time.append(second);        time.push_back(' ');
  time.append(meridiem);      time.push_back(' ');
  time.append("UTC");
  return time;
} 
int main(int argc, const char *argv[])
{
  // TODO Add switches
  // -h,--help          // This HELP message
  // -l, --logger       // enable logging
  // -d,--default       // 0
  // -p,--pagecache     // 1
  // -s,--slabobjects   // 2
  // -f,--fullcache     // 3
  // -m,--mode          // specify mode by name or int
  bool logStdout = true;
  bool logStderr = true;
  std::ofstream logger("/var/log/dropcachecl.log", std::ios_base::app);
  const filesys::path dropCachesPath("/proc/sys/vm/drop_caches");
  Globals::Structs::ExitCodes genericCode;
  std::map<std::string, int> option_map =
  {
    {"default",     0}, {"0", 0},
    {"pagecache",   1}, {"1", 1},
    {"slabobjects", 2}, {"2", 2},
    {"fullcache",   3}, {"3", 3}
  };
  std::string optionString  = "pagecache";
  int optionInteger         = option_map[optionString];
  std::ofstream ofile(dropCachesPath.native().c_str());
  if (ofile.is_open())
  {
    ofile << option_map[optionString];
    if (logStdout && logger.is_open())
    {
      std::string logMessage
      (
        "Drop Cache set to [" + std::to_string(option_map[optionString]) +
        ":" + optionString + "] @ " + time_utc() + "\n"
      );
      logger << logMessage;
    }
    ofile.close();
  }
  else
  {
    try
    {
      genericCode.value = 2;
      genericCode.message =
        std::string
        (
          "Could not open '" +
          dropCachesPath.native() +
          "' for writing.\nDo you have root privileges?"
        );
      throw genericCode;
    }
    catch(Globals::Structs::ExitCodes & code)
    {
      std::cerr << code.message << '\n';
      std::exit(code.value);
    }
  }
  if ((logStderr || logStdout) && logger.is_open())
  {
    logger.close();
  }
  return genericCode.value;
}
