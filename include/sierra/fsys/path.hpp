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

#ifndef SRR_FSYS_PATH_HPP
#define SRR_FSYS_PATH_HPP

#include <filesystem>
#include <string_view>
#include <utility>

inline namespace srr {
namespace fsys {
namespace stdfs = std::filesystem;

class [[nodiscard]] Path {
public:
    Path()                                        = delete;

    ~Path() noexcept                              = default;
    [[nodiscard]] Path(const Path &path) noexcept = default;
    [[nodiscard]] Path(Path &&path) noexcept      = default;

    Path &operator=(const Path &path)             = delete;
    Path &operator=(Path &&path)                  = delete;

    [[nodiscard]] inline Path(std::string_view path) noexcept;
    [[nodiscard]] inline Path(const char *path) noexcept;

    [[nodiscard]] constexpr const stdfs::path &get() const noexcept;

    [[nodiscard]] constexpr bool               isPath() const noexcept;
    [[nodiscard]] constexpr bool               isFile() const noexcept;
    [[nodiscard]] constexpr bool               isDir() const noexcept;

    [[nodiscard]] inline Path                  parent() const noexcept;

private:
    [[nodiscard]] inline Path(stdfs::path &&path) noexcept;

    stdfs::path path_;
};

inline Path::Path(std::string_view path) noexcept : path_{ path } {}

inline Path::Path(const char *path) noexcept : path_{ path } {}

constexpr const stdfs::path &Path::get() const noexcept { return path_; }

constexpr bool Path::isPath() const noexcept { return stdfs::exists(path_); }

constexpr bool Path::isFile() const noexcept {
    return stdfs::is_regular_file(path_);
}

constexpr bool Path::isDir() const noexcept {
    return stdfs::is_directory(path_);
}

Path Path::parent() const noexcept { return path_.parent_path(); }

inline Path::Path(stdfs::path &&path) noexcept : path_{ std::move(path) } {}

} // namespace fsys
} // namespace srr

#endif // SRR_FSYS_PATH_HPP
