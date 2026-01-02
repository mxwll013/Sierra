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

#ifndef SRR_ERROR_HPP
#define SRR_ERROR_HPP

#include "sierra/primitives.hpp"

#include <array>
#include <string_view>

inline namespace srr {

enum class Err : u8 {
    OK = 0,
    FAILURE,
    ERR_COUNT,
};

constexpr std::array<std::string_view, static_cast<usize>(Err::ERR_COUNT)>
    ERR_TABLE{
        "Ok",
        "Failure",
    };
static_assert(!ERR_TABLE.back().empty(), "Missing error message");

[[nodiscard]] constexpr std::string_view lookup(Err err) noexcept;

constexpr std::string_view               lookup(Err err) noexcept {
    const usize index = static_cast<usize>(err);
    return index < ERR_TABLE.size() ? ERR_TABLE.at(index) : "Unknown Error";
}

} // namespace srr

#endif // SRR_ERROR_HPP
