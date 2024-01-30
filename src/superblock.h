#pragma once

#include "compose.h"
#include "content.h"
#include "global_config.h"
#include "logger.h"
#include "system_config.h"

#include <cstdint>
#include <memory>
#include <utility>

template <system_config System, global_config Config> class superblock
{
 constexpr static bool has_inodes_count() noexcept;
 constexpr static bool has_free_blocks_count() noexcept;
 constexpr static bool has_magic() noexcept;
 constexpr static bool has_creator_os() noexcept;
 constexpr static bool has_rev_level() noexcept;
 constexpr static bool has_lpf_ino() noexcept;
 public:
 enum class magic_t;
 //Field getters
 template <class Self> auto get_inodes_count(this Self&& self) noexcept requires(has_inodes_count());
 template <class Self> auto get_free_blocks_count(this Self&& self) noexcept requires(has_free_blocks_count);
 template <class Self> auto get_magic(this Self&& self) noexcept requires(has_magic());
 template <class Self> auto get_creator_os(this Self&& self) noexcept requires(has_creator_os());
 template <class Self> auto get_rev_level(this Self&& self) noexcept requires(has_rev_level());
 template <class Self> auto get_lpf_ino(this Self&& self) noexcept requires(has_lpf_ino());
 //Universal
 constexpr static std :: size_t get_block_size() noexcept;
 template <class Self> auto&& get_block(this Self&& self) noexcept;
 private:
 std :: shared_ptr<content<get_block_size(), Config> > block;
};

template <system_config System, global_config Config>
enum class superblock <System, Config> :: magic_t
{
 old_ext1,
 ext2_and_later
};

template <system_config System, global_config Config>
constexpr inline bool superblock <System, Config> :: has_inodes_count() noexcept
{
 return true;
}

template <system_config System, global_config Config>
constexpr inline bool superblock <System, Config> :: has_free_blocks_count() noexcept
{
 return true;
}

template <system_config System, global_config Config>
constexpr inline bool superblock <System, Config> :: has_magic() noexcept
{
 return true;
}

template <system_config System, global_config Config>
constexpr inline bool superblock <System, Config> :: has_creator_os() noexcept
{
 switch (System.file_system)
 {
  using enum system_config :: file_system_t;
  case ext:
  return false;
  case ext2:
  case ext3:
  case ext4:
  return true;
 }
}

template <system_config System, global_config Config>
constexpr inline bool superblock <System, Config> :: has_rev_level() noexcept
{
 switch (System.file_system)
 {
  using enum system_config :: file_system_t;
  case ext:
  return false;
  case ext2:
  case ext3:
  case ext4:
  return true;
 }
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
inline auto superblock <System, Config> :: get_free_blocks_count(this Self&& self) noexcept
requires(superblock <System, Config> :: has_free_blocks_count())
{
 using enum system_config :: file_system_t;
 if constexpr ((System.file_system == ext4) && System.feature_compat_64bit)
 {
  return compose<0x15Bzu, 0x15Azu, 0x159zu, 0x158zu, 0x00Fzu, 0x00Ezu, 0x00Dzu, 0x00Czu>(std :: forward<Self>(self).block);
 }
 else if constexpr (System.file_system == ext)
 { //Ext1 has same location as other exts.
  return compose<0x00Fzu, 0x00Ezu, 0x00Dzu, 0x00Czu>(std :: forward<Self>(self).block);
 }
 else
 {
  return compose<0x00Fzu, 0x00Ezu, 0x00Dzu, 0x00Czu>(std :: forward<Self>(self).block);
 }
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_magic(this Self&& self) noexcept
requires(superblock <System, Config> :: has_magic())
{
 
 if (const auto magic = compose<0x039zu, 0x038zu>(std :: forward<Self>(self).block); !magic)
 {
  logger<Config, log_level :: error> l; l.log("Failed to read magic.");
  return static_cast<std :: optional<magic_t> >(std :: nullopt);
 }
 else switch (*magic)
 {
  using enum magic_t;
  case UINT16_C(0x137D):
  return std :: make_optional<magic_t>(old_ext1);
  case UINT16_C(0xEF53):
  return std :: make_optional<magic_t>(ext2_and_later);
  default:
  {
   logger<Config, log_level :: error> l; l.log("Unknown magic: ", std :: hex, *magic);
   return static_cast<std :: optional<magic_t> >(std :: nullopt);
  }
 }
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_creator_os(this Self&& self) noexcept
requires(superblock <System, Config> :: has_creator_os())
{
 if (const auto os = compose<0x04Bzu, 0x04Azu, 0x049zu, 0x048zu>(std :: forward<Self>(self).block); !os)
 {
  logger<Config, log_level :: error> l; l.log("Failed to read creator OS.");
  return static_cast<std :: optional<system_config :: creator_os_t> >(std :: nullopt);
 }
 else switch (*os)
 {
  using enum system_config :: creator_os_t;
  case UINT32_C(0):
  return std :: make_optional<system_config :: creator_os_t>(linux);
  case UINT32_C(1):
  return std :: make_optional<system_config :: creator_os_t>(hurd);
  case UINT32_C(2):
  return std :: make_optional<system_config :: creator_os_t>(masix);
  case UINT32_C(3):
  return std :: make_optional<system_config :: creator_os_t>(free_bsd);
  case UINT32_C(4):
  return std :: make_optional<system_config :: creator_os_t>(lites);
  default:
  {
   logger<Config, log_level :: error> l; l.log("Unknown creator OS: ", std :: hex, *os);
   return static_cast<std :: optional<system_config :: creator_os_t> >(std :: nullopt);
  }
 }
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_rev_level(this Self&& self) noexcept
requires(superblock <System, Config> :: has_rev_level())
{
 if (const auto lev = compose<0x04Fzu, 0x04Ezu, 0x04Dzu, 0x04Czu>(std :: forward<Self>(self).block); !lev)
 {
  logger<Config, log_level :: error> l; l.log("Failed to read revision level.");
  return static_cast<std :: optional<system_config :: revision_t> >(std :: nullopt);
 }
 else switch (*lev)
 {
  using enum system_config :: revision_t;
  case UINT32_C(0):
  return std :: make_optional<system_config :: revision_t>(good_old_rev);
  case UINT32_C(1):
  return std :: make_optional<system_config :: revision_t>(dynamic_rev);
  default:
  {
   logger<Config, log_level :: error> l; l.log("Unknown revision level: ", std :: hex, *lev);
   return static_cast<std :: optional<system_config :: revision_t> >(std :: nullopt);
  }
 }
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_lpf_ino(this Self&& self) noexcept
requires(superblock <System, Config> :: has_lpf_ino())
{
 return compose<0x26Bzu, 0x26Azu, 0x269zu, 0x268zu>(std :: forward<Self>(self).block);
}

template <system_config System, global_config Config>
constexpr inline std :: size_t superblock <System, Config> :: get_block_size() noexcept
{
 switch (System.file_system)
 {
  using enum system_config :: file_system_t;
  case ext:
  return 58zu; //Linux 2.1.20 reads whole 1024 octets, but names fields (including reservedSTH) only up to "magic".
  case ext2:
  case ext3:
  case ext4:
  return 1024zu;
 }
}

template <system_config System, global_config Config> template <class Self>
inline auto&& superblock <System, Config> :: get_block(this Self&& self) noexcept
{
 return std :: forward<Self>(self).block;
}
