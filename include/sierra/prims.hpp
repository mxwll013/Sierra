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

#ifndef SRR_PRIMS_HPP
#define SRR_PRIMS_HPP

#include <cstddef>
#include <cstdint>
#include <limits>

inline namespace srr {

// Primitive aliases should be lowercase
// NOLINTBEGIN(readability-identifier-naming)

using i8    = std::int8_t;
using i16   = std::int16_t;
using i32   = std::int32_t;
using i64   = std::int64_t;

using u8    = std::uint8_t;
using u16   = std::uint16_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;

using usize = std::size_t;

using f32   = float;
using f64   = double;

// NOLINTEND(readability-identifier-naming)

enum class LimitType : u8 {
    MIN,
    MAX,
    LOWEST,
    EPSILON,
    QUIET_NAN,
    INF,
};

template<typename T, LimitType U>
[[nodiscard]] static consteval T limit() noexcept {
    switch (U) {
    case LimitType::MIN      : return std::numeric_limits<T>::min();
    case LimitType::MAX      : return std::numeric_limits<T>::max();
    case LimitType::LOWEST   : return std::numeric_limits<T>::lowest();
    case LimitType::EPSILON  : return std::numeric_limits<T>::epsilon();
    case LimitType::QUIET_NAN: return std::numeric_limits<T>::quiet_NaN();
    case LimitType::INF      : return std::numeric_limits<T>::infinity();
    }
}

constexpr i8    I8_MIN           = limit<i8, LimitType::MIN>();
constexpr i16   I16_MIN          = limit<i16, LimitType::MIN>();
constexpr i32   I32_MIN          = limit<i32, LimitType::MIN>();
constexpr i64   I64_MIN          = limit<i64, LimitType::MIN>();

constexpr i8    I8_MAX           = limit<i8, LimitType::MAX>();
constexpr i16   I16_MAX          = limit<i16, LimitType::MAX>();
constexpr i32   I32_MAX          = limit<i32, LimitType::MAX>();
constexpr i64   I64_MAX          = limit<i64, LimitType::MAX>();

constexpr u8    U8_MAX           = limit<u8, LimitType::MAX>();
constexpr u16   U16_MAX          = limit<u16, LimitType::MAX>();
constexpr u32   U32_MAX          = limit<u32, LimitType::MAX>();
constexpr u64   U64_MAX          = limit<u64, LimitType::MAX>();
constexpr usize USIZE_MAX        = limit<usize, LimitType::MAX>();

constexpr f32   F32_LOWEST       = limit<f32, LimitType::LOWEST>();
constexpr f64   F64_LOWEST       = limit<f64, LimitType::LOWEST>();

constexpr f32   F32_MIN          = limit<f32, LimitType::MIN>();
constexpr f64   F64_MIN          = limit<f64, LimitType::MIN>();

constexpr f32   F32_MAX          = limit<f32, LimitType::MAX>();
constexpr f64   F64_MAX          = limit<f64, LimitType::MAX>();

constexpr f32   F32_EPSILON      = limit<f32, LimitType::EPSILON>();
constexpr f64   F64_EPSILON      = limit<f64, LimitType::EPSILON>();

constexpr f32   F32_NAN          = limit<f32, LimitType::QUIET_NAN>();
constexpr f64   F64_NAN          = limit<f64, LimitType::QUIET_NAN>();

constexpr f32   F32_INF          = limit<f32, LimitType::INF>();
constexpr f64   F64_INF          = limit<f64, LimitType::INF>();

constexpr u8    BASE_BINARY      = 8;
constexpr u8    BASE_OCTAL       = 8;
constexpr u8    BASE_DECIMAL     = 10;
constexpr u8    BASE_HEXADECIMAL = 16;

} // namespace srr

#endif // SRR_PRIMS_HPP
