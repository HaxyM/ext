#pragma once

struct system_config
{
 enum class file_system_t;
 enum class creator_os_t;
 enum class revision_t;
 file_system_t file_system;
 creator_os_t creator_os;
 revision_t revision;
 bool feature_compat_64bit;
 template <file_system_t> struct feature_compat_flags;
 constexpr static system_config getDefault() noexcept;
 private:
 enum class ext2_feature_compat_flags : std :: uint32_t;
 enum class ext3_feature_compat_flags : std :: uint32_t;
 enum class ext4_feature_compat_flags : std :: uint32_t;
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

enum class system_config :: ext2_feature_compat_flags : std :: uint32_t
{
 dir_prealloc = UINT32_C(0b000001),
 imagic_inodes = UINT32_C(0b000010),
 has_journal = UINT32_C(0b000100), //Marks at least ext3.
 ext_attr = UINT32_C(0b001000),
 resize_inode = UINT32_C(0b010000),
 dir_index = UINT32_C(0b100000)
};

enum class system_config :: ext3_feature_compat_flags : std :: uint32_t
{
};

enum class system_config :: ext4_feature_compat_flags : std :: uint32_t
{
 lazy_bg = UINT32_C(0b0001000000),
 exclude_inode = UINT32_C(0b0010000000),
 exclude_bitmap = UINT32_C(0b0100000000),
 sparse_super = UINT32_C(0b1000000000)
};

template <> struct system_config :: feature_compat_flags<system_config :: file_system_t :: ext>
{
};

template <> struct system_config :: feature_compat_flags<system_config :: file_system_t :: ext2>
{
 using enum system_config :: ext2_feature_compat_flags;
};

template <> struct system_config :: feature_compat_flags<system_config :: file_system_t :: ext3>
{
 using enum system_config :: ext2_feature_compat_flags;
 using enum system_config :: ext3_feature_compat_flags;
};

template <> struct system_config :: feature_compat_flags<system_config :: file_system_t :: ext4>
{
 using enum system_config :: ext2_feature_compat_flags;
 using enum system_config :: ext3_feature_compat_flags;
 using enum system_config :: ext4_feature_compat_flags;
};

constexpr inline system_config system_config :: getDefault() noexcept
{
 return
 {
  .file_system = file_system_t :: ext,
  .creator_os = creator_os_t :: linux,
  .revision = revision_t :: good_old_rev,
  .feature_compat_64bit = false
 };
}
