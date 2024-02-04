#pragma once

#include "global_config.h"

#include <chrono>
#include <format>
#include <iostream>
#include <mutex>
#include <optional>
#include <source_location>
#include <stacktrace>
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
 constexpr static bool outputAnything() noexcept;
 constexpr static bool useSourceLocation() noexcept;
 constexpr static bool useStackTrace() noexcept;
 public:
 logger() noexcept requires(!useSourceLocation() && !useStackTrace());
 logger(std :: stacktrace&& t = std :: stacktrace :: current()) noexcept requires(!useSourceLocation() && useStackTrace());
 logger(std :: source_location&& l = std :: source_location :: current()) noexcept requires(useSourceLocation() && !useStackTrace());
 logger(std :: source_location&& l = std :: source_location :: current(), std :: stacktrace&& t = std :: stacktrace :: current()) noexcept requires(useSourceLocation() && useStackTrace());
 template <class ... Args> bool log(Args&& ... args) noexcept;
 private:
 static std :: ostream& getOutput() noexcept;
 static std :: optional<std :: unique_lock<std :: mutex> > getLock();
 template <bool has_location, bool has_trace, class ... Empty> struct content;
 template <class ... Empty> struct content<false, false, Empty...>{};
 template <class ... Empty> struct content<false, true, Empty...>;
 template <class ... Empty> struct content<true, false, Empty...>;
 template <class ... Empty> struct content<true, true, Empty...>;
 content<useSourceLocation(), useStackTrace()> cont;
};

template <global_config Config, log_level Level>
template <class ... Empty>
struct logger <Config, Level> :: template content<false, true, Empty...>
{
 std :: stacktrace trace;
};

template <global_config Config, log_level Level>
template <class ... Empty>
struct logger <Config, Level> :: template content<true, false, Empty...>
{
 std :: source_location location;
};

template <global_config Config, log_level Level>
template <class ... Empty>
struct logger <Config, Level> :: template content<true, true, Empty...>
{
 std :: source_location location;
 std :: stacktrace trace;
};

template <global_config Config, log_level Level>
constexpr inline bool logger <Config, Level> :: outputAnything() noexcept
{
  using enum global_config :: verbocity_level;
  if constexpr (Config.verbocity == quiet) return false;
  else if constexpr (Config.verbocity == normal && Level == log_level :: debug) return false;
  else if constexpr (Config.verbocity == normal && Level == log_level :: info) return false;
  else return true;
}

template <global_config Config, log_level Level>
constexpr inline bool logger <Config, Level> :: useSourceLocation() noexcept
{
  using enum global_config :: verbocity_level;
  if constexpr (!outputAnything()) return false;
  else return (Level == log_level :: debug) || Config.debug;
}

template <global_config Config, log_level Level>
constexpr inline bool logger <Config, Level> :: useStackTrace() noexcept
{
 using enum global_config :: verbocity_level;
 if constexpr (!outputAnything()) return false;
 else return Config.debug && (Level == log_level :: error);
}

template <global_config Config, log_level Level>
inline logger <Config, Level> :: logger() noexcept
requires(!logger <Config, Level> :: useSourceLocation() && !logger <Config, Level> :: useStackTrace())
{
}

template <global_config Config, log_level Level>
inline logger <Config, Level> :: logger(std :: stacktrace&& t) noexcept
requires(!logger <Config, Level> :: useSourceLocation() && logger <Config, Level> :: useStackTrace())
	: cont{.trace = std :: forward<std :: stacktrace>(t)}
{
}

template <global_config Config, log_level Level>
inline logger <Config, Level> :: logger(std :: source_location&& l) noexcept
requires(logger <Config, Level> :: useSourceLocation() && !logger <Config, Level> :: useStackTrace())
	: cont{.location = std :: forward<std :: source_location>(l)}
{
}

template <global_config Config, log_level Level>
inline logger <Config, Level> :: logger(std :: source_location&& l, std :: stacktrace&& t) noexcept
requires(logger <Config, Level> :: useSourceLocation() && logger <Config, Level> :: useStackTrace())
	: cont{.location = std :: forward<std :: source_location>(l), .trace = std :: forward<std :: stacktrace>(t)}
{
}

template <global_config Config, log_level Level>
template <class ... Args>
inline bool logger <Config, Level> :: log(Args&& ... args) noexcept
{
 try
 {
  using enum global_config :: verbocity_level;
  if constexpr (!outputAnything()) return true;
  else
  {
   auto& output = getOutput();
   const auto lock = getLock();
   if constexpr (useSourceLocation())
   {
    output << cont.location.file_name() << " at " << cont.location.line() << ": ";
    output << std :: format("{0:%F_%T}", std :: chrono :: system_clock :: now()) << ' ';
   }
   if constexpr (useStackTrace())
   {
    return static_cast<bool>((output << ... << std :: forward<Args>(args)) << std :: endl << cont.trace << std :: endl);
   }
   else return static_cast<bool>((output << ... << std :: forward<Args>(args)) << std :: endl);
  }
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
