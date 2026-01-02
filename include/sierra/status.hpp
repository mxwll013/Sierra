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

#ifndef SRR_STATUS_HPP
#define SRR_STATUS_HPP

#include "sierra/error.hpp"

#include <string_view>

inline namespace srr {

class Status;

class [[nodiscard]] Status {
public:
    [[nodiscard]] constexpr Status() noexcept;
    [[nodiscard]] constexpr Status(Err err) noexcept;

    [[nodiscard]] constexpr bool             ok() const noexcept;
    [[nodiscard]] constexpr bool             bad() const noexcept;

    [[nodiscard]] constexpr Err              err() const noexcept;
    [[nodiscard]] constexpr std::string_view msg() const noexcept;

private:
    Err err_;
};

constexpr Status::Status() noexcept : err_{ Err::OK } {}

constexpr Status::Status(Err err) noexcept : err_{ err } {}

constexpr bool Status::ok() const noexcept { return err_ == Err::OK; }

constexpr bool Status::bad() const noexcept { return err_ != Err::OK; }

constexpr Err  Status::err() const noexcept { return err_; }

constexpr std::string_view Status::msg() const noexcept { return lookup(err_); }

} // namespace srr

#endif // SRR_STATUS_HPP
