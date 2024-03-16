// SPDX-FileCopyrightText: 2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <stl/memory.hpp>
#include <vector>
#include <concepts>

namespace stl
  {
namespace concepts
  {
  using std::destructible;
  }  // namespace concepts

/**
 * @page std_vector_requirements std::vector<T> Requirements in C++23
 *
 * @section sec_overview Overview
 * As of C++23, for a type `T` to be used with `std::vector<T>`, it must satisfy certain requirements,
 * depending on the operations performed. These requirements ensure that `std::vector` can manage its
 * elements effectively, providing a robust and efficient container.
 *
 * @section sec_requirements Requirements
 *
 * @subsection subsec_default_constructible Default Constructible
 * - **Not Required**: A `std::vector` can be instantiated without requiring `T` to be Default Constructible.
 * However, certain operations like `resize(size_type count)` require `T` to be Default Constructible if no
 * initial value is provided.
 *
 * @subsection subsec_copy_operations Copy Constructible and Copy Assignable
 * - **Copy Operations**: Required if the vector is copied, where elements are copied individually.
 *
 * @subsection subsec_move_operations Move Constructible and Move Assignable
 * - **Move Operations**: Highly recommended for performance reasons, especially when the vector is resized
 * or reallocated. This allows transferring elements without copying, which is crucial for types that are
 * expensive to copy.
 *
 * @subsection subsec_destructible Destructible
 * - **Destruction**: Required for all types stored in a `std::vector` because the destruction of the vector
 * or its elements individually will invoke the destructor of `T`.
 *
 * @subsection subsec_other_considerations Other Considerations
 * - **Swappable**: For certain member functions like `swap()`, elements of `T` must be swappable.
 * - **Emplace Operations**: For operations like `emplace_back()` or `emplace()`, `T` must support construction
 * with the given arguments directly within the vector's storage.
 *
 * @section sec_cpp23_specifics C++23 Specifics
 * C++23 doesn't significantly change the fundamental requirements for a type `T` to be used with `std::vector`
 * compared to previous standards. However, it continues to emphasize efficiency improvements, especially with
 * move semantics, and introduces more algorithms and utilities that make use of concepts, potentially leading
 * to more idiomatic usage patterns that might indirectly affect type requirements in practical use
 * (e.g., through constraints imposed by algorithms used on vectors).
 *
 * @section sec_summary Summary
 * In summary, the type `T` used in a `std::vector<T>` should be Destructible, and depending on the vector's
 * usage, it might also need to be Default Constructible, Copy Constructible, Move Constructible, Copy Assignable,
 * Move Assignable, and Swappable. The more of these traits `T` supports, the more functionalities of `std::vector`
 * you can utilize efficiently.
 */
template<concepts::destructible T, concepts::allocator<T> Allocator = allocator<T>>
using vector = std::vector<T, Allocator>;
  }  // namespace stl
