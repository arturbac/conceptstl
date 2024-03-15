// SPDX-FileCopyrightText: 2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0

#include <stl/format.hpp>
#include <iostream>

struct Foo
  {
  int bar;
  };

template<>
struct std::formatter<Foo> : std::formatter<std::string>
  {
  auto format(Foo const & foo, format_context & ctx) -> typename format_context::iterator
    {
    return std::formatter<std::string>::format(std::format("Foo{{bar: {}}}", foo.bar), ctx);
    }
  };

int main() 
{
  Foo foo{42};
  std::cout << std::format("{}", foo) << std::endl;
}


