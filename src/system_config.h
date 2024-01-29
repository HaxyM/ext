#pragma once

struct system_config
{
 enum class file_system_t;
 enum class creator_os_t;
 enum class revision_t;
 file_system_t file_system;
 creator_os_t creator_os;
 revision_t revision;
 constexpr static system_config getDefault() noexcept;
};

enum class system_config :: file_system_t
{
 ext,
 ext2,
 ext3,
 ext4
};

enum class system_config :: creator_os_t
{
 linux,
 hurd,
 masix,
 free_bsd,
 lites
};

enum class system_config :: revision_t
{
 good_old_rev,
 dynamic_rev
};

constexpr inline system_config system_config :: getDefault() noexcept
{
 return
 {
  .file_system = file_system_t :: ext2,
  .creator_os = creator_os_t :: linux,
  .revision = revision_t :: good_old_rev
 };
}

