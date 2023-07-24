#pragma once

struct global_config
{
 bool debug;
 enum class verbocity_level;
 verbocity_level verbocity;
 constexpr static global_config getDefault() noexcept;
};

enum class global_config :: verbocity_level
{
 quiet,
 normal,
 verbose
};

constexpr inline global_config global_config :: getDefault() noexcept
{
 return {.debug = false, .verbocity = verbocity_level :: normal};
}

