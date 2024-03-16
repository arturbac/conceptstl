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

int main() 
{
  Foo const foo{42};
  (void)stl::format("{}", foo);
  (void)std::format("{}", foo); // for -ftime-trace
}
