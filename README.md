# conceptstl

## Overview

`conceptstl` is a modern interface C++20 and up library designed to address a significant gap (for me) in the Standard Template Library (STL) regarding type constraints and error messaging. Despite the introduction of concepts in C++20, aimed at improving compile-time type checking and providing clearer, more concise error messages, many types and functions within the STL remain unconstrained. This often results in complex and confusing error messages when these elements are used with incompatible arguments. The `conceptstl` project emerges from the disappointment with this oversight in both the C++20 and C++23 standards, with a commitment to exploring and improving upon the current limitations.

## Motivation

The primary motivation behind `conceptstl` is the persistent issue of "horrible error messages" that plague developers when they inadvertently use STL types and functions with invalid arguments for for example with ranges and format. Although C++20 brought forward the promise of concepts to mitigate these challenges by enforcing compile-time constraints, the reality has been less than satisfactory for me and it depends given stl library implementation. Many STL components still lack proper constraints, leading to a frustrating developer experience. This project aims to reimagine these components by applying concepts rigorously, adhering to the requirements described in the C++ standard, thereby producing more intelligible compile-time errors.

## Objectives

- **Enhance Compile-Time Error Messages:** Apply C++20 and C++23 concepts to STL types and functions by using aliases in namespace `stl`, aiming to generate clearer and more helpful error messages.
- **Evaluate Performance Impact:** Investigate how the introduction of constraints affects compile performance especially compile time template instantiation, providing insights and benchmarks.
- **Standard Compliance Exploration:** Through the lens of concepts, examine how closely the current implementations of STL types and functions align with their described requirements in the C++ standard, are there any logic holes ?.

## AI-Assisted Development

This project makes significant use of AI technologies to assist in generating code. The intricate nature of C++ concepts and the comprehensive coverage required for the STL means that manually coding each aspect is highly time-consuming. By leveraging AI, `conceptstl` aims to expedite the development process, focusing on the content's accuracy and validity. While AI helps in scaffolding and code generation, meticulous attention is dedicated to ensuring that the resulting implementations faithfully meet the complex requirements set forth by the C++ standards for concepts. This approach allows for a more efficient exploration of potential improvements to STL, making the development both innovative and grounded in solid engineering principles.


## Getting Started

To begin exploring `conceptstl`, clone the repository or use CPM and add target dependency on conceptstl::header_only.

## License

This project is licensed under the Boost Software License 1.0 (BSL 1.0). For more details, see the [LICENSE.md](LICENSE.md) file.


