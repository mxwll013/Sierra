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

#ifndef SRR_UTILS_SYS_HPP
#define SRR_UTILS_SYS_HPP

#include "sierra/prims.hpp"
#include "sierra/target.hpp"

inline namespace srr {
namespace utils {

enum class Sink : u8 {
    CONSOLE_IN,
    CONSOLE_OUT,
    CONSOLE_ERR,
};

struct [[nodiscard]] Sys {
    template<Sink S>
    inline static void write(const char *buf, usize len) noexcept;
};

#ifdef SRR_TARGET_UNIX

    #include <unistd.h>

template<Sink S>
[[nodiscard]] consteval Fd fd() noexcept {
    switch (S) {
    case Sink::CONSOLE_IN : return STD_IN;
    case Sink::CONSOLE_OUT: return STD_OUT;
    case Sink::CONSOLE_ERR: return STD_ERR;
    }
}

template<Sink S>
inline void Sys::write(const char *buf, usize len) noexcept {
    const Fd dst = fd<S>();
    ::write(dst, buf, len);
}

#else  // SRR_TARGET_UNIX
    #error
#endif // SRR_TARGET_UNIX

} // namespace utils
} // namespace srr

#endif // SRR_UTILS_SYS_HPP
