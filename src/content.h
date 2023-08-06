#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <utility>

#include "global_config.h"
#include "logger.h"

template <std :: size_t N, global_config Config> class content : public std :: enable_shared_from_this<content<N, Config> >
{
 public:
 using content_type = content<N, Config>;
 [[nodiscard]] static std :: shared_ptr<content> create() noexcept;
 template <class Stream> [[nodiscard]] static std :: shared_ptr<content> create(Stream&& s) noexcept;
 template <class Self> std :: shared_ptr<content> share(this Self&& self) noexcept;
 template <class Self> auto&& getData(this Self&& self) noexcept;
 private:
 using byte_type = std :: uint8_t;
 std :: array<byte_type, N> data;
 content() noexcept = default;
};

template <std :: size_t N, global_config Config>
inline std :: shared_ptr<content<N, Config> > content <N, Config> :: create() noexcept
{
 try
 {//TODO: Find way to use make_shared here.
  return static_cast<std :: shared_ptr<content<N, Config> > >(new content<N, Config>());
 }
 catch (const std :: exception& e)
 {
  logger<Config, log_level :: error> l; l.log("Creation failed ", e.what(), '.');
 }
 catch (...)
 {
  logger<Config, log_level :: error> l; l.log("Creation failed with exception.");
 }
 return nullptr;
}

template <std :: size_t N, global_config Config>
template <class Stream>
inline std :: shared_ptr<content<N, Config> > content <N, Config> :: create(Stream&& s) noexcept
{
 try
 {//TODO: Find way to use make_shared here.
  auto result = std :: shared_ptr<content<N, Config> >(new content<N, Config>());
  std :: copy_n(std :: istream_iterator<typename content <N, Config> :: byte_type>(s), N, result->data.begin());
  return result;
 }
 catch (const std :: exception& e)
 {
  logger<Config, log_level :: error> l; l.log("Creation failed ", e.what(), '.');
 }
 catch (...)
 {
  logger<Config, log_level :: error> l; l.log("Creation failed with exception.");
 }
 return nullptr;
}

template <std :: size_t N, global_config Config>
template <class Self>
inline std :: shared_ptr<content<N, Config> > content <N, Config> :: share(this Self&& self) noexcept
{
 try
 {
  return std :: forward<Self>(self).shared_from_this();
 }
 catch (const std :: exception& e)
 {
  logger<Config, log_level :: error> l; l.log("Sharing failed ", e.what(), '.');
 }
 catch (...)
 {
  logger<Config, log_level :: error> l; l.log("Sharing failed with exception.");
 }
 return nullptr;
}

template <std :: size_t N, gloabl_config Config>
template <class Self>
inline auto&& content <N, Config> :: getData(this Self&& self) noexcept
{
 return std :: forward<Self>(self).data;
}
