// SPDX-FileCopyrightText: 2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <concepts>
#include <type_traits>
#include <iterator>
#include <memory>

namespace stl
  {
namespace concepts
  {
  using std::allocator_traits;
  using std::convertible_to;
  using std::declval;
  using std::ptrdiff_t;
  using std::same_as;
  using std::signed_integral;
  using std::unsigned_integral;

  template<typename Ptr, typename ValueType>
  concept pointer_like = requires(Ptr p, Ptr q, Ptr const cp, std::iter_difference_t<Ptr> n) {
    // clang-format off
    { *p } -> convertible_to<ValueType&>;
    { p + n } -> same_as<Ptr>;
    { p - n } -> same_as<Ptr>;
    { p - q } -> convertible_to<std::iter_difference_t<Ptr>>;
    { p == q } -> convertible_to<bool>;
    { p != q } -> convertible_to<bool>;
    { ++p } -> same_as<Ptr&>;
    { p++ } -> same_as<Ptr>;
    { --p } -> same_as<Ptr&>;
    { p-- } -> same_as<Ptr>;
    { *cp } -> convertible_to<const ValueType&>; // Dereferencing a const pointer
                                                             // clang-format on
  };

  template<typename VoidPtr>
  concept void_pointer = requires(VoidPtr vp, void * raw) {
    // clang-format off
    // Conversion from void* to VoidPtr
    { static_cast<VoidPtr>(raw) } -> same_as<VoidPtr>;
    // Conversion from VoidPtr to void*
    { static_cast<void*>(vp) } -> same_as<void*>;
      // clang-format on
  };

  template<typename ConstVoidPtr>
  concept const_void_pointer = requires(ConstVoidPtr cvp, void const * const_raw) {
    // clang-format off
    // Conversion from const void* to ConstVoidPtr
    { static_cast<ConstVoidPtr>(const_raw) } -> same_as<ConstVoidPtr>;
    // Conversion from ConstVoidPtr to const void*
    { static_cast<void const *>(cvp) } -> same_as<void const *>;
      // clang-format on
  };

  template<typename DiffType>
  concept difference_type_compatible = signed_integral<DiffType> && requires(DiffType d) {
    // clang-format off
    { d } -> convertible_to<ptrdiff_t>;
    { static_cast<DiffType>(0) } -> convertible_to<DiffType>;
      // clang-format on
  };

  template<typename SizeType>
  concept size_type_compatible = unsigned_integral<SizeType> && requires(SizeType s) {
    // clang-format off
    { s } -> convertible_to<size_t>;
    { static_cast<SizeType>(0) } -> convertible_to<SizeType>;
      // clang-format on
  };
  /**
   * @page allocator_requirements Allocator Requirements in C++ Standard Library
   *
   * @section sec_overview Overview
   * Allocators are objects that abstract memory allocation and deallocation in the C++ Standard Library containers.
   * They provide a layer of abstraction for memory management, allowing containers to allocate and deallocate memory
   * without being tied to specific allocation strategies. This documentation outlines the requirements that allocator
   * types must meet to be used with standard library containers.
   *
   * @section sec_requirements Requirements
   *
   * @subsection subsec_type_definitions Type Definitions
   * Allocators must provide certain type definitions to be used by containers for memory management and type
   * manipulation:
   * - `value_type`: The type of objects that can be allocated.
   * - `pointer`: A pointer type that can point to `value_type`.
   * - `const_pointer`: A pointer type that can point to const `value_type`.
   * - `void_pointer`: A generic pointer type (`void*`).
   * - `const_void_pointer`: A generic pointer type pointing to const (`const void*`).
   * - `difference_type`: A signed integer type capable of representing the difference between two pointers.
   * - `size_type`: An unsigned integer type capable of representing the size of the largest object that can be
   * allocated.
   *
   * @subsection subsec_member_functions Member Functions
   * Allocators must support the following operations for memory management:
   * - `allocate(size_type n)`: Allocates memory for `n` objects of type `value_type` without constructing them.
   * - `deallocate(pointer p, size_type n)`: Deallocates memory allocated for `n` objects starting from the address `p`.
   *
   * Optional operations (pre-C++20):
   * - `construct(pointer p, Args&&... args)`: Constructs an object of type `value_type` at the address `p`.
   * - `destroy(pointer p)`: Destroys the object of type `value_type` at the address `p`.
   *
   * @subsection subsec_traits_and_concepts Traits and Concepts
   * C++17 and later introduce `std::allocator_traits` to standardize interactions with allocator types, providing
   * default implementations for optional operations like `construct` and `destroy`, making custom allocator design
   * simpler.
   *
   * @section sec_cpp20_specifics C++20 and Allocator Concepts
   * C++20 introduces concepts that formalize requirements for allocator types, making it easier to define generic
   * components that work with allocators. These concepts are part of the standard library's effort to use concepts
   * and constraints for clearer, more reliable template code.
   *
   * @section sec_summary Summary
   * To be compatible with the C++ Standard Library containers, allocators must meet specific requirements regarding
   * type definitions and memory management operations. The introduction of `std::allocator_traits` and, in C++20,
   * allocator concepts, simplifies working with custom allocators while ensuring they meet these requirements.
   */
  template<typename Alloc, typename T>
  concept allocator
    = requires(Alloc a, allocator_traits<Alloc>::pointer p, typename allocator_traits<Alloc>::size_type n) {
        typename allocator_traits<Alloc>::value_type;
        typename allocator_traits<Alloc>::pointer;
        typename allocator_traits<Alloc>::const_pointer;
        typename allocator_traits<Alloc>::void_pointer;
        typename allocator_traits<Alloc>::const_void_pointer;
        typename allocator_traits<Alloc>::difference_type;
        typename allocator_traits<Alloc>::size_type;

        requires pointer_like<typename allocator_traits<Alloc>::pointer, typename Alloc::value_type>;
        requires pointer_like<typename allocator_traits<Alloc>::const_pointer, typename Alloc::value_type const>;
        requires difference_type_compatible<typename allocator_traits<Alloc>::difference_type>;
        requires size_type_compatible<typename allocator_traits<Alloc>::size_type>;

          // clang-format off
        { allocator_traits<Alloc>::allocate(a, n) }  -> same_as<typename allocator_traits<Alloc>::pointer>;
        { allocator_traits<Alloc>::deallocate(a, declval<typename allocator_traits<Alloc>::pointer>(), n) } -> same_as<void>;

          // clang-format on
          requires same_as<T, typename allocator_traits<Alloc>::value_type>;
      };

  }  // namespace concepts
  
  template<typename T>
  using allocator = std::allocator<T>;
  }  // namespace stl

