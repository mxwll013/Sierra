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

#ifndef SRR_UTILS_MEMORY_HPP
#define SRR_UTILS_MEMORY_HPP

#include <type_traits>

inline namespace srr {
namespace utils {

template<typename T>
concept Moveable = std::is_move_constructible_v<T>;

template<typename T>
concept Copyable = std::is_copy_constructible_v<T>;

template<typename T>
concept SafeDestructible = std::is_nothrow_destructible_v<T>;

template<typename T>
concept SafeMoveable = std::is_nothrow_move_constructible_v<T>;

template<typename T>
concept SafeCopyable = std::is_nothrow_copy_constructible_v<T>;

template<typename T>
concept SafeMovePolicy = Moveable<T> && SafeMoveable<T>;

template<typename T>
concept SafeCopyPolicy = !Copyable<T> || SafeCopyable<T>;

} // namespace utils
} // namespace srr

#endif // SRR_UTILS_MEMORY_HPP
