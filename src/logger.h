#pragma once

#include "global_config.h"

#include <chrono>
//#include <format>
#include <iostream>
#include <mutex>
#include <optional>
#include <source_location>
#include <utility>

enum class log_level
{
 debug,
 info,
 error
};

template <global_config Config, log_level Level>
class logger
{
 public:
 logger(std :: source_location&& l = std :: source_location :: current()) noexcept;
 template <class ... Args> bool log(Args&& ... args) noexcept;
 private:
 static std :: ostream& getOutput() noexcept;
 static std :: optional<std :: unique_lock<std :: mutex> > getLock();
 std :: source_location location;
};

template <global_config Config, log_level Level>
inline logger <Config, Level> :: logger(std :: source_location&& l) noexcept
	: location(std :: forward<std :: source_location>(l))
{
}

template <global_config Config, log_level Level>
template <class ... Args>
inline bool logger <Config, Level> :: log(Args&& ... args) noexcept
{
 try
 {
  using enum global_config :: verbocity_level;
  if constexpr (Config.verbocity == quiet) return true;
  if constexpr (Config.verbocity == normal && Level == log_level :: debug) return true;
  if constexpr (Config.verbocity == normal && Level == log_level :: info) return true;
  auto& output = getOutput();
  const auto lock = getLock();
  if constexpr (Level == log_level :: debug || Config.debug)
  {
   output << location.file_name() << " at " << location.line() << ": ";
   output << std :: format("{0:%F_%T}", std :: chrono :: system_clock :: now()) << ' ';
  }
  return static_cast<bool>((output << ... << std :: forward<Args>(args)) << std :: endl);
  //output << std :: chrono :: system_clock :: now();
  //return true;
 }
 catch (...) {} return false;
}

template <global_config Config, log_level Level>
inline std :: ostream& logger <Config, Level> :: getOutput() noexcept
{
 if constexpr (Level == log_level :: debug) return std :: cout;
 if constexpr (Level == log_level :: info) return std :: cout;
 if constexpr (Level == log_level :: error) return std :: cerr;
}

template <global_config Config, log_level Level>
inline std :: optional<std :: unique_lock<std :: mutex> > logger <Config, Level> :: getLock()
{
 if constexpr (Config.threads != 1zu)
 {
  static std :: mutex loggerGuard = {};
  std :: unique_lock lock{loggerGuard};
  return {std :: move(lock)};
 }
 return std :: nullopt;
}

