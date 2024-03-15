// SPDX-FileCopyrightText: 2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0

#include <stl/vector.hpp>
#include <stl/format.hpp>

#include <boost/ut.hpp>

namespace ut = boost::ut;

struct Foo{};

static ut::suite _ = [] 
  {
    using namespace ut;
    stl::vector<int> t;
    stl::vector<Foo> t2;
    
    "test_example"_test = [] {
        expect(true); // Replace with actual tests
    };
};

int main(){}
