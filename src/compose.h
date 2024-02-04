#pragma once

#include "content.h"
#include "global_config.h"
#include "logger.h"

#include <array>
#include <climits>
#include <cstdint>
#include <format>
#include <memory>
#include <optional>
#include <tuple>
#include <type_traits>
#include <utility>

template <global_config Config>
class composer
{
 public:
 template <class ... Indices_Set, std :: size_t N>
 constexpr static bool valid_for_array(std :: tuple<Indices_Set...>) noexcept;
 template <class ... Indices_Set, std :: size_t N>
 constexpr static bool valid_for_struct(std :: tuple<Indices_Set...>) noexcept;
 template <class ... Indices_Set, std :: size_t N>
 static auto compose_as_array(const std :: shared_ptr<content<N, Config> >& source, std :: tuple<Indices_Set...>) noexcept
 requires(valid_for_array<N>(std :: tuple<Indices_Set...>()));
 template <class ... Indices_Set, std :: size_t N>
 static auto compose_as_struct(const std :: shared_ptr<content<N, Config> >& source, std :: tuple<Indices_Set...>) noexcept
 requires(valid_for_struct<N>(std :: tuple<Indices_Set...>()));
 template <std :: size_t ... Indices, std :: size_t N>
 static auto compose(const std :: shared_ptr<content<N, Config> >& source) noexcept requires(((Indices < N) && ...));
 private:
 template <class Type, std :: size_t ... Indices, std :: size_t N>
 static auto basic_compose(const std :: shared_ptr<content<N, Config> >& source) noexcept requires(((Indices < N) && ...));
};

template <global_config Config>
template <std :: size_t ... Indices, std :: size_t N>
auto composer <Config> :: compose(const std :: shared_ptr<content<N, Config> >& source) noexcept
requires(((Indices < N) && ...))
{
 if constexpr (sizeof...(Indices) == 1zu)
 {
  using Type = std :: uint8_t;
  if (!source)
  {
   logger<Config, log_level :: error>().log("Content not set.");
   return static_cast<std :: optional<Type> >(std :: nullopt);
  }
  return basic_compose<Type, Indices...>(source);
 }
 else if constexpr (sizeof...(Indices) == 2zu)
 {
  using Type = std :: uint16_t;
  if (!source)
  {
   logger<Config, log_level :: error>().log("Content not set.");
   return static_cast<std :: optional<Type> >(std :: nullopt);
  }
  return basic_compose<Type, Indices...>(source);
 }
 else if constexpr (sizeof...(Indices) == 4zu)
 {
  using Type = std :: uint32_t;
  if (!source)
  {
   logger<Config, log_level :: error>().log("Content not set.");
   return static_cast<std :: optional<Type> >(std :: nullopt);
  }
  return basic_compose<Type, Indices...>(source);
 }
 else if constexpr (sizeof...(Indices) == 8zu)
 {
  using Type = std :: uint64_t;
  if (!source)
  {
   logger<Config, log_level :: error>().log("Content not set.");
   return static_cast<std :: optional<Type> >(std :: nullopt);
  }
  return basic_compose<Type, Indices...>(source);
 }
 else static_assert(false, std :: format("Unsupported length of indices. Expected 1, 2, 4 or 8 but got {}", sizeof...(Indices)));
}

template <global_config Config>
template <class Type, std :: size_t ... Indices, std :: size_t N>
auto composer <Config> :: basic_compose(const std :: shared_ptr<content<N, Config> >& source) noexcept
requires(((Indices < N) && ...))
{
 const auto impl = [&source]<std :: size_t ... Ns>(std :: type_identity<Type>, std :: index_sequence<Ns...>) noexcept
 {
  const auto& data = source->getData();
  return std :: make_optional<Type>(((static_cast<Type>(data[Indices]) << ((sizeof...(Ns) - Ns - 1zu) * CHAR_BIT)) | ...));
 };
 return impl(std :: type_identity<Type>(), std :: make_index_sequence<sizeof...(Indices)>());
}

