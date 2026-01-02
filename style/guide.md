# Sierra Style guide

Echo Engine Project - Apache 2.0 License

Copyright (c) 2025 Echo Engine Project contributors

- https://echoengine.org
- https://docs.echoengine.org
- https://style.echoengine.org

## Introduction

The Sierra Style Guide defines the authoritative coding standards for the Echo Engine Project.

It establishes a unified set of rules governing code structure, formatting, language usage, ownership semantics, tooling configuration, and module interaction across the entire ecosystem.

Echo Engine is designed as a modular, long-lived C++ codebase. Its architecture prioritizes clear ownership, deterministic behavior, compile-time correctness, and predictable performance across a wide range of platforms and build configurations. The Sierra Style Guide exists to ensure that these design goals are reflected consistently in the code itself.

This document is not merely a formatting guide. It is a set of engineering constraints that encode architectural decisions and tradeoffs. These constraints exist to:

- Make ownership, lifetime, and intent explicit in the type system
- Enable aggressive static analysis and tooling enforcement
- Minimize ambiguity at module boundaries
- Ensure that code written today remains understandable, safe, and maintainable years into the future

## Scope & Authority

The Sierra Style Guide applies to all code within the Echo Engine Project, including:

- Public and private headers
- Platform abstraction layers
- Tooling, code generation, and build scripts
- Tests, benchmarks, and examples

Where this guide defines a rule, that rule is authoritative.

Local deviations must be explicitly documented and approved.

## Design Principles

### 1. Static Guarantees over Runtime Assumptions

The Project favors compile-time correctness wherever possible.

Runtime checks are used only when static enforcement is impractical.

### 2. Tooling as a First-Class Constraint

All code must be compatible with the project’s tooling ecosystem, including:

- Language servers
- Static analysis tools
- Sanitizers
- Automated formatting
- Code generation pipelines
- Testing frameworks

Style rules are written to be machine-verifiable wherever possible.

### 3. Long-Term Maintainability Over Short-Term Optimization

The Project is expected to evolve over many years.

The style guide therefore prioritizes:

- Readability over cleverness
- Predictable patterns over improvised solutions
- Consistency over personal preference

Performance optimizations are encouraged, but only when measured and localized.

### 4. Judgment and Author Responsibility

Not all rules defined in the Sierra Style Guide can be enforced automatically.

While the Echo Engine Project makes extensive use of compilers, static analyzers, formatters, and language servers to enforce correctness and consistency, tooling is inherently limited. Certain aspects of software design—such as ownership intent, architectural boundaries, semantic correctness, and long-term maintainability—cannot be fully verified by automated analysis.

As a result, compliance with this guide is ultimately the responsibility of the code author.

### What this Guide is

The Sierra Style Guide defines standards for:

- C++ language feature usage
- Memory management, ownership, and RAII
- Naming conventions and code layout
- Header and source file structure
- Module and namespace organization
- Error handling and diagnostics
- Concurrency and synchronization
- Code generation and build integration
- Static analysis and enforcement tooling

Each section explains what is allowed, what is forbidden, and why.

### What this Guide is not

- A tutorial on C++
- A collection of optional suggestions
- A replacement for design documentation

The guide assumes familiarity with modern C++ and focuses on project-specific constraints and expectations.

### Evolution of the Guide

The Sierra Style Guide is a living document.

Changes to the guide must:

- Be motivated by concrete problems or long-term goals
- Preserve backward compatibility where possible
- Be clearly communicated to all contributors

Style changes that materially affect existing code should include migration guidance.

## How to Read This Guide

The preceding sections describe the motivation, scope, and guiding principles behind the Sierra Style Guide.

The remainder of this document is normative.

From this point forward, the guide defines explicit, enforceable rules governing how code in the Echo Engine Project is written, structured, and reviewed. These rules are not suggestions; they represent the expected standard for all contributions.

Wherever possible, rules are written to be unambiguous and actionable. Examples are provided to clarify intent, but examples do not override rules.

## Index

- 1. Project
  - 1.1 Language & Compilers
  - 1.2 Build System
  - 1.3 Modules & Components
- 2. Format
  - 2.1 Module Naming Conventions

## 1. Project

### 1.1 Language & Compilers

#### Language Standard

All code in the Echo Engine Project must be written against the ISO C++20 standard.

Code must not rely on features introduced in later standards.

#### Compiler Extensions

Compiler-specific language extensions are strictly forbidden.

