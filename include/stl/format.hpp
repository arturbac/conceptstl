// SPDX-FileCopyrightText: 2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0

#pragma once
#include <format>

namespace stl
  {
using std::back_insert_iterator;
using std::basic_format_context;
using std::basic_format_parse_context;
using std::basic_string;
using std::format_string;
using std::formatter;

using std::make_format_args;
using std::make_wformat_args;

using std::same_as;
using std::string;
using std::vformat;
using std::wformat_string;
using std::wstring;

namespace concepts
  {
  using std::remove_const_t;
  using std::remove_cvref_t;
  using std::remove_reference_t;
  using std::semiregular;

  namespace detail
    {

    template<typename Iter, typename CharT>
    using fmt_context_iter = typename basic_format_context<Iter, CharT>::iterator;

    template<typename CharT>
    using iter_for = back_insert_iterator<basic_string<CharT>>;  // TODO it is unspecified how to deduce it ... ?

    template<class T, class Context, class Formatter = typename Context::template formatter_type<remove_const_t<T>>>
    concept formattable_with = semiregular<Formatter>
                               && requires(
                                 Formatter & f,
                                 Formatter const & cf,
                                 T && t,
                                 Context fc,
                                 basic_format_parse_context<typename Context::char_type> pc
                               )
    // clang-format off
    {
      { f.parse(pc) } -> same_as<typename decltype(pc)::iterator>;
      { cf.format(t, fc) } -> same_as<typename Context::iterator>;
    };
    // clang-format on

    template<typename T, typename CharT, typename Context = basic_format_context<iter_for<CharT>, CharT>>
    concept formattable_impl = formattable_with<T, Context>;
    }  // namespace detail

  template<class T, class CharT>
  concept formattable = detail::formattable_impl<remove_reference_t<T>, CharT>;

  }  // namespace concepts

template<concepts::formattable<char>... Args>
auto format(format_string<Args...> fmt, Args &&... args) -> string
  {
  return vformat(fmt.get(), make_format_args(std::forward<Args>(args)...));
  }

template<concepts::formattable<wchar_t>... Args>
auto format(wformat_string<Args...> fmt, Args &&... args) -> wstring
  {
  return vformat(fmt.get(), make_wformat_args(std::forward<Args>(args)...));
  }
  }  // namespace stl

// note: because 'cf.format(t, fc)' would be invalid: non-const lvalue reference to type
// 'basic_format_context<__format::_Sink_iter<char>, [...]>' cannot bind to a value of unrelated type
// 'basic_format_context<std::back_insert_iterator<std::basic_string<char>>, [...]>'
