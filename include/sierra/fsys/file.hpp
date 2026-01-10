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

#ifndef SRR_FSYS_FILE_HPP
#define SRR_FSYS_FILE_HPP

#include "sierra/error.hpp"
#include "sierra/fsys/path.hpp"
#include "sierra/result.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

inline namespace srr {
namespace fsys {

class [[nodiscard]] FileRead {
public:
    FileRead(const FileRead &file)            = delete;
    FileRead()                                = delete;

    FileRead &operator=(const FileRead &file) = delete;
    FileRead &operator=(FileRead &&file)      = delete;

    [[nodiscard]] inline FileRead(FileRead &&file) noexcept;
    [[nodiscard]] inline FileRead(const Path &path) noexcept;

    inline ~FileRead() noexcept;

    [[nodiscard]] constexpr bool     opened() const noexcept;

    [[nodiscard]] inline std::string dump() noexcept;

private:
    std::unique_ptr<std::ifstream> stream_;
};

class [[nodiscard]] File {
public:
    File(const File &file)            = delete;
    File()                            = delete;

    ~File()                           = default;

    File &operator=(const File &file) = delete;
    File &operator=(File &&file)      = delete;

    [[nodiscard]] inline File(File &&file) noexcept;
    [[nodiscard]] inline File(Path &&path) noexcept;

    inline Result<FileRead> read() const noexcept;

private:
    Path path_;
};

[[nodiscard]] inline Result<File> openFile(Path &&path) noexcept;
[[nodiscard]] inline Result<File> openFile(const Path &path) noexcept;
[[nodiscard]] inline Result<File> openFile(std::string_view path) noexcept;

[[nodiscard]] inline Result<File> makeFile(Path &&path) noexcept;
[[nodiscard]] inline Result<File> makeFile(const Path &path) noexcept;
[[nodiscard]] inline Result<File> makeFile(std::string_view path) noexcept;

inline FileRead::FileRead(FileRead &&file) noexcept :
    stream_{ std::move(file.stream_) } {}

inline FileRead::FileRead(const Path &path) noexcept :
    stream_{ std::make_unique<std::ifstream>(path.get()) } {}

inline FileRead::~FileRead() noexcept {
    if (stream_ == nullptr) return;

    if (stream_->is_open()) stream_->close();
}

constexpr bool FileRead::opened() const noexcept { return stream_->is_open(); }

inline std::string FileRead::dump() noexcept {
    std::stringstream buffer{};
    buffer << stream_->rdbuf();
    return buffer.str();
}

inline File::File(File &&file) noexcept : path_{ std::move(file.path_) } {}

inline File::File(Path &&path) noexcept : path_{ std::move(path) } {}

inline Result<FileRead> File::read() const noexcept {
    if (!path_.isPath()) return Err::FS_NO_SUCH_PATH;
    if (!path_.isFile()) return Err::FS_NO_SUCH_FILE;

    FileRead read{ path_ };
    if (!read.opened()) return Err::FS_FAILED_TO_OPEN;

    return read;
}

inline Result<File> openFile(Path &&path) noexcept {
    if (!path.isPath()) return Err::FS_NO_SUCH_PATH;
    if (!path.isFile()) return Err::FS_NO_SUCH_FILE;

    return File{ std::move(path) };
}

inline Result<File> openFile(const Path &path) noexcept {
    Path copy{ path };
    return openFile(std::move(copy));
}

inline Result<File> openFile(std::string_view path) noexcept {
    return openFile(Path{ path });
}

inline Result<File> makeFile(Path &&path) noexcept {
    if (!path.isPath()) return Err::FS_FILE_ALREADY_EXISTS;

    const Path parent = path.parent();

    if (!parent.isDir()) return Err::FS_NO_SUCH_PARENT;

    return File{ std::move(path) };
}

inline Result<File> makeFile(const Path &path) noexcept {
    Path copy{ path };
    return makeFile(std::move(copy));
}

inline Result<File> makeFile(std::string_view path) noexcept {
    return makeFile(Path{ path });
}

} // namespace fsys
} // namespace srr

#endif // SRR_FSYS_FILE_HPP