#### Supported Compilers

The Echo Engine Project supports a fixed set of compilers per platform.
Code must compile cleanly with all supported compilers.

Linux

- Compiler : GCC
- Version : TBD

MacOS

- Compiler : Clang
- Version : Apple Clang 17.0.0

Windows

- Compiler : MSVC
- Version : TBD

#### Compiler flags

All builds must enable the following compiler flags (or equivalent):

```bash
cc \
-std=c++20 \
-Werror \
-Wall \
-Wextra \
-Wshadow \
-Wold-style-cast \
-Wcast-align \
-Wsign-conversion \
-Wconversion \
-Wnull-dereference \
-Wdouble-promotion \
-pedantic \
-pedantic-errors
```

### 1.2 Build System

The Echo Engine Project is designed with a strict custom build system in mind.
Until the tool is created, `make` is the build system in use.

### 1.3 Modules & Components

The Echo Engine Project is organized as a collection of independent, composable _modules_.

Each _module_ represents a coherent unit of functionality with:

- A clearly defined responsibility
- Explicit dependencies
- Independent versioning and evolution

_Modules_ are designed to be developed, tested, and reasoned about in isolation, while still integrating cleanly into larger systems.

#### Modules

A _module_ is defined as:

- A standalone Git repository
- With its own build configuration
- With a well-defined public interface
- And explicit dependencies

_Modules_ are integrated into consuming _modules_ using Git Submodules.

#### Module Dependencies

- Dependencies between _modules_ must be explicit.
- Cyclic dependencies between _modules_ are forbidden.
- Each _module_ is responsible for declaring and managing its own dependencies.

#### Components

Within a _module_, code may be organized into _components_.

A _component_ is a logical subdivision of a _module_ that:

- Groups related functionality
- Has a clear purpose within the _module_
- May expose a public interface within the _module_

_Components_ exist solely for internal organization and clarity.
They do not represent independent _modules_ and must not be treated as such.

#### Primary Component

Each _module_ must define a primary _component_.

- The primary _component_ must be named after the _module_ itself
- It represents the core functionality of the _module_
- It defines the _module_’s primary public interface

#### Shared Component

_Modules_ may define a special _component_ reserved for functionality that is shared across multiple _components_ within the same _module_.

- This _component_ must be named `shared`
- It contains code used by more than one _component_
- Must not contain _module_-specific policy or behavior
- Must remain free of dependencies on higher-level _components_

#### Component Dependencies

Within a _module_:

- _Components_ may depend on the shared _component_
- The shared _component_ must not depend on other _components_
- The primary _component_ may depend on other _components_
- Cyclic dependencies between _components_ are forbidden

_Component_ dependencies must form a directed acyclic graph.

## 2. Format

### 2.1 Module Naming Conventions

#### Module

