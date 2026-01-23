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

#ifndef SRR_UTILS_CONSTEVAL_HPP
#define SRR_UTILS_CONSTEVAL_HPP

#include "sierra/prims.hpp"

#include <utility>

inline namespace srr {
namespace utils {

template<usize N, typename F, usize... I>
static consteval void callEachIndex(
    // NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
    F                                        &&func,
    [[maybe_unused]] std::index_sequence<I...> seq) noexcept {
    (func.template operator()<I>(), ...);
}

template<usize N, typename F>
consteval void forEachIndex(F &&func) noexcept {
    callEachIndex<N>(std::forward<F>(func), std::make_index_sequence<N>{});
}

template<usize N, typename F, usize... I>
static consteval void callEachPair(
    // NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
    F                                        &&func,
    [[maybe_unused]] std::index_sequence<I...> seq) noexcept {
    (
        [&] {
            forEachIndex<N>([&]<usize J> {
                if constexpr (I < J) func.template operator()<I, J>();
            });
        }(),
        ...);
}

template<usize N, typename F>
consteval void forEachPair(F &&func) noexcept {
    callEachPair<N>(std::forward<F>(func), std::make_index_sequence<N>{});
}

template<usize N, typename F>
// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
consteval void forEachAdj(F &&func) noexcept {
    if constexpr (N >= 2) {
        forEachIndex<N - 1>(
            [&]<usize I> { func.template operator()<I, I + 1>(); });
    }
}

} // namespace utils
} // namespace srr

#endif // SRR_UTILS_CONSTEVAL_HPP
