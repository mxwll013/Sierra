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

#ifndef SRR_UTILS_CHAR_HPP
#define SRR_UTILS_CHAR_HPP

inline namespace srr {
namespace utils {

// NOLINTBEGIN(misc-confusable-identifiers)

enum Ch : char {

    // CONTROL ---
    NUL,
    SOH,
    STX,
    ETX,
    EOT,
    ENQ,
    ACK,
    BEL,

    BS,
    HT,
    LF,
    VT,
    FF,
    CR,
    SO,
    SI,

    DLE,
    DC1,
    DC2,
    DC3,
    DC4,
    NAK,
    SYN,
    ETB,
    CAN,
    EM,
    SUB,
    ESC,
    FS,
    GS,
    RS,
    US,

    // VISIBLE ---
    SPACE,
    EXCLAMATION,
    DOUBLE_QUOTE,
    HASH,
    DOLLAR,
    PERCENT,
    AMPERSAND,
    SINGLE_QUOTE,
    PAREN_OPEN,
    PAREN_CLOSE,
    STAR,
    PLUS,
    COMMA,
    MINUS,
    DOT,
    SLASH,

    NUM_0,
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,

    COLON,
    SEMI_COLON,
    ANGLED_OPEN,
    EQUALS,
    ANGLED_CLOSE,
    QUESTION,
    AT,

    UP_A,
    UP_B,
    UP_C,
    UP_D,
    UP_E,
    UP_F,
    UP_G,
    UP_H,
    UP_I,
    UP_J,
    UP_K,
    UP_L,
    UP_M,
    UP_N,
    UP_O,
    UP_P,
    UP_Q,
    UP_R,
    UP_S,
    UP_T,
    UP_U,
    UP_V,
    UP_W,
    UP_X,
    UP_Y,
    UP_Z,

    BRACKET_OPEN,
    BACKSLASH,
    BRACKET_CLOSE,
    CARET,
    UNDERSCORE,
    BACKTICK,

    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    BRACE_OPEN,
    PIPE,
    BRACE_CLOSE,
    TILDE,

    DEL,
};

// NOLINTEND(misc-confusable-identifiers)

[[nodiscard]] static constexpr bool isDigit(char chr) noexcept;
[[nodiscard]] static constexpr bool isNumerical(char chr) noexcept;

static constexpr bool               isDigit(char chr) noexcept {
    switch (chr) {
    case NUM_0: [[fallthrough]];
    case NUM_1: [[fallthrough]];
    case NUM_2: [[fallthrough]];
    case NUM_3: [[fallthrough]];
    case NUM_4: [[fallthrough]];
    case NUM_5: [[fallthrough]];
    case NUM_6: [[fallthrough]];
    case NUM_7: [[fallthrough]];
    case NUM_8: [[fallthrough]];
    case NUM_9: return true;
    default   : return false;
    }
}

static constexpr bool isNumerical(char chr) noexcept {
    if (isDigit(chr)) return true;

    switch (chr) {
    case NUM_0: [[fallthrough]];
    case NUM_1: [[fallthrough]];
    case NUM_2: [[fallthrough]];
    case NUM_3: [[fallthrough]];
    case NUM_4: [[fallthrough]];
    case NUM_5: [[fallthrough]];
    case NUM_6: [[fallthrough]];
    case NUM_7: [[fallthrough]];
    case NUM_8: [[fallthrough]];
    case NUM_9: [[fallthrough]];
    case MINUS: [[fallthrough]];
    case UP_E : [[fallthrough]];
    case PLUS : [[fallthrough]];
    case DOT  : [[fallthrough]];
    case E    : return true;
    default   : return false;
    }
}

} // namespace utils
} // namespace srr

#endif // SRR_UTILS_CHAR_HPP
