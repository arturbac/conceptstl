// SPDX-FileCopyrightText: 2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0

#include <stl/vector.hpp>

struct Foo
  {
  ~Foo() = delete;
  };

int main()
  {
  stl::vector<Foo> t2;
  }
