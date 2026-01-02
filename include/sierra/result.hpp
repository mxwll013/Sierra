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

#ifndef SRR_RESULT_HPP
#define SRR_RESULT_HPP

#include "sierra/error.hpp"
#include "sierra/memory.hpp"

#include <string_view>

inline namespace srr {

template<typename T>
concept ResultValue =
    SafeDestructible<T> && SafeMovePolicy<T> && SafeCopyPolicy<T>;

template<ResultValue T>
class Result;

template<ResultValue T>
class [[nodiscard]] Result {
public:
    using ValueType = T;

    [[nodiscard]] constexpr Result(Err err) noexcept;

    [[nodiscard]] constexpr Result(T &&value) noexcept;

    [[nodiscard]] constexpr Result(const T &value) noexcept
        requires SafeCopyable<T>;

    [[nodiscard]] constexpr Result(Result &&result) noexcept;
    [[nodiscard]] constexpr Result(const Result &result) noexcept
        requires SafeCopyable<T>;

    Result &operator=(Result &&result)      = delete;
    Result &operator=(const Result &result) = delete;

    constexpr ~Result() noexcept;

    [[nodiscard]] constexpr bool             ok() const noexcept;
    [[nodiscard]] constexpr bool             bad() const noexcept;

    [[nodiscard]] constexpr Err              err() const noexcept;

    [[nodiscard]] constexpr T               &value()               &noexcept;
    [[nodiscard]] constexpr const T         &value() const         &noexcept;

    [[nodiscard]] constexpr T              &&value()              &&noexcept;

    [[nodiscard]] constexpr std::string_view msg() const noexcept;

private:
    union Data {
        T   value;
        Err err;
    } data_;

    bool ok_;
};

template<ResultValue T>
constexpr Result<T>::Result(Err err) noexcept : ok_{ false } {
    new (&data_.err) Err{ err };
}

template<ResultValue T>
constexpr Result<T>::Result(T &&value) noexcept : ok_{ true } {
    new (&data_.value) T{ std::move(value) };
}

template<ResultValue T>
constexpr Result<T>::Result(const T &value) noexcept
    requires SafeCopyable<T>
    : ok_{ true } {
    new (&data_.value) T{ value };
}

template<ResultValue T>
constexpr Result<T>::Result(Result &&result) noexcept : ok_{ result.ok_ } {
    if (ok_)
        new (&data_.value) T{ std::move(result.data_.value) };
    else
        new (&data_.err) Err{ result.data_.err };
}

template<ResultValue T>
constexpr Result<T>::Result(const Result &result) noexcept
    requires SafeCopyable<T>
    : ok_{ result.ok_ } {
    if (ok_)
        new (&data_.value) T{ result.data_.value };
    else
        new (&data_.err) Err{ result.data_.err };
}

template<ResultValue T>
constexpr Result<T>::~Result() noexcept {
    if (ok_) data_.value.~T();
}

template<ResultValue T>
constexpr bool Result<T>::ok() const noexcept {
    return ok_;
}

template<ResultValue T>
constexpr bool Result<T>::bad() const noexcept {
    return !ok_;
}

template<ResultValue T>
constexpr Err Result<T>::err() const noexcept {
    return data_.err;
}

template<ResultValue T>
constexpr T &Result<T>::value() & noexcept {
    return data_.value;
}

template<ResultValue T>
constexpr const T &Result<T>::value() const & noexcept {
    return data_.value;
}

template<ResultValue T>
constexpr T &&Result<T>::value() && noexcept {
    return std::move(data_.value);
}

template<ResultValue T>
constexpr std::string_view Result<T>::msg() const noexcept {
    return lookup(data_.err);
}

} // namespace srr

#endif // SRR_RESULT_HPP
