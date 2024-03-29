#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

struct system_config
{
 enum class file_system_t;
 enum class creator_os_t;
 enum class revision_t;
 enum class feature_compat_t : std :: uint32_t;
 enum class feature_incompat_t : std :: uint32_t;
 enum class feature_ro_compat_t : std :: uint32_t;
 enum class compression_algorithm_t : std :: uint32_t;
 enum class encoding_t;
 enum class encoding_params_t : std :: uint16_t;
 file_system_t file_system;
 creator_os_t creator_os;
 revision_t revision;
 feature_compat_t feature_compat;
 feature_incompat_t feature_incompat;
 feature_ro_compat_t feature_ro_compat;
 compression_algorithm_t compression_algorithm;
 encoding_t encoding;
 encoding_params_t encoding_params;
 template <file_system_t> struct feature_compat_flags;
 template <file_system_t> struct feature_incompat_flags;
 template <file_system_t> struct feature_ro_compat_flags;
 enum class compression_algorithm_flags : std :: underlying_type_t<compression_algorithm_t>;
 template <encoding_t> struct encoding_params_flags;
 constexpr static system_config getDefault() noexcept;
 private:
 enum class ext2_feature_compat_flags : std :: underlying_type_t<feature_compat_t>;
 enum class ext3_feature_compat_flags : std :: underlying_type_t<feature_compat_t>;
 enum class ext4_feature_compat_flags : std :: underlying_type_t<feature_compat_t>;
 enum class ext2_feature_incompat_flags : std :: underlying_type_t<feature_incompat_t>;
 enum class ext3_feature_incompat_flags : std :: underlying_type_t<feature_incompat_t>;
 enum class ext4_feature_incompat_flags : std :: underlying_type_t<feature_incompat_t>;
 enum class ext2_feature_ro_compat_flags : std :: underlying_type_t<feature_ro_compat_t>;
 enum class ext3_feature_ro_compat_flags : std :: underlying_type_t<feature_ro_compat_t>;
 enum class ext4_feature_ro_compat_flags : std :: underlying_type_t<feature_ro_compat_t>;
 enum class ascii_encoding_params_flags : std :: underlying_type_t<encoding_params_t>;
 enum class utf8_12_1_encoding_params_flags : std :: underlying_type_t<encoding_params_t>;
 template <auto System, system_config :: ext2_feature_compat_flags Flag> friend constexpr bool is_flag_set() noexcept;
 template <auto System, system_config :: ext3_feature_compat_flags Flag> friend constexpr bool is_flag_set() noexcept;
 template <auto System, system_config :: ext4_feature_compat_flags Flag> friend constexpr bool is_flag_set() noexcept;
 template <auto System, system_config :: ext2_feature_incompat_flags Flag> friend constexpr bool is_flag_set() noexcept;
 template <auto System, system_config :: ext3_feature_incompat_flags Flag> friend constexpr bool is_flag_set() noexcept;
 template <auto System, system_config :: ext4_feature_incompat_flags Flag> friend constexpr bool is_flag_set() noexcept;
 template <auto System, system_config :: ext2_feature_ro_compat_flags Flag> friend constexpr bool is_flag_set() noexcept;
 template <auto System, system_config :: ext3_feature_ro_compat_flags Flag> friend constexpr bool is_flag_set() noexcept;
 template <auto System, system_config :: ext4_feature_ro_compat_flags Flag> friend constexpr bool is_flag_set() noexcept;
 template <auto System, system_config :: compression_algorithm_flags Flag> friend constexpr bool is_flag_set() noexcept;
 template <auto System, system_config :: ascii_encoding_params_flags Flag> friend constexpr bool is_flag_set() noexcept;
 template <auto System, system_config :: utf8_12_1_encoding_params_flags Flag> friend constexpr bool is_flag_set() noexcept;
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

enum class system_config :: feature_compat_t : std :: uint32_t
{
 empty = UINT32_C(0),
 ext2_mask = UINT32_C(0b1'1111'1011),
 ext3_mask = UINT32_C(0b1'1111'1111),
 ext4_mask = UINT32_C(0b1'1111'1111'1111)
};

enum class system_config :: feature_incompat_t : std :: uint32_t
{
 empty = UINT32_C(0),
 ext2_mask = UINT32_C(0b1'0011),
 ext3_mask = UINT32_C(0b111'1111),
 ext4_mask = UINT32_C(0b11'1111'0111'1101'1111)
};

enum class system_config :: feature_ro_compat_t : std :: uint32_t
{
 empty = UINT32_C(0),
 ext2_mask = UINT32_C(0b111),
 ext3_mask = UINT32_C(0b111),
 ext4_mask = UINT32_C(0b1'1111'1111'1111'1111)
};

enum class system_config :: compression_algorithm_t : std :: uint32_t
{
 empty = UINT32_C(0),
 mask = UINT32_C(0b1'1111)
};

enum class system_config :: encoding_t
{
 ascii,
 utf8_12_1
};

enum class system_config :: encoding_params_t : std :: uint16_t
{
 empty = UINT16_C(0),
 ascii_mask = UINT16_C(0b0),
 utf8_12_1_mask = UINT16_C(0b1)
};

enum class system_config :: ext2_feature_compat_flags : std :: underlying_type_t<system_config :: feature_compat_t>
{
 dir_prealloc = UINT32_C(0b0'0000'0001),
 imagic_inodes = UINT32_C(0b0'0000'0010),
 ext_attr = UINT32_C(0b0'0000'1000),
 resize_inode = UINT32_C(0b0'0001'0000),
 dir_index = UINT32_C(0b0'0010'0000),
 lazy_bg = UINT32_C(0b0'0100'0000),
 exclude_inode = UINT32_C(0b0'1000'0000),
 exclude_bitmap = UINT32_C(0b1'0000'0000),
};

enum class system_config :: ext3_feature_compat_flags : std :: underlying_type_t<system_config :: feature_compat_t>
{
 has_journal = UINT32_C(0b100),
};

enum class system_config :: ext4_feature_compat_flags : std :: underlying_type_t<system_config :: feature_compat_t>
{
 sparse_super = UINT32_C(0b0'0010'0000'0000),
 fast_commit = UINT32_C(0b0'0100'0000'0000),
 stable_inodes = UINT32_C(0b0'1000'0000'0000),
 orphan_file = UINT32_C(0b1'0000'0000'0000)
};

enum class system_config :: ext2_feature_incompat_flags : std :: underlying_type_t<system_config :: feature_incompat_t>
{
 compresion = UINT32_C(0b0'0001),
 filetype = UINT32_C(0b0'0010),
 meta_bg = UINT32_C(0b1'0000)
};

enum class system_config :: ext3_feature_incompat_flags : std :: underlying_type_t<system_config :: feature_incompat_t>
{
 recover = UINT32_C(0b000'0100),
 journal_dev = UINT32_C(0b000'1000),
 extents = UINT32_C(0b100'0000),
};

enum class system_config :: ext4_feature_incompat_flags : std :: underlying_type_t<system_config :: feature_incompat_t>
{
 bits64 = UINT32_C(0b00'0000'0000'1000'0000),
 mmp = UINT32_C(0b00'0000'0001'0000'0000),
 flex_bg = UINT32_C(0b00'0000'0010'0000'0000),
 ea_inod = UINT32_C(0b00'0000'0100'0000'0000),
 dir_data = UINT32_C(0b00'0001'0000'0000'0000),
 csum_seed = UINT32_C(0b00'0010'1000'0000'0000),
 large_dir = UINT32_C(0b00'0100'0000'0000'0000),
 inline_data = UINT32_C(0b00'1000'0000'0000'0000),
 encrypt = UINT32_C(0b01'0000'0000'0000'0000),
 case_fold = UINT32_C(0b10'0000'0000'0000'0000)
};

enum class system_config :: ext2_feature_ro_compat_flags : std :: underlying_type_t<system_config :: feature_ro_compat_t>
{
 sparse_super = UINT32_C(0b001),
 large_file = UINT32_C(0b010),
 btree_dir = UINT32_C(0b100)
};

enum class system_config :: ext3_feature_ro_compat_flags : std :: underlying_type_t<system_config :: feature_ro_compat_t>
{
};

enum class system_config :: ext4_feature_ro_compat_flags : std :: underlying_type_t<system_config :: feature_ro_compat_t>
{
 huge_file = UINT32_C(0b0'0000'0000'0000'1000),
 gdt_csum = UINT32_C(0b0'0000'0000'00'0001'0000),
 dir_nlink = UINT32_C(0b0'0000'0000'0010'0000),
 extra_isize = UINT32_C(0b0'0000'0000'0100'0000),
 has_snapshot = UINT32_C(0b0'0000'0000'1000'0000),
 quota = UINT32_C(0b0'0000'0001'0000'0000),
 big_alloc = UINT32_C(0b0'0000'0010'0000'0000),
 metadata_csum = UINT32_C(0b0'0000'0100'0000'0000),
 replica = UINT32_C(0b0'0000'1000'0000'0000),
 readonly = UINT32_C(0b0'0001'0000'0000'0000),
 project = UINT32_C(0b0'0010'0000'0000'0000),
 shared_blocks = UINT32_C(0b0'0100'0000'0000'0000),
 verity = UINT32_C(0b0'1000'0000'0000'0000),
 orphan_present = UINT32_C(0b1'0000'0000'0000'0000)
};

enum class system_config :: ascii_encoding_params_flags : std :: underlying_type_t<system_config :: encoding_params_t>
{
};

enum class system_config :: utf8_12_1_encoding_params_flags : std :: underlying_type_t<system_config :: encoding_params_t>
{
 strict = UINT16_C(0b1)
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

template <> struct system_config :: feature_incompat_flags<system_config :: file_system_t :: ext2>
{
 using enum system_config :: ext2_feature_incompat_flags;
};

template <> struct system_config :: feature_incompat_flags<system_config :: file_system_t :: ext3>
{
 using enum system_config :: ext2_feature_incompat_flags;
 using enum system_config :: ext3_feature_incompat_flags;
};

template <> struct system_config :: feature_incompat_flags<system_config :: file_system_t :: ext4>
{
 using enum system_config :: ext2_feature_incompat_flags;
 using enum system_config :: ext3_feature_incompat_flags;
 using enum system_config :: ext4_feature_incompat_flags;
};

template <> struct system_config :: feature_ro_compat_flags<system_config :: file_system_t :: ext2>
{
 using enum system_config :: ext2_feature_ro_compat_flags;
};

template <> struct system_config :: feature_ro_compat_flags<system_config :: file_system_t :: ext3>
{
 using enum system_config :: ext2_feature_ro_compat_flags;
 using enum system_config :: ext3_feature_ro_compat_flags;
};

template <> struct system_config :: feature_ro_compat_flags<system_config :: file_system_t :: ext4>
{
 using enum system_config :: ext2_feature_ro_compat_flags;
 using enum system_config :: ext3_feature_ro_compat_flags;
 using enum system_config :: ext4_feature_ro_compat_flags;
};

template <> struct system_config :: encoding_params_flags<system_config :: encoding_t :: ascii>
{
 using enum system_config :: ascii_encoding_params_flags;
};

template <> struct system_config :: encoding_params_flags<system_config :: encoding_t :: utf8_12_1>
{
 using enum system_config :: utf8_12_1_encoding_params_flags;
};

enum class system_config :: compression_algorithm_flags : std :: underlying_type_t<system_config :: compression_algorithm_t>
{
 LZV1 = UINT32_C(0b0'0001),
 LZRW3A = UINT32_C(0b0'0010),
 GZIP = UINT32_C(0b0'0100),
 BZIP2 = UINT32_C(0b0'1000),
 LZO = UINT32_C(0b1'0000)
};

constexpr inline system_config system_config :: getDefault() noexcept
{
 return
 {
  .file_system = file_system_t :: ext4,
  .creator_os = creator_os_t :: linux,
  .revision = revision_t :: dynamic_rev,
  .feature_compat = feature_compat_t :: empty,
  .feature_incompat = feature_incompat_t :: empty,
  .feature_ro_compat = feature_ro_compat_t :: empty,
  .compression_algorithm = compression_algorithm_t :: empty,
  .encoding = encoding_t :: ascii,
  .encoding_params = encoding_params_t :: empty
 };
}

template <auto System, system_config :: ext2_feature_compat_flags Flag> constexpr bool is_flag_set() noexcept
{
 constexpr const static auto res = std :: to_underlying(System.feature_compat) & ~std :: to_underlying(Flag);
 return static_cast<system_config :: feature_compat_t>(res) != system_config :: feature_compat_t :: empty;
}

template <auto System, system_config :: ext3_feature_compat_flags Flag> constexpr bool is_flag_set() noexcept
{
 constexpr const static auto res = std :: to_underlying(System.feature_compat) & ~std :: to_underlying(Flag);
 return static_cast<system_config :: feature_compat_t>(res) != system_config :: feature_compat_t :: empty;
}

template <auto System, system_config :: ext4_feature_compat_flags Flag> constexpr bool is_flag_set() noexcept
{
 constexpr const static auto res = std :: to_underlying(System.feature_compat) & ~std :: to_underlying(Flag);
 return static_cast<system_config :: feature_compat_t>(res) != system_config :: feature_compat_t :: empty;
}

template <auto System, system_config :: ext2_feature_incompat_flags Flag> constexpr bool is_flag_set() noexcept
{
 constexpr const static auto res = std :: to_underlying(System.feature_incompat) & ~std :: to_underlying(Flag);
 return static_cast<system_config :: feature_incompat_t>(res) != system_config :: feature_incompat_t :: empty;
}

template <auto System, system_config :: ext3_feature_incompat_flags Flag> constexpr bool is_flag_set() noexcept
{
 constexpr const static auto res = std :: to_underlying(System.feature_incompat) & ~std :: to_underlying(Flag);
 return static_cast<system_config :: feature_incompat_t>(res) != system_config :: feature_incompat_t :: empty;
}

template <auto System, system_config :: ext4_feature_incompat_flags Flag> constexpr bool is_flag_set() noexcept
{
 constexpr const static auto res = std :: to_underlying(System.feature_incompat) & ~std :: to_underlying(Flag);
 return static_cast<system_config :: feature_incompat_t>(res) != system_config :: feature_incompat_t :: empty;
}

template <auto System, system_config :: ext2_feature_ro_compat_flags Flag> constexpr bool is_flag_set() noexcept
{
 constexpr const static auto res = std :: to_underlying(System.feature_ro_compat) & ~std :: to_underlying(Flag);
 return static_cast<system_config :: feature_ro_compat_t>(res) != system_config :: feature_ro_compat_t :: empty;
}

template <auto System, system_config :: ext3_feature_ro_compat_flags Flag> constexpr bool is_flag_set() noexcept
{
 constexpr const static auto res = std :: to_underlying(System.feature_ro_compat) & ~std :: to_underlying(Flag);
 return static_cast<system_config :: feature_ro_compat_t>(res) != system_config :: feature_ro_compat_t :: empty;
}

template <auto System, system_config :: ext4_feature_ro_compat_flags Flag> constexpr bool is_flag_set() noexcept
{
 constexpr const static auto res = std :: to_underlying(System.feature_ro_compat) & ~std :: to_underlying(Flag);
 return static_cast<system_config :: feature_ro_compat_t>(res) != system_config :: feature_ro_compat_t :: empty;
}

template <auto System, system_config :: compression_algorithm_flags Flag> constexpr bool is_flag_set() noexcept
{
 constexpr const static auto res = std :: to_underlying(System.compression_algorithm) & ~std :: to_underlying(Flag);
 return static_cast<system_config :: compression_algorithm_t>(res) != system_config :: compression_algorithm_t :: empty;
}

template <auto System, system_config :: ascii_encoding_params_flags Flag> constexpr bool is_flag_set() noexcept
{
 static_assert(System.encoding == system_config :: encoding_t :: ascii, "Ascii encodnig params requires ascii encoding");
 constexpr const static auto res = std :: to_underlying(System.encoding_params) & ~std :: to_underlying(Flag);
 return static_cast<system_config :: encoding_params_t>(res) != system_config :: encoding_params_t :: empty;
}

template <auto System, system_config :: utf8_12_1_encoding_params_flags Flag> constexpr bool is_flag_set() noexcept
{
 static_assert(System.encoding == system_config :: encoding_t :: utf8_12_1, "Utf8 12.1 encodnig params requires utf8 12.1 encoding");
 constexpr const static auto res = std :: to_underlying(System.encoding_params) & ~std :: to_underlying(Flag);
 return static_cast<system_config :: encoding_params_t>(res) != system_config :: encoding_params_t :: empty;
}
