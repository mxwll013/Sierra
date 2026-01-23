/*
 * -----------------------------------------------------------------------------
 * Echo Engine Project - Apache 2.0 License
 *
 * Part of the Echo Engine Project, a modular C++ engine designed for
 * flexibility, maintainability, and scalability.
 *
 * To ensure consistency across all modules, the Sierra Style Guide establishes
 * comprehensive coding conventions, formatting rules, and tooling
 * configurations. This includes rules for C++ formatting, language server
 * behavior, static analysis, and guidelines for naming, structure and module
 * interaction.
 *
 * All contributors are expected to adhere to the Sierra Style Guide,
 * ensuring that code across the entire ecosystem is readable, maintainable,
 * and compatible with the project’s tools and pipelines.
 *
 * By following these conventions, developers help maintain a cohesive
 * and professional codebase across the Echo Engine Project.
 *
 * - https://echoengine.org
 * - https://docs.echoengine.org
 * - https://style.echoengine.org
 *
 * Module : Sierra - Shared
 * Copyright (c) 2026 Echo Engine Project contributors
 * -----------------------------------------------------------------------------
 */

#ifndef SRR_UTILS_FLOAT_HPP
#define SRR_UTILS_FLOAT_HPP

#include "sierra/prims.hpp"
#include "sierra/utils/char.hpp"

#include <charconv>
#include <string_view>
#include <system_error>

inline namespace srr {
namespace utils {

[[nodiscard]] constexpr f32 readF32(std::string_view view) noexcept;
[[nodiscard]] constexpr f64 readF64(std::string_view view) noexcept;

template<typename T>
[[nodiscard]] static constexpr T readFast(const char *ptr, usize len) noexcept;
template<typename T>
[[nodiscard]] static constexpr T readFull(const char *ptr, usize len) noexcept;
template<typename T>
[[nodiscard]] static constexpr T read(std::string_view view) noexcept;

template<typename T>
static constexpr T readFast(const char *ptr, usize len) noexcept {
    u64 val{ 0 };
    for (usize i = 0; i < len; ++i)
        val = val * BASE_DECIMAL + static_cast<u64>(ptr[i] - NUM_0);

    return static_cast<T>(val);
}

template<typename T>
static constexpr T readFull(const char *ptr, usize len) noexcept {
    T                            val{};
    const char                  *end = ptr + len;

    const std::from_chars_result res = std::from_chars(ptr, end, val);

    if (res.ec == std::errc{} && res.ptr == end) return val;

    return limit<T, LimitType::QUIET_NAN>();
}

template<typename T>
static constexpr T read(std::string_view view) noexcept {
    const char *ptr = view.data();
    const usize len = view.length();

    for (usize i = 0; i < len; ++i) {
        switch (ptr[i]) {
        case MINUS: [[fallthrough]];
        case UP_E : [[fallthrough]];
        case PLUS : [[fallthrough]];
        case DOT  : [[fallthrough]];
        case E    : return readFull<T>(ptr, len);
        default   : continue;
        }
    }

    return readFast<T>(ptr, len);
}

constexpr f32 readF32(std::string_view view) noexcept {
    return read<f32>(view);
}

constexpr f64 readF64(std::string_view view) noexcept {
    return read<f64>(view);
}

} // namespace utils
} // namespace srr

#endif // SRR_UTILS_FLOAT_HPP
