// SPDX-FileCopyrightText: 2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0

#pragma once
#include <format>

namespace stl
  {
  using std::formatter;
  using std::basic_format_parse_context;
  using std::basic_format_context;
  using std::back_insert_iterator;
  using std::basic_string;
  using std::same_as;
  using std::string;
  using std::wstring;
  using std::vformat;
  using std::make_format_args;
  using std::forward;
  using std::make_wformat_args;
  
namespace concepts
  {
  template<class T, class CharT>
  concept formattable = requires(
    T t,
    basic_format_parse_context<CharT> parse_ctx,
    basic_format_context<back_insert_iterator<basic_string<CharT>>, CharT> & format_ctx
  )
  // clang-format off
    {
      { formatter<T, CharT>{} } -> same_as<formatter<T, CharT>>;
      { formatter<T, CharT>{}.parse(parse_ctx) } -> same_as<typename formatter<T, CharT>::iterator>;
      formatter<T, CharT>{}.format(t, format_ctx);
    };
  // clang-format on
  }  // namespace concepts

template<concepts::formattable<char>... Args>
string format(basic_string<char> const & fmt, Args &&... args)
  {
  return vformat(fmt, make_format_args(forward<Args>(args)...));
  }

template<concepts::formattable<wchar_t>... Args>
wstring format(basic_string<wchar_t> const & fmt, Args &&... args)
  {
  return vformat(fmt, make_wformat_args(forward<Args>(args)...));
  }
  }  // namespace stl
