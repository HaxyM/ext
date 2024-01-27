#pragma once

#include "system_config.h"

#include <cstdint>

template <system_config System> class superblock
{
 constexpr static bool has_inodes_count() noexcept;
 constexpr static bool has_lpf_ino() noexcept;
 public:
 using inodes_count_t = std :: uint32_t;
 using lpf_ino_t = std :: uint32_t;
 inodes_count_t get_inodes_count() const noexcept requires(has_inodes_count());
 lpf_ino_t get_lpf_ino() const noexcept requires(has_lpf_ino());
};

template <system_config System> using superblock_inodes_count_t = typename superblock <System> :: inodes_count_t;
template <system_config System> using superblock_lpf_ino_t = typename superblock <System> :: lpf_ino_t; 

template <system_config System> constexpr inline bool superblock <System> :: has_inodes_count() noexcept
{
 return true;
}

template <system_config System> constexpr inline bool superblock <System> :: has_lpf_ino() noexcept
{
 switch (System.file_system)
 {
  using enum system_config :: file_system_t;
  case ext:
  case ext2:
  case ext3:
  return false;
  case ext4:
  return true;
 }
}

template <system_config System>
inline superblock_inodes_count_t<System>
superblock <System> :: get_inodes_count() const noexcept requires(superblock <System> :: has_inodes_count())
{
 return {};
}

template <system_config System>
inline superblock_lpf_ino_t<System>
superblock <System> :: get_lpf_ino() const noexcept requires(superblock <System> :: has_lpf_ino())
{
 return {};
}
