// SPDX-FileCopyrightText: 2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0

#include <stl/format.hpp>


struct Foo
  {
  int bar;
  };

template<>
struct std::formatter<Foo> : std::formatter<std::string>
  {
  auto format(Foo const & foo, auto & ctx) const
    {
    return std::formatter<std::string>::format(std::format("Foo{{bar: {}}}", foo.bar), ctx);
    }
  };
static_assert( stl::ext::valid_formatter<std::formatter<Foo>,Foo>);

struct Bar
  {
  double bar;
  };
template<>
struct std::formatter<Bar> : std::formatter<std::string>
  {
  auto format(Bar const & foo, auto & ctx) const
    {
    return std::formatter<std::string>::format(std::format("Bar{{bar: {}}}", foo.bar), ctx);
    }
  };

struct Baz
  {
  int bar;
  };

template<>
struct std::formatter<Baz> : std::formatter<std::string>
  {
  auto format(Baz const & foo, auto & ctx)
    {
    return std::formatter<std::string>::format(std::format("Foo{{bar: {}}}", foo.bar), ctx);
    }
  };
static_assert( !stl::ext::valid_formatter<std::formatter<Baz>,Baz>);
struct Qux
  {
  int bar;
  };
template<>
struct std::formatter<Qux> : std::formatter<std::string>
  {
  auto format(Baz const & foo, auto & ctx) const
    {
    return std::formatter<std::string>::format(std::format("Foo{{bar: {}}}", foo.bar), ctx);
    }
  };
static_assert( !stl::ext::valid_formatter<std::formatter<Qux>,Qux>);

int main() 
{
  Foo const foo{42};
  Bar const bar{42};
  (void)stl::format("{}", foo);
  (void)std::format("{}", bar); // for -ftime-trace
}
