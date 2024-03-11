#pragma once

#include "system_config.h"

template <system_config System> class system_query
{
 ~system_query() = delete;
 public:
 constexpr static bool is_64bit() noexcept;
 constexpr static bool is_having_block_preallocation() noexcept;
 constexpr static bool is_having_case_fold() noexcept
};

template <system_config System>
constexpr inline bool system_query <System> :: is_64bit() noexcept
{
 switch (System.file_system)
 {
  using enum system_config :: file_system_t;
  case ext:
  case ext2:
  case ext3:
  return false;
  case ext4:
  return is_flag_set<System, system_config :: feature_incompat_flags <ext4> :: bits64>();
 }
}

template <system_config System>
constexpr inline bool system_query <System> :: is_having_block_preallocation() noexcept
{
 switch (System.file_system)
 {
  using enum system_config :: file_system_t;
  case ext:
  return false;
  case ext2:
  return is_flag_set<System, system_config :: feature_compat_flags <ext2> :: dir_prealloc>();
  case ext3:
  return is_flag_set<System, system_config :: feature_compat_flags <ext3> :: dir_prealloc>();
  case ext4:
  return is_flag_set<System, system_config :: feature_compat_flags <ext4> :: dir_prealloc>();
 }
}

template <system_config System>
constexpr inline bool system_query <System> :: is_having_case_fold() noexcept
{
 switch (System.file_system)
 {
  using enum system_config :: file_system_t;
  case ext:
  case ext2:
  case ext3:
  return false;
  case ext4:
  return is_flag_set<System, system_config :: feature_incompat_flags <ext4> :: case_fold>();
 }
}
