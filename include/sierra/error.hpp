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

#include "sierra/prims.hpp"

#include <string>
#include <string_view>

inline namespace srr {

enum class Err : u8 {
    OK = 0,

    // none
    FAILURE,
    NOT_IMPLEMENTED,

    // none : access
    INDEX_OUT_OF_RANGE,
    NO_SUCH_KEY,

    // none : parse
    INVALID_NUMBER,

    // fs : access
    FS_NO_SUCH_PATH,
    FS_NO_SUCH_FILE,
    FS_NO_SUCH_DIR,
    FS_NO_SUCH_PARENT,
    FS_FILE_ALREADY_EXISTS,
    FS_DIR_ALREADY_EXISTS,
    FS_FAILED_TO_OPEN,

    // json : cast
    JSON_BAD_CAST,
    JSON_BAD_SUBTYPE,
    JSON_BAD_ASSUMED,

    // json : parse
    JSON_BAD_TOKEN,

    // json : syntax
    JSON_SYNTAX_EXP_VALUE,
    JSON_SYNTAX_EXP_KEY,
    JSON_SYNTAX_EXP_SEP,
    JSON_SYNTAX_DBL_KEY,
    JSON_SYNTAX_DBL_ROOT,

    ERR_COUNT,
};

enum class ErrType : u8 {
    NONE = 0,

    FSYS,
    JSON,
};

enum class ErrSubtype : u8 {
    NONE = 0,

    ACCESS,
    CAST,
    PARSE,
    SYNTAX,
};

struct ErrInfo {
    std::string_view msg;
    ErrType          type    = ErrType::NONE;
    ErrSubtype       subtype = ErrSubtype::NONE;
};

[[nodiscard]] static constexpr ErrInfo lookupInfo(Err err) noexcept {
    switch (err) {
    case Err::OK:
        return {
            .msg = "Ok",
        };
    case Err::FAILURE        : return { .msg = "Failure" };
    case Err::NOT_IMPLEMENTED: return { .msg = "Not implemented" };

    case Err::INDEX_OUT_OF_RANGE:
        return { .msg = "Index out of range", .subtype = ErrSubtype::ACCESS };
    case Err::NO_SUCH_KEY:
        return { .msg = "No such key", .subtype = ErrSubtype::ACCESS };

    case Err::INVALID_NUMBER:
        return { .msg = "Invalid number", .subtype = ErrSubtype::PARSE };

    case Err::FS_NO_SUCH_PATH:
        return { .msg     = "No such file or directory",
                 .type    = ErrType::FSYS,
                 .subtype = ErrSubtype::ACCESS };
    case Err::FS_NO_SUCH_FILE:
        return { .msg     = "No such file",
                 .type    = ErrType::FSYS,
                 .subtype = ErrSubtype::ACCESS };
    case Err::FS_NO_SUCH_DIR:
        return { .msg     = "No such directory",
                 .type    = ErrType::FSYS,
                 .subtype = ErrSubtype::ACCESS };
    case Err::FS_NO_SUCH_PARENT:
        return { .msg     = "No such parent directory",
                 .type    = ErrType::FSYS,
                 .subtype = ErrSubtype::ACCESS };

    case Err::FS_FILE_ALREADY_EXISTS:
        return { .msg     = "File already exists",
                 .type    = ErrType::FSYS,
                 .subtype = ErrSubtype::ACCESS };
    case Err::FS_DIR_ALREADY_EXISTS:
        return { .msg     = "Directory already exists",
                 .type    = ErrType::FSYS,
                 .subtype = ErrSubtype::ACCESS };
    case Err::FS_FAILED_TO_OPEN:
        return { .msg     = "Failed to open file",
                 .type    = ErrType::FSYS,
                 .subtype = ErrSubtype::ACCESS };

    case Err::JSON_BAD_CAST:
        return { .msg     = "Attempted to cast to wrong type",
                 .type    = ErrType::JSON,
                 .subtype = ErrSubtype::CAST };
    case Err::JSON_BAD_SUBTYPE:
        return { .msg     = "Attempted to cast to wrong subtype",
                 .type    = ErrType::JSON,
                 .subtype = ErrSubtype::CAST };
    case Err::JSON_BAD_ASSUMED:
        return { .msg     = "Assumed (implicit cast) to wrong type",
                 .type    = ErrType::JSON,
                 .subtype = ErrSubtype::CAST };

    case Err::JSON_BAD_TOKEN:
        return { .msg     = "Invalid token",
                 .type    = ErrType::JSON,
                 .subtype = ErrSubtype::PARSE };

    case Err::JSON_SYNTAX_EXP_VALUE:
        return { .msg     = "Was expecting value",
                 .type    = ErrType::JSON,
                 .subtype = ErrSubtype::SYNTAX };
    case Err::JSON_SYNTAX_EXP_KEY:
        return { .msg     = "Was expecting key",
                 .type    = ErrType::JSON,
                 .subtype = ErrSubtype::SYNTAX };
    case Err::JSON_SYNTAX_EXP_SEP:
        return { .msg     = "Was expecting separator",
                 .type    = ErrType::JSON,
                 .subtype = ErrSubtype::SYNTAX };
    case Err::JSON_SYNTAX_DBL_KEY:
        return { .msg     = "Key was specified twice",
                 .type    = ErrType::JSON,
                 .subtype = ErrSubtype::SYNTAX };
    case Err::JSON_SYNTAX_DBL_ROOT:
        return { .msg     = "Tree has multiple root objects",
                 .type    = ErrType::JSON,
                 .subtype = ErrSubtype::SYNTAX };

    case Err::ERR_COUNT: return { .msg = "Unknown error" };
    }
}

[[nodiscard]] constexpr bool ofType(Err err, ErrType type) noexcept {
    return lookupInfo(err).type == type;
}

[[nodiscard]] constexpr bool ofType(Err err, ErrSubtype subtype) noexcept {
    return lookupInfo(err).subtype == subtype;
}

[[nodiscard]] constexpr bool ofType(Err        err,
                                    ErrType    type,
                                    ErrSubtype subtype) noexcept {
    const ErrInfo info = lookupInfo(err);
    return info.type == type && info.subtype == subtype;
}

[[nodiscard]] static constexpr std::string_view lookupPrefix(
    ErrType type) noexcept {
    switch (type) {
    case ErrType::NONE: return "";
    case ErrType::FSYS: return "[fsys]";
    case ErrType::JSON: return "[json]";
    }
}

[[nodiscard]] static constexpr std::string_view lookupPrefix(
    ErrSubtype type) noexcept {
    switch (type) {
    case ErrSubtype::NONE  : return "";
    case ErrSubtype::ACCESS: return "[access]";
    case ErrSubtype::CAST  : return "[cast]";
    case ErrSubtype::PARSE : return "[parse]";
    case ErrSubtype::SYNTAX: return "[syntax]";
    }
}

[[nodiscard]] constexpr std::string lookupMsg(Err err) noexcept {
    const ErrInfo info = lookupInfo(err);
    std::string   msg{};

    msg += lookupPrefix(info.type);
    msg += lookupPrefix(info.subtype);

    if (!msg.empty()) msg += " ";

    msg += info.msg;

    return msg;
}

} // namespace srr

#endif // SRR_ERROR_HPP
