#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <utility>

template <std :: size_t N> class content : public std :: enable_shared_from_this<content<N> >
{
 public:
 template <class Stream> [[nodiscard]] static std :: shared_ptr<content> create(Stream&& s) noexcept;
 template <class Self> std :: shared_ptr<content> share(this Self&& self) noexcept;
 template <class Self> auto&& getData(this Self&& self) noexcept;
 private:
 using byte_type = std :: uint8_t;
 std :: array<byte_type, N> data;
 content() noexcept = default;
};

template <std :: size_t N>
template <class Stream>
inline std :: shared_ptr<content<N> > content <N> :: create(Stream&& s) noexcept
{
 try
 {
  auto result = std :: shared_ptr<content<N> >(new content<N>());
  std :: copy_n(std :: istream_iterator<typename content <N> :: byte_type>(s), N, result->data.begin());
  return result;
 }
 catch(...){} //TODO: Add error logging
 return nullptr;
}

template <std :: size_t N>
template <class Self>
inline std :: shared_ptr<content<N> > content <N> :: share(this Self&& self) noexcept
{
 try
 {
  return std :: forward<Self>(self).shared_from_this();
 }
 catch(...){} //TODO: Add error logging
 return nullptr;
}

template <std :: size_t N>
template <class Self>
inline auto&& content <N> :: getData(this Self&& self) noexcept
{
 return std :: forward<Self>(self).data;
}
