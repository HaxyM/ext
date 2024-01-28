#pragma once

#include <climits>
#include <cstdint>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>

#include "content.h"
#include "global_config.h"
#include "logger.h"

template <std :: size_t ... Indices, global_config Config, std :: size_t N>
auto compose(const std :: shared_ptr<content<N, Config> >& source) noexcept requires(((Indices < N) && ...))
{
 const auto impl = [&source]<class Type, std :: size_t ... Ns>(std :: type_identity<Type>, std :: index_sequence<Ns...>) noexcept
 {
  if (!source)
  {
   logger<Config, log_level :: error> l; l.log("Content not set.");
   return static_cast<std :: optional<Type> >(std :: nullopt);
  }
  const auto& data = source->getData();
  return std :: make_optional<Type>(((static_cast<Type>(data[Indices]) << ((sizeof...(Ns) - Ns - 1zu) * CHAR_BIT)) | ...));
 };
 if constexpr (sizeof...(Indices) == 1zu) return impl(std :: type_identity<std :: uint8_t>(), std :: make_index_sequence<sizeof...(Indices)>());
 if constexpr (sizeof...(Indices) == 2zu) return impl(std :: type_identity<std :: uint16_t>(), std :: make_index_sequence<sizeof...(Indices)>());
 if constexpr (sizeof...(Indices) == 4zu) return impl(std :: type_identity<std :: uint32_t>(), std :: make_index_sequence<sizeof...(Indices)>());
 if constexpr (sizeof...(Indices) == 8zu) return impl(std :: type_identity<std :: uint64_t>(), std :: make_index_sequence<sizeof...(Indices)>());
 std :: unreachable();
}