Each _module_ must be named after a letter in the [NATO phonetic alphabet](https://en.wikipedia.org/wiki/NATO_phonetic_alphabet).

The chosen name should reflect the _module_’s purpose where possible.

Examples:

| Purpose       | Name   |
| ------------- | ------ |
| Engine (core) | Echo   |
| Shared        | Sierra |
| Logging       | Lima   |

The phonetic name is the canonical _module_ identifier used throughout the project.

#### Repository

The Git repository name must be the _module_ name, capitalized.
Thus the repository root directory must match the capitalized form.

#### Component

Within a _module_ repository:

- All _component_ directory names must be lowercase
- No separators (underscores, hyphens) are permitted
- _Component_ names must be concise and descriptive

The primary _component_ directory name must be the _module_ name in all lowercase.

Examples:

| _Module_ name | Primary _component_ |
| ------------- | ------------------- |
| Echo          | echo                |
| Sierra        | sierra              |
| Lima          | lima                |

#### Namespace

Each _module_ defines a single top-level namespace, derived mechanically from the _module_ name.

The namespace is formed as follows:

- Take the first letter of the _module_ name
- Append all subsequent consonants, in order
- If the resulting string exceeds 4 characters, remove the second-to-last character repeatedly until exactly 4 characters remain
- Convert the final result to lowercase

This derived name is the canonical _module_ namespace.

Examples:

| _Module_ name | Sequence | Namespace |
| ------------- | -------- | --------- |
| Echo          | E + ch   | ech       |
| Sierra        | S + rr   | srr       |
| Lima          | L + m    | lm        |

The primary and shared _component_ must use the top level namespace solely.

Example:

```C++
namespace mdl {

// ...

} // namespace mdl
```

Additional _components_ must use a sub-namespace of the form:

```C++
namespace mdl::cmp {

// ...

} // namespace mdl::cmp
```

Where:

- `cmp` is derived from the _component_ name
- It must be lowercase
- It can be shortened if necessary
- The resulting namespace should be concise and unambiguous

Internal code which should not be exposed must also use a sub-namespace of the forms:

```C++
namespace mdl::impl {

// ...

} // namespace mdl::impl
```

and

```C++
namespace mdl::cmp::impl {

// ...

} // namespace mdl::cmp::impl
```

### 2.2 File Naming Conventions

#### File Extensions

Public and private C++ headers must use the .hpp extension.

C++ source files must use the .cpp extension.

No alternative file extensions are permitted.

#### Class files

Files whose primary purpose is to define a class or closely related set of types must:

- Use `PascalCase` for the base filename
- Use matching names for header and source files

Examples:

```
include/cmp/ClassName.hpp
src/cmp/ClassName.cpp

include/cmp/impl/TypeName.hpp
src/cmp/impl/TypeName.cpp
```

#### Non-Class files

Source files that do not primarily define a single class (e.g. utilities, free functions, internal helpers) must use `snake_case` for the base filename.

#### Header files

The public header filename must match the component name exactly.

#### Entry point

Each executable target must define a single entry point source file.
The entry point file must be named `entry.cpp`.

This rule applies regardless of module or component.

### 2.3 General Naming Conventions

#### Guidelines

- Names must be descriptive, unambiguous, and concise
- Abbreviations should be avoided unless well-established
- Identifiers must not encode type information redundantly
- Compound names must be ordered from least specific to most specific

#### Identifiers

The following table defines the required case style for each category:

| Category                                 | Convention                 |
| ---------------------------------------- | -------------------------- |
| Variables                                | `lower_snake_case`         |
| Namespaces                               | `lower_snake_case`         |
| Functions                                | `camelCase`                |
| Methods                                  | `camelCase`                |
| Types (classes, structs, enums, aliases) | `PascalCase`               |
| Concepts                                 | `PascalCase`               |
| Constants                                | `UPPER_SNAKE_CASE`         |
| Macros                                   | `UPPER_SNAKE_CASE`         |
| Enum Values                              | `UPPER_SNAKE_CASE`         |
| Template Parameters                      | Single uppercase character |

#### Additional Specifications

Namespaces must be a single word.

Examples:

```C++
namespace name          { /* ... */ } // Ok  (single word)
namespace compound_name { /* ... */ } // Bad (multiple words)
namespace name1::name2  { /* ... */ } // Ok  (single words)
```

Private data members must include a trailing underscore (`_`).

Example:

```C++
class ClassName {

private:
    int member_

};
```

Macros must be prefixed to reflect their logical namespace.

Examples:

```C++
// in namespace mdl
#define MDL_MACRO_NAME

// or

// in namespace mdl::cmp
#define MDL_CMP_MACRO_NAME
```

#### Header Guards

Header guards must be used in all headers.

Guard names must be globally unique, be prefixed with the _module_/_component_ namespace and must reflect the relative path of the header.

Example:

```C++
#ifndef CMP_PATH_TO_HEADER_HPP
#define CMP_PATH_TO_HEADER_HPP

// ...

#endif // CMP_PATH_TO_HEADER_NAME_HPP
```

### 2.4 Spacing & layout

The code must be formatted according to the `clang-format` configuration files provided in the Sierra Style Guide.

### 2.5 Include Directives

#### Direct Dependencies

Source and header files must explicitly include every header that they directly depend on.

Indirect or transitive includes must not be relied upon

The removal or reordering of unrelated includes must not break compilation

Example:

```C++
// a.hpp

struct A { /* ... */ };
```

```C++
// b.hpp

#include "a.hpp"
```

```C++
// c.cpp

#include "b.hpp"

using C = A; // Wrong: relies on indirect include of "a.hpp"
```

#### Absolute Path

Include paths must not be written relative to the including file.

Example:

```C++
// Bad (relative to current file)
#include "../realtive/path/a.hpp"
#include "./realtive/path/b.hpp"
```

```C++
// Good (relative to current file)
#include "absolute/path/a.hpp"
#include "absolute/path/b.hpp"
```

#### Quoted & Angled Includes

Quoted includes must be used when including headers from the current _module_.

Example:

```C++
#include "cmp/cmp.hpp" // public header (current component)
#include "shared/shared.hpp" // public header (other component)

#include "cmp/impl/detail.hpp" // internal header
```

Angled includes must be used for all headers outside the current module (other modules, Third-party Libraries, Standard Library).

Example:

```C++
#include <module/module.hpp> // other module (mdl/)

#include <lib/lib.h> // third-party library (ext/)

#include <vector> // standard library
```

#### Include Ordering

Include ordering is enforced by `clang-format`.

The canonical order is defined by the project’s `clang-format` configuration

Example:

```C++
// Internal headers (current module)
#include "cmp/impl/a.hpp"
#include "cmp/impl/b.hpp"

// Public headers (current module)
#include "cmp/a.hpp"
#include "cmp/b.hpp"

// Other modules (mdl/)
#include <mdl/a.hpp>
#include <mdl/b.hpp>

// External dependency (ext/)
#include <lib/a.h>
#include <lib/b.h>

// Standard library
#include <a>
#include <b>
```

### 2.6 File Structure

Files must present their contents in the following order:

#### Preamble

- Copyright and license notice
- Use the `full.txt` template for public files
- Use the `short.txt` template for implementation files

#### Header Guard (Header only)

```C++
#ifndef CMP_PATH_TO_HEADER_HPP
#define CMP_PATH_TO_HEADER_HPP
```

#### Includes

Ordered and grouped as defined in the Include Directives section.

#### Macro Definitions

Macros must be minimal and localized.

Unrelated and unused macros are forbidden.

#### Namespace opening

Code should be entirely contained in namespaces.

Source files may have an anonymous namespace if necessary.

#### Types & Forward Declaration

Type aliases and forward declarations of classes and structs.

#### Constants

`constexpr` definitions with static storage duration.

#### Function Declaration (Header only)

Definitions should be separated even for `inline`, `constrexpr`/`consteval`, and templated functions.

#### Class & Struct Definitions

Complete type definitions.

#### Implementation

Headers must define `inline` methods here.

#### Namespace Closing

Must be commented.

#### Header Guard End (Header only)

```C++
#enif // CMP_PATH_TO_HEADER_HPP
```

## 3. Language Features

### 3.1 Memory Management and Resource Lifetime

#### RAII

All resources must be managed using RAII (Resource Acquisition Is Initialization).

This applies to, but is not limited to:

- Dynamic memory
- File handles
- Sockets
- Mutexes and locks
- Threads
- OS or platform handles

Resources must be acquired in constructors and released in destructors.
Manual acquisition and release outside RAII types is forbidden.

#### Ownership Model

Every allocation must have exactly one logical owner.

- Ownership must be deterministic.
- Ownership must be unambiguous.
- Ownership must not be shared implicitly.

Ownership and lifetime semantics must be determined solely by the type system.

- Ownership must not be communicated via comments or conventions.
- Function signatures must make ownership intent explicit.
- Code that requires contextual knowledge to determine ownership is non-compliant.

Examples:

```C++
void foo(Bar *); // ambiguous (invalid)

void foo(std::unique_ptr<Bar>); // transfer (valid)
void foo(const Bar &);          // borrow (valid)
void foo(Bar &);                // borrow (valid)
```

#### Allocation

Use of `new` and `delete` is permitted only:

- Inside RAII wrapper types
- Inside allocator implementations

Such usage must be fully encapsulated and invisible to consumers.

#### Wrappers

All allocation wrappers must:

- Allocate resources in their constructor
- Release resources in their destructor
- Enforce exclusive ownership
- Be exception-safe

Partial or delayed ownership is forbidden.

#### Stack & Heap Allocation

Stack allocation is strongly preferred
Heap allocation is permitted only when required by:

- Object lifetime requirements
- Polymorphic behavior
- Object size constraints

Unnecessary heap allocation is considered a design error.

#### References

References are the preferred way to express non-owning access

- A reference implies non-null and valid lifetime.
- References must not outlive the referenced object.

#### Raw Pointers

Raw pointers are forbidden by default.

Raw pointers may be used only:

- When interfacing with legacy or C APIs
- In clearly documented, performance-critical code paths

In all cases:

- Raw pointers must be non-owning
- Raw pointers must not be deleted

#### Smart Pointers

- `std::shared_ptr` is forbidden
- Shared ownership is not permitted

Exclusive ownership must be expressed through deterministic lifetime management.

#### Views & Non-Owning Ranges

- `std::span` must be used for non-owning views over contiguous data
- `std::string_view` must be used for non-owning string references
- Views must not outlive the underlying storage
- Views must not be stored unless lifetime is guaranteed

- new, new[], delete, delete[], alloc, calloc, realloc, free
  - only in tight, contained wrappers or allocators
  - use `[[nodiscard]]` on allocation
- RAII wrappers must
  - Acquire resource in constructor
  - Release resource in destructor

### 3.2 Templates & Generic Programming

#### Concepts First

C++20 concepts must be used to express template requirements whenever possible.

Concepts are preferred over:

- SFINAE
- `std::enable_if`
- Unconstrained templates

#### SFINAE Restrictions

- Direct use of SFINAE is discouraged.
- `std::enable_if` and similar techniques are forbidden.
- SFINAE may be used internally only when concepts cannot express the required constraint.

#### CRTP Usage

CRTP-based static polymorphism is explicitly allowed.

CRTP may be used when:

- Zero-overhead abstraction is required
- Behavior is fixed at compile time
- The relationship is internal and well-documented

CRTP must not:

- Obscure ownership or lifetime
- Replace simple composition
- Be used as a workaround for missing concepts

#### Template Scope and Visibility

Templates intended for public use must:

- Be declared in public headers
- Be fully constrained using concepts

### 3.3 Modern Features and Restrictions

#### Macros

Macros must be used sparingly.

Macros are permitted primarily for:

- Platform detection
- Build configuration
- Compile-time feature toggles

#### Reinterpret Cast

`reinterpret_cast<>` is permitted only in tightly scoped, well-contained situations.

- Usage must be localized and minimal
- Usage must be justified by platform or ABI requirements
- Code must be documented to explain safety assumptions
- Unbounded or pervasive use is forbidden.

#### Dynamic Polymorphism

Dynamic polymorphism is forbidden.

This includes:

- `virtual` functions
- `dynamic_cast<>`
- RTTI (typeid, runtime type information)

Compile-time polymorphism must be used instead (templates, concepts, CRTP).

#### C-style Casts

C-style casts are forbidden.

All casts must use explicit C++ cast syntax:

- static_cast<>
- const_cast<>
- reinterpret_cast<> (restricted)

#### Exceptions

C++ exceptions are forbidden. `throw`, `try`, and `catch` must not be used.

Error handling is defined separately in the Error Handling section.

#### Forbidden Features

The following are forbidden:

- C++ coroutines
- `goto` control flow
- `auto` type deduction
- C++20 modules (`module`, `import`)

#### Structured Bindings & Type Deduction

Structured bindings rely on implicit type deduction and therefore conflict with the project’s requirement for explicit types.

- Structured bindings are forbidden
- The `auto` keyword is forbidden in all forms
- All variable declarations must explicitly spell out their type

Values must be accessed explicitly through named variables, accessors, or structured types.

### 3.4 Concurrency & Parallelism

#### Status

Concurrency and parallel execution are not currently part of the Echo Engine Project’s design requirements.

At this time:

- No threading model is defined
- No synchronization primitives are approved
- No concurrency-related language or library features are standardized

#### Future Work

This section is intentionally reserved.

A formal concurrency model will be specified only when concurrent execution becomes a required architectural concern. At that time, this section will define:

- Approved concurrency primitives
- Thread ownership and lifetime rules
- Synchronization and memory-ordering guarantees
- Interaction with modules and components
- Tooling and analysis requirements

Until such a model is explicitly defined:

- Code must assume single-threaded execution
- Ad-hoc concurrency solutions are forbidden
- Threading, atomics, and lock-based designs must not be introduced

## 4. Design & Patterns

### 4.1 Error handling

#### Definitions

The Sierra shared module is the single source of truth for error handling primitives.

Sierra provides:

- Standardized error enums
- Result enums for function outcomes
- Lookup utilities for converting error codes to human-readable strings

All modules must use these definitions and must not define their own error systems.

#### Error Representation

- Errors are represented using strongly typed enums
- Each enum value represents a distinct failure condition
- Error enums must not encode state or behavior

#### Result Values

Functions that may fail must return an explicit result value.

Typical patterns include:

- Returning a result enum
- Returning a composite result type (value + error)

Failure must be observable at the call site.

### 4.2 Abstraction

#### Guidelines

- Avoid abstraction bloat and unnecessary layers.
- Do not introduce abstractions without a clear and measurable benefit.
- Abstractions must not obscure data layout, ownership, or performance characteristics.

Zero-cost or near-zero-cost abstractions are preferred.

#### Classes & Structs

Classes must be used for:

- High-level abstractions
- Public APIs
- RAII wrappers managing resources or lifetime
- Objects with invariants that must be enforced

Classes are responsible for maintaining correctness and enforcing ownership rules.

Structs must be used for:

- Low-level abstractions
- Plain data carriers (POD)
- C-like interfaces and data-oriented designs
- Performance-critical code paths

### 4.3 Functions

#### Design Rules

- Overloaded functions must exhibit equivalent behavior
- Overloads must differ only in how inputs are provided, not in semantics
- Overloads must not introduce surprising or incompatible behavior

If behavior differs meaningfully, a different function name must be used.

Default arguments are forbidden.

All function behavior must be explicit at the call site.

#### Attributes & Annotations

- All functions must be marked noexcept.
- Exceptions are forbidden; noexcept documents and enforces this guarantee.

Functions that cannot be noexcept are not permitted.

- Functions whose return value conveys meaningful information must be marked `[[nodiscard]]`.
- Discarding such return values is considered a logic error.

Functions whose return value may be safely ignored must be explicitly justified.

Functions that do not return control to the call site must be marked `[[noreturn]]`.

#### Return Values

- Avoid ambiguous boolean return values.
- Avoid boolean parameters that alter behavior in non-obvious ways.

If a boolean cannot be understood without reading the implementation, it is non-compliant.

Prefer:

- Strongly typed enums (Result)
- Explicit function names
- Separate functions for distinct behavior

#### Clarity and Intent

- Function signatures must communicate intent clearly.
- Side effects must be minimal and documented
- Functions should do one thing and do it clearly

Hidden behavior or overloaded meaning is forbidden.

### 4.4 Variables

#### Rules

All variables must be initialized at the point of declaration.
Uninitialized variables are forbidden.

Variables must be declared as close as possible to their first use.
Early declarations that widen scope unnecessarily are not permitted.

#### Scope & Lifetime

- Variable scope must be minimized.
- Lifetimes must be obvious from the surrounding code.
- Variables must not outlive their usefulness.

### 4.5 Avoid

#### Singletons

- Singleton patterns are forbidden
- Implicit global access to shared state is not permitted
- Lifetime and initialization order must always be explicit

Shared services must be passed explicitly or owned by a higher-level system.

#### Global state

- Global mutable state is forbidden
- Global variables must not be used to store runtime data
- Hidden dependencies via global state are not permitted

Configuration and shared data must be owned and passed explicitly.

#### Magic Numbers

- Magic numbers are forbidden.
- All non-trivial numeric values must be named.

Use:

- `constexpr` constants
- Strongly typed enums

Numeric literals may be used only when they are self-evident and universally understood (e.g. 0, 1).

#### Macro Overuse

- Excessive macro usage is forbidden.
- Macros must not be used where language features suffice
- Macros must not encode logic, control flow, or hidden behavior

Macros are restricted to:

- Platform detection
- Build configuration
- Compile-time feature flags

## 5. Documentation

### 5.1 Comments

Prefer clear, expressive code over inline comments.

Code should be understandable without requiring explanatory comments.

Inline comments should be used only when necessary.

Inline comments must be used to:

- Justify deviations from the style guide.
- Explain non-obvious constraints or trade-offs.

### 5.2 Documentation Generation

#### Status

- No documentation comment standard is currently defined.
- No specific documentation generation tool is mandated.

As a result:

- Documentation comments are optional.
- No particular syntax (e.g. Doxygen-style) is required or enforced.

#### Future Work

A formal documentation standard will be introduced when auto-generated documentation becomes a project requirement.

At that time, this section will define:

- Approved documentation tools
- Required comment syntax
- Documentation coverage expectations

## 6. Testing & CodeGen

#### Status

Testing infrastructure and code generation are planned but not yet standardized within the Echo Engine Project.

A custom build system is under development and will eventually:

- Define a canonical structure for tests
- Support automated test discovery and execution
- Provide first-class support for code generation workflows
- Enforce consistent project layouts for generated code

#### Future Work

Until the build system is finalized:

- No testing framework is mandated.
- No code generation standard is enforced.
- Ad-hoc solutions are discouraged.

Testing and code generation patterns will be specified once their requirements are concrete.
