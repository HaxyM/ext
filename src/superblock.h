#pragma once

#include "compose.h"
#include "content.h"
#include "global_config.h"
#include "logger.h"
#include "system_config.h"

#include <chrono>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>

template <system_config System, global_config Config> class superblock
{
 public:
 //Queries
 constexpr static bool has_inodes_count() noexcept;
 constexpr static bool has_blocks_count() noexcept;
 constexpr static bool has_reserved_blocks_count() noexcept;
 constexpr static bool has_free_blocks_count() noexcept;
 constexpr static bool has_free_inodes_count() noexcept;
 constexpr static bool has_mount_time() noexcept;
 constexpr static bool has_write_time() noexcept;
 constexpr static bool has_magic() noexcept;
 constexpr static bool has_last_check() noexcept;
 constexpr static bool has_creator_os() noexcept;
 constexpr static bool has_rev_level() noexcept;
 constexpr static bool has_mkfs_time() noexcept;
 constexpr static bool has_first_error_time() noexcept;
 constexpr static bool has_last_error_time() noexcept;
 constexpr static bool has_lpf_ino() noexcept;
 //Subtypes
 enum class magic_t;
 using time_point_t = std :: chrono :: time_point<std :: chrono :: file_clock>;
 //Field getters
 template <class Self> auto get_inodes_count(this Self&& self) noexcept requires(has_inodes_count());
 template <class Self> auto get_blocks_count(this Self&& self) noexcept requires(has_blocks_count());
 template <class Self> auto get_reserved_blocks_count(this Self&& self) noexcept requires(has_reserved_blocks_count());
 template <class Self> auto get_free_blocks_count(this Self&& self) noexcept requires(has_free_blocks_count());
 template <class Self> auto get_free_inodes_count(this Self&& self) noexcept requires(has_free_inodes_count());
 template <class Self> auto get_mount_time(this Self&& self) noexcept requires(has_mount_time());
 template <class Self> auto get_write_time(this Self&& self) noexcept requires(has_write_time());
 template <class Self> auto get_magic(this Self&& self) noexcept requires(has_magic());
 template <class Self> auto get_last_check(this Self&& self) noexcept requires(has_last_check());
 template <class Self> auto get_creator_os(this Self&& self) noexcept requires(has_creator_os());
 template <class Self> auto get_rev_level(this Self&& self) noexcept requires(has_rev_level());
 template <class Self> auto get_mkfs_time(this Self&& self) noexcept requires(has_mkfs_time());
 template <class Self> auto get_first_error_time(this Self&& self) noexcept requires(has_first_error_time());
 template <class Self> auto get_last_error_time(this Self&& self) noexcept requires(has_last_error_time());
 template <class Self> auto get_lpf_ino(this Self&& self) noexcept requires(has_lpf_ino());
 //Universal
 constexpr static std :: size_t get_block_size() noexcept;
 template <class Self> auto&& get_block(this Self&& self) noexcept;
 private:
 template <class Self, std :: size_t ... Indices> auto read(this Self&& self, std :: index_sequence<Indices...>) noexcept;
 //Indices
 constexpr static auto get_inodes_count_indices() noexcept requires(has_inodes_count());
 constexpr static auto get_blocks_count_indices() noexcept requires(has_blocks_count());
 constexpr static auto get_reserved_blocks_count_indices() noexcept requires(has_reserved_blocks_count());
 constexpr static auto get_free_blocks_count_indices() noexcept requires(has_free_blocks_count());
 constexpr static auto get_free_inodes_count_indices() noexcept requires(has_free_inodes_count());
 constexpr static auto get_mount_time_indices() noexcept requires(has_mount_time());
 constexpr static auto get_write_time_indices() noexcept requires(has_write_time());
 constexpr static auto get_magic_indices() noexcept requires(has_magic());
 constexpr static auto get_last_check_indices() noexcept requires(has_last_check());
 constexpr static auto get_creator_os_indices() noexcept requires(has_creator_os());
 constexpr static auto get_rev_level_indices() noexcept requires(has_rev_level());
 constexpr static auto get_mkfs_time_indices() noexcept requires(has_mkfs_time());
 constexpr static auto get_first_error_time_indices() noexcept requires(has_first_error_time());
 constexpr static auto get_last_error_time_indices() noexcept requires(has_last_error_time());
 constexpr static auto get_lpf_ino_indices() noexcept requires(has_lpf_ino());
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
constexpr inline bool superblock <System, Config> :: has_blocks_count() noexcept
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
constexpr inline bool superblock <System, Config> :: has_reserved_blocks_count() noexcept
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
constexpr inline bool superblock <System, Config> :: has_free_blocks_count() noexcept
{
 return true;
}

template <system_config System, global_config Config>
constexpr inline bool superblock <System, Config> :: has_free_inodes_count() noexcept
{
 return true;
}

template <system_config System, global_config Config>
constexpr inline bool superblock <System, Config> :: has_mount_time() noexcept
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
constexpr inline bool superblock <System, Config> :: has_write_time() noexcept
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
constexpr inline bool superblock <System, Config> :: has_magic() noexcept
{
 return true;
}

template <system_config System, global_config Config>
constexpr inline bool superblock <System, Config> :: has_last_check() noexcept
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
constexpr inline bool superblock <System, Config> :: has_mkfs_time() noexcept
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

template <system_config System, global_config Config>
constexpr inline bool superblock <System, Config> :: has_first_error_time() noexcept
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

template <system_config System, global_config Config>
constexpr inline bool superblock <System, Config> :: has_last_error_time() noexcept
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
 return std :: forward<Self>(self).read(get_inodes_count_indices());
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_blocks_count(this Self&& self) noexcept
requires(superblock <System, Config> :: has_blocks_count())
{
 return std :: forward<Self>(self).read(get_blocks_count_indices());
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_reserved_blocks_count(this Self&& self) noexcept
requires(superblock <System, Config> :: has_reserved_blocks_count())
{
 return std :: forward<Self>(self).read(get_reserved_blocks_count_indices());
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_free_blocks_count(this Self&& self) noexcept
requires(superblock <System, Config> :: has_free_blocks_count())
{
 return std :: forward<Self>(self).read(get_free_blocks_count_indices());
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_free_inodes_count(this Self&& self) noexcept
requires(superblock <System, Config> :: has_free_inodes_count())
{
 return std :: forward<Self>(self).read(get_free_inodes_count_indices());
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_mount_time(this Self&& self) noexcept
requires(superblock <System, Config> :: has_mount_time())
{
 if (const auto mtime = std :: forward<Self>(self).read(get_mount_time_indices()); !mtime)
 {
  logger<Config, log_level :: error>().log("Failed to read last mount time.");
  return static_cast<std :: optional<time_point_t> >(std :: nullopt);
 }
 else return static_cast<time_point_t :: duration>(std :: chrono :: seconds(*mtime));
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_write_time(this Self&& self) noexcept
requires(superblock <System, Config> :: has_write_time())
{
 if (const auto wtime = std :: forward<Self>(self).read(get_write_time_indices()); !wtime)
 {
  logger<Config, log_level :: error>().log("Failed to read last write time.");
  return static_cast<std :: optional<time_point_t> >(std :: nullopt);
 }
 else return static_cast<time_point_t :: duration>(std :: chrono :: seconds(*wtime));
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_magic(this Self&& self) noexcept
requires(superblock <System, Config> :: has_magic())
{
 if (const auto magic = std :: forward<Self>(self).read(get_magic_indices()); !magic)
 {
  logger<Config, log_level :: error>().log("Failed to read magic.");
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
   logger<Config, log_level :: error>().log("Unknown magic: ", std :: hex, *magic);
   return static_cast<std :: optional<magic_t> >(std :: nullopt);
  }
 }
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_last_check(this Self&& self) noexcept
requires(superblock <System, Config> :: has_last_check())
{
 if (const auto last = std :: forward<Self>(self).read(get_last_check_indices()); !last)
 {
  logger<Config, log_level :: error>().log("Failed to read last check time.");
  return static_cast<std :: optional<time_point_t> >(std :: nullopt);
 }
 else return static_cast<time_point_t :: duration>(std :: chrono :: seconds(*last));
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_creator_os(this Self&& self) noexcept
requires(superblock <System, Config> :: has_creator_os())
{
 if (const auto os = std :: forward<Self>(self).read(get_creator_os_indices()); !os)
 {
  logger<Config, log_level :: error>().log("Failed to read creator OS.");
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
   logger<Config, log_level :: error>().log("Unknown creator OS: ", std :: hex, *os);
   return static_cast<std :: optional<system_config :: creator_os_t> >(std :: nullopt);
  }
 }
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_rev_level(this Self&& self) noexcept
requires(superblock <System, Config> :: has_rev_level())
{
 if (const auto lev = std :: forward<Self>(self).read(get_rev_level_indices()); !lev)
 {
  logger<Config, log_level :: error>().log("Failed to read revision level.");
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
   logger<Config, log_level :: error>().log("Unknown revision level: ", std :: hex, *lev);
   return static_cast<std :: optional<system_config :: revision_t> >(std :: nullopt);
  }
 }
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_mkfs_time(this Self&& self) noexcept
requires(superblock <System, Config> :: has_mkfs_time())
{
 if (const auto created = std :: forward<Self>(self).read(get_mkfs_time_indices()); !created)
 {
  logger<Config, log_level :: error>().log("Failed to read creation time.");
  return static_cast<std :: optional<time_point_t> >(std :: nullopt);
 }
 else return static_cast<time_point_t :: duration>(std :: chrono :: seconds(*created));
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_first_error_time(this Self&& self) noexcept
requires(superblock <System, Config> :: has_first_error_time())
{
 if (const auto first = std :: forward<Self>(self).read(get_first_error_time_indices()); !first)
 {
  logger<Config, log_level :: error>().log("Failed to read first error time.");
  return static_cast<std :: optional<time_point_t> >(std :: nullopt);
 }
 else return static_cast<time_point_t :: duration>(std :: chrono :: seconds(*first));
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_last_error_time(this Self&& self) noexcept
requires(superblock <System, Config> :: has_last_error_time())
{
 if (const auto last = std :: forward<Self>(self).read(get_last_error_time_indices()); !last)
 {
  logger<Config, log_level :: error>().log("Failed to read last error time.");
  return static_cast<std :: optional<time_point_t> >(std :: nullopt);
 }
 else return static_cast<time_point_t :: duration>(std :: chrono :: seconds(*last));
}

template <system_config System, global_config Config> template <class Self>
inline auto superblock <System, Config> :: get_lpf_ino(this Self&& self) noexcept
requires(superblock <System, Config> :: has_lpf_ino())
{
 return std :: forward<Self>(self).read(get_lpf_ino_indices());
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

template <system_config System, global_config Config>
template <class Self, std :: size_t ... Indices>
inline auto superblock <System, Config> :: read(this Self&& self, std :: index_sequence<Indices...>) noexcept
{
 return compose<Indices...>(std :: forward<Self>(self).block);
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_inodes_count_indices() noexcept
requires(superblock <System, Config> :: has_inodes_count())
{
 return std :: index_sequence<0x003zu, 0x002zu, 0x001zu, 0x000zu>();
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_blocks_count_indices() noexcept
requires(superblock <System, Config> :: has_blocks_count())
{
 using enum system_config :: file_system_t;
 if constexpr ((System.file_system == ext4) && System.feature_compat_64bit)
 {
  return std :: index_sequence<0x153zu, 0x152zu, 0x151zu, 0x150zu, 0x007zu, 0x006zu, 0x005zu, 0x004zu>();
 }
 else
 {
  return std :: index_sequence<0x007zu, 0x006zu, 0x005zu, 0x004zu>();
 }
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_reserved_blocks_count_indices() noexcept
requires(superblock <System, Config> :: has_reserved_blocks_count())
{
 using enum system_config :: file_system_t;
 if constexpr ((System.file_system == ext4) && System.feature_compat_64bit)
 {
  return std :: index_sequence<0x157zu, 0x156zu, 0x155zu, 0x154zu, 0x00Bzu, 0x00Azu, 0x009zu, 0x008zu>();
 }
 else
 {
  return std :: index_sequence<0x00Bzu, 0x00Azu, 0x009zu, 0x008zu>();
 }
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_free_blocks_count_indices() noexcept
requires(superblock <System, Config> :: has_free_blocks_count())
{
 using enum system_config :: file_system_t;
 if constexpr ((System.file_system == ext4) && System.feature_compat_64bit)
 {
  return std :: index_sequence<0x15Bzu, 0x15Azu, 0x159zu, 0x158zu, 0x00Fzu, 0x00Ezu, 0x00Dzu, 0x00Czu>();
 }
 else if constexpr (System.file_system == ext)
 { //Ext1 has same location as other exts.
  return std :: index_sequence<0x00Fzu, 0x00Ezu, 0x00Dzu, 0x00Czu>();
 }
 else
 {
  return std :: index_sequence<0x00Fzu, 0x00Ezu, 0x00Dzu, 0x00Czu>();
 }
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_free_inodes_count_indices() noexcept
requires(superblock <System, Config> :: has_free_inodes_count())
{
 if constexpr (System.file_system == system_config :: file_system_t :: ext)
 {
  return std :: index_sequence<0x017zu, 0x016zu, 0x015zu, 0x014zu>();
 }
 else
 {
  return std :: index_sequence<0x013zu, 0x012zu, 0x011zu, 0x010zu>();
 }
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_mount_time_indices() noexcept
requires(superblock <System, Config> :: has_mount_time())
{
 return std :: index_sequence<0x02Fzu, 0x02Ezu, 0x02Dzu, 0x02Czu>();
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_write_time_indices() noexcept
requires(superblock <System, Config> :: has_write_time())
{
 return std :: index_sequence<0x033zu, 0x032zu, 0x031zu, 0x030zu>();
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_magic_indices() noexcept
requires(superblock <System, Config> :: has_magic())
{
 return std :: index_sequence<0x039zu, 0x038zu>();
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_last_check_indices() noexcept
requires(superblock <System, Config> :: has_last_check())
{
 return std :: index_sequence<0x043zu, 0x042zu, 0x041zu, 0x040zu>();
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_creator_os_indices() noexcept
requires(superblock <System, Config> :: has_creator_os())
{
 return std :: index_sequence<0x04Bzu, 0x04Azu, 0x049zu, 0x048zu>();
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_rev_level_indices() noexcept
requires(superblock <System, Config> :: has_rev_level())
{
 return std :: index_sequence<0x04Fzu, 0x04Ezu, 0x04Dzu, 0x04Czu>();
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_mkfs_time_indices() noexcept
requires(superblock <System, Config> :: has_mkfs_time())
{
 return std :: index_sequence<0x10Bzu, 0x10Azu, 0x109zu, 0x108zu>();
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_first_error_time_indices() noexcept
requires(superblock <System, Config> :: has_first_error_time())
{
 return std :: index_sequence<0x19Bzu, 0x19Azu, 0x199zu, 0x198zu>();
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_last_error_time_indices() noexcept
requires(superblock <System, Config> :: has_last_error_time())
{
 return std :: index_sequence<0x1CFzu, 0x1CEzu, 0x1CDzu, 0x1CCzu>();
}

template <system_config System, global_config Config>
constexpr inline auto superblock <System, Config> :: get_lpf_ino_indices() noexcept
requires(superblock <System, Config> :: has_lpf_ino())
{
 return std :: index_sequence<0x26Bzu, 0x26Azu, 0x269zu, 0x268zu>();
}
