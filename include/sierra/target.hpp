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

#ifndef SRR_TARGET_HPP
#define SRR_TARGET_HPP

#define SRR_TARGET_UNKNOWN

#ifdef _WIN32
    #undef SRR_TARGET_UNKNOWN
    #define SRR_TARGET_WINDOWS
    #error "Windows is not supported!"
#endif // _WIN32

#ifdef __linux__
    #undef SRR_TARGET_UNKNOWN
    #define SRR_TARGET_UNIX
    #define SRR_TARGET_LINUX
    #error "Linux is not supported!"
#endif // __linux__

#ifdef __APPLE__
    #undef SRR_TARGET_UNKNOWN
    #define SRR_TARGET_UNIX
    #define SRR_TARGET_APPLE
#endif // __APPLE__

#ifdef SRR_TARGET_UNKNOWN
    #error "Unknown target is not supported!"
#endif // SRR_TARGET_UNKNOWN

#ifdef SRR_TARGET_UNIX

    #include "sierra/prims.hpp"

    #include <unistd.h>

inline namespace srr {

using Fd             = i32;

constexpr Fd STD_IN  = STDIN_FILENO;
constexpr Fd STD_OUT = STDOUT_FILENO;
constexpr Fd STD_ERR = STDERR_FILENO;

} // namespace srr

#endif // SRR_TARGET_UNIX

#endif // SRR_TARGET_HPP
