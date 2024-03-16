// SPDX-FileCopyrightText: 2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0

#include <stl/vector.hpp>
#include <stl/format.hpp>
#include <stl/unordered_set.hpp>

#include <boost/ut.hpp>

namespace ut = boost::ut;

struct Foo{ int bar; };
template<>
struct std::formatter<Foo> : std::formatter<std::string>
  {
  auto format(Foo const & foo, auto & ctx) const
    {
    return std::formatter<std::string>::format(std::format("Foo{{bar: {}}}", foo.bar), ctx);
    }
  };
static ut::suite _ = [] 
  {
    using namespace ut;
    stl::vector<int> t;
    stl::vector<Foo> t2;
    int a=2;
    std::cout << stl::format("{}", a) << std::endl;
    Foo foo{2};
    std::cout << stl::format("{}", foo) << std::endl;
    
    "test_example"_test = [] {
        expect(true); // Replace with actual tests
    };
};

int main(){}
