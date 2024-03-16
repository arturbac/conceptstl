// SPDX-FileCopyrightText: 2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0

#include <stl/vector.hpp>

struct Foo
  {
  ~Foo() = default;
  };

int main()
  {
  stl::vector<Foo> t1;
  (void)t1[0];
  std::vector<Foo> t2;  // for -ftime-trace
  (void)t2[0];
  }

