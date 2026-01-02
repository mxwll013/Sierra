// --------------------------------------------------------------------------------
// Echo Engine Project - Apache 2.0 License

// Part of the Echo Engine Project, a modular C++ engine designed for
// flexibility, maintainability, and scalability.

// To ensure consistency across all modules, the Sierra Style Guide establishes
// comprehensive coding conventions, formatting rules, and tooling
// configurations. This includes rules for C++ formatting, language server
// behavior, static analysis, and guidelines for naming, structure and module
// interaction.

// All contributors are expected to adhere to the Sierra Style Guide,
// ensuring that code across the entire ecosystem is readable, maintainable,
// and compatible with the project’s tools and pipelines.

// By following these conventions, developers help maintain a cohesive
// and professional codebase across the Echo Engine Project.

// - https://echoengine.org
// - https://docs.echoengine.org
// - https://style.echoengine.org

// Module : Sierra - Shared
// Copyright (c) 2025 Echo Engine Project contributors
// --------------------------------------------------------------------------------

#ifndef SRR_PRIMITIVES_HPP
#define SRR_PRIMITIVES_HPP

#include <cstddef>
#include <cstdint>
#include <limits>

inline namespace srr {

// Primitive aliases should be lowercase
// NOLINTBEGIN(readability-identifier-naming)

using i8                  = std::int8_t;
using i16                 = std::int16_t;
using i32                 = std::int32_t;
using i64                 = std::int64_t;

using u8                  = std::uint8_t;
using u16                 = std::uint16_t;
using u32                 = std::uint32_t;
using u64                 = std::uint64_t;

using usize               = std::size_t;

using f32                 = float;
using f64                 = double;

// NOLINTEND(readability-identifier-naming)

constexpr i8    I8_MIN    = INT8_MIN;
constexpr i16   I16_MIN   = INT16_MIN;
constexpr i32   I32_MIN   = INT32_MIN;
constexpr i64   I64_MIN   = INT64_MIN;

constexpr i8    I8_MAX    = INT8_MAX;
constexpr i16   I16_MAX   = INT16_MAX;
constexpr i32   I32_MAX   = INT32_MAX;
constexpr i64   I64_MAX   = INT64_MAX;

constexpr u8    U8_MAX    = UINT8_MAX;
constexpr u16   U16_MAX   = UINT16_MAX;
constexpr u32   U32_MAX   = UINT32_MAX;
constexpr u64   U64_MAX   = UINT64_MAX;
constexpr usize USIZE_MAX = SIZE_MAX;

constexpr f32   F32_MIN   = std::numeric_limits<f32>::min();
constexpr f64   F64_MIN   = std::numeric_limits<f64>::min();

constexpr f32   F32_MAX   = std::numeric_limits<f32>::max();
constexpr f64   F64_MAX   = std::numeric_limits<f64>::max();

} // namespace srr

#endif // SRR_PRIMITIVES_HPP
