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

#ifndef SRR_RESULT_HPP
#define SRR_RESULT_HPP

#include "sierra/error.hpp"
#include "sierra/utils/memory.hpp"

#include <string>
#include <type_traits>

inline namespace srr {

template<typename T>
struct ResultStorage;

template<typename T>
struct ResultStorage {
    using Type = T;

    static void construct(Type &slot, T &&value) noexcept {
        new (&slot) T{ std::move(value) };
    }

    static void construct(Type &slot, const T &value) noexcept {
        new (&slot) T{ value };
    }

    static void destroy(Type &slot) noexcept { slot.~T(); }

    static T   &access(Type &slot) noexcept { return slot; }

    // access() is a non-owning view into Result storage
    // NOLINTNEXTLINE(bugprone-return-const-ref-from-parameter)
    static const T &access(const Type &slot) noexcept { return slot; }
};

template<typename T>
struct ResultStorage<T &> {
    using Type = std::add_pointer_t<T>;

    static void construct(Type &slot, T &value) noexcept { slot = &value; }

    static void destroy([[maybe_unused]] Type &slot) noexcept {}

    static T   &access(Type slot) noexcept { return *slot; }
};

template<typename T>
concept ResultStorable =
    utils::SafeDestructible<typename ResultStorage<T>::Type> &&
    utils::SafeMovePolicy<T> &&
    utils::SafeCopyPolicy<T>;

template<ResultStorable T>
class [[nodiscard]] Result {
public:
    using ValueType  = T;
    using Storage    = ResultStorage<T>;
    using StoredType = typename Storage::Type;

    [[nodiscard]] constexpr Result(Err err) noexcept;

    [[nodiscard]] constexpr Result(T &&value) noexcept;

    [[nodiscard]] constexpr Result(const T &value) noexcept
        requires utils::SafeCopyable<T>;

    [[nodiscard]] constexpr Result(Result &&result) noexcept;
    [[nodiscard]] constexpr Result(const Result &result) noexcept
        requires utils::SafeCopyable<T>;

    Result &operator=(Result &&result)      = delete;
    Result &operator=(const Result &result) = delete;

    constexpr ~Result() noexcept;

    [[nodiscard]] constexpr bool        ok() const noexcept;
    [[nodiscard]] constexpr bool        bad() const noexcept;

    [[nodiscard]] constexpr Err         err() const noexcept;

    [[nodiscard]] constexpr T          &val()          &noexcept;
    [[nodiscard]] constexpr const T    &val() const    &noexcept;
    [[nodiscard]] constexpr T         &&val()         &&noexcept;

    [[nodiscard]] constexpr std::string msg() const noexcept;

private:
    bool ok_;

    union Data {
        Err        err{};
        StoredType value;

        constexpr Data() noexcept {}

        Data(const Data &)            = delete;
        Data(Data &&)                 = delete;
        Data &operator=(const Data &) = delete;
        Data &operator=(Data &&)      = delete;

        ~Data() noexcept {}

    } data_;
};

// IMPL ---

template<ResultStorable T>
constexpr Result<T>::Result(Err err) noexcept : ok_{ false }, data_{} {
    new (&data_.err) Err{ err };
}

template<ResultStorable T>
constexpr Result<T>::Result(T &&value) noexcept : ok_{ true }, data_{} {
    Storage::construct(data_.value, std::move(value));
}

template<ResultStorable T>
constexpr Result<T>::Result(const T &value) noexcept
    requires utils::SafeCopyable<T>
    : ok_{ true }, data_{} {
    Storage::construct(data_.value, value);
}

template<ResultStorable T>
constexpr Result<T>::Result(Result &&result) noexcept :
    ok_{ result.ok_ },
    data_{} {
    if (ok_)
        Storage::construct(data_.value, std::move(result.data_.value));
    else
        new (&data_.err) Err{ result.data_.err };
}

template<ResultStorable T>
constexpr Result<T>::Result(const Result &result) noexcept
    requires utils::SafeCopyable<T>
    : ok_{ result.ok_ }, data_{} {
    if (ok_)
        Storage::construct(data_.value, result.data_.value);
    else
        new (&data_.err) Err{ result.data_.err };
}

template<ResultStorable T>
constexpr Result<T>::~Result() noexcept {
    if (ok_) Storage::destroy(data_.value);
}

template<ResultStorable T>
constexpr bool Result<T>::ok() const noexcept {
    return ok_;
}

template<ResultStorable T>
constexpr bool Result<T>::bad() const noexcept {
    return !ok_;
}

template<ResultStorable T>
constexpr Err Result<T>::err() const noexcept {
    return data_.err;
}

template<ResultStorable T>
constexpr T &Result<T>::val() & noexcept {
    return Storage::access(data_.value);
}

template<ResultStorable T>
constexpr const T &Result<T>::val() const & noexcept {
    return Storage::access(data_.value);
}

template<ResultStorable T>
constexpr T &&Result<T>::val() && noexcept {
    return std::move(Storage::access(data_.value));
}

template<ResultStorable T>
constexpr std::string Result<T>::msg() const noexcept {
    return lookupMsg(data_.err);
}

} // namespace srr

#endif // SRR_RESULT_HPP
