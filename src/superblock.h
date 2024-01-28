#pragma once

#include "compose.h"
#include "content.h"
#include "global_config.h"
#include "system_config.h"

#include <cstdint>
#include <memory>
#include <utility>

template <system_config System, global_config Config> class superblock
{
 constexpr static bool has_inodes_count() noexcept;
 constexpr static bool has_lpf_ino() noexcept;
 public:
 template <class Self> auto get_inodes_count(this Self&& self) noexcept requires(has_inodes_count());
 template <class Self> auto get_lpf_ino(this Self&& self) noexcept requires(has_lpf_ino());
 private:
 constexpr const static std :: size_t total_size = 1024zu;
 std :: shared_ptr<content<total_size, Config> > block;
};

template <system_config System, global_config Config>
constexpr inline bool superblock <System, Config> :: has_inodes_count() noexcept
{
 return true;
}

template <system_config System, global_config Config>
constexpr inline bool superblock <System, Config> :: has_lpf_ino() noexcept
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

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_inodes_count(this Self&& self) noexcept
requires(superblock <System, Config> :: has_inodes_count())
{
 return compose<0x003zu, 0x002zu, 0x001zu, 0x000zu>(std :: forward<Self>(self).block);
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_lpf_ino(this Self&& self) noexcept
requires(superblock <System, Config> :: has_lpf_ino())
{
 return compose<0x26B, 0x26A, 0x269, 0x268>(std :: forward<Self>(self).block);
}
