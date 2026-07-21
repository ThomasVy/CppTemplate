# CppTemplate Agent Notes

A C++23 CMake + Conan template project. No README exists; treat this file as the source of truth for project conventions.

## Stack & Versions

- C++23 (`CMAKE_CXX_STANDARD 23` with `CXX_STANDARD_REQUIRED On`).
- CMake 3.30+.
- Ninja generator (set in Conan profiles).
- Conan 2.x for dependency management.
- Compilers: MSVC 19.5 (`compiler.version=195`) (Windows) / GCC 14 (Linux).
- Dependency provider: `cmake/cmake-conan/conan_provider.cmake` via `CMAKE_PROJECT_TOP_LEVEL_INCLUDES`.

## Dependencies

Declared in `conanfile.py`:
- `fmt/12.1.0`
- `spdlog/1.17.0`
- `gtest/1.17.0`
- `cxxopts/3.3.1`
- `openssl/4.0.1`
- `boost/1.91.0` (header-only, no Python/test)
- `magic_enum/0.9.7`
- `nlohmann_json/3.12.0`

Use `find_package(<pkg> CONFIG REQUIRED)` in the consuming target.

## Project Layout

- `apps/<name>/` — executables. Use `add_project_app(NAME <name> SRCS ... PRIVATE_DEPS ...)`.
- `services/<name>/` — project-specific static libraries with optional tests. Use `add_project_library(...)` and `add_project_test(...)`.
- `libs/<name>/` — shared/reusable libraries from the `CommonCppHelpers` submodule. Use `add_project_library(...)`.
- `cmake/CMakeFunctions.cmake` — custom helpers: `add_project_library`, `add_project_app`, `add_project_test`.

Library conventions:
- Public headers: `include/<name>/<header>.h(pp)` (under the target directory).
- Private headers/sources: `src/` (under the target directory).
- Header-only libraries omit `SRCS` (they become `INTERFACE` targets).
- `add_project_library` exposes `include/` PUBLIC and `src/` PRIVATE.
- Include project headers with the library-qualified path, e.g. `"stock_problem/stock_problem.h"`, `"logger/logger.h"`, `"file_operations/i_file_operations.hpp"`.

## Code Style

- Format with `.clang-format`: Google base, 4-space indent, break after open bracket, no bin-packing, indent all namespaces.
- Use `#pragma once` in headers.
- Use C++23 features freely: `std::expected`, `std::optional`, `std::ranges`, `std::span`, `std::jthread`, `std::move_only_function`, designated initializers.
- Use `magic_enum` for enum/flag reflection.
- Use the rule-of-five macros from `common/RuleOfFiveMacros.h` when appropriate.
- Existing code mixes member-naming conventions (`m_` vs `trailing_`). Match the file you edit; do not rename unrelated members in a drive-by refactor.
- Keep public interfaces in `include/<lib>/` and implementations in `src/`. Prefer `i_*.hpp` naming for abstract interfaces.

## Build & Test

Use `CMakePresets.json`.

Windows:
```sh
cmake --workflow --preset debug-windows   # configure + build + test + package
```

Or step by step:
```sh
cmake --preset debug-windows
cmake --build --preset debug-windows
ctest --preset debug-windows
```

Linux:
```sh
cmake --preset debug-linux
cmake --build --preset debug-linux
# tests are not exposed via a test preset; run manually:
ctest --test-dir build/debug
```

Build directories: `build/debug` and `build/release` (ignored by `.gitignore`). Sanitizer presets use `build/debug-asan` (Windows) and `build/debug-sanitizers` (Linux).

### Sanitizers

Sanitizer support is in `cmake/Sanitizers.cmake` and controlled by the CMake cache options `ENABLE_ASAN` and `ENABLE_UBSAN`.

Presets:
- `debug-windows-asan` — AddressSanitizer with MSVC.
- `debug-linux-sanitizers` — ASAN + UBSAN with GCC.

```sh
cmake --build --preset debug-windows-asan
cmake --build --preset debug-linux-sanitizers
```

UBSAN is not supported with MSVC; enabling it on Windows emits a warning and is ignored.

### Format and clang-tidy

- `cmake --build --preset debug-windows --target format`
- `cmake --build --preset debug-windows --target clang-tidy`
- Install the pre-commit hook: `cmake --build --preset debug-windows --target install-hooks`
- Or manually: `git config core.hooksPath scripts`

The pre-commit hook formats staged C++ files with `clang-format`, re-stages them, and runs `clang-tidy` on staged `.c`/`.cpp` files for warnings using `build/debug/compile_commands.json`.

## Adding Code

- Add new source files to the explicit `SRCS`/`HEADERS` lists in the target's `CMakeLists.txt`. Do not use globbing for build sources.
- For a new project-specific library: create `services/<name>/` and add `add_subdirectory(<name>)` to `services/CMakeLists.txt`.
- For a new app: create `apps/<name>/` and add `add_subdirectory(<name>)` to `apps/CMakeLists.txt`.
- For a new shared/reusable helper meant to be used in other repos: add it inside `libs/<name>/` in the `CommonCppHelpers` submodule and update the submodule pointer in this repo.
- Add new Conan dependencies to `conanfile.py` `requirements()`, then use `find_package(... CONFIG REQUIRED)` in the consumer.
- Tests live in `tests/` under the target directory; use `add_project_test` and Google Test.
- Do not hardcode sanitizer flags in individual targets; use the presets or `ENABLE_ASAN`/`ENABLE_UBSAN` options.

## Verification

Before finishing a change:
1. Configure and build the relevant preset.
2. Run tests (`ctest --preset debug-windows` or `ctest --test-dir build/debug`).
3. Run `format` and `clang-tidy` targets (or let the pre-commit hook run them).
4. If you touched sanitizer-relevant code, also build the matching sanitizer preset and run tests under it.
5. Ensure no new warnings or broken tests are introduced.

## Notes

- `BUILD_TESTING` controls whether `add_project_test` creates test targets.
- `CMakeUserPresets.json` and `build/` are ignored.
- The project uses git submodules under `cmake/cmake-conan`, `cmake/WindowsToolchain`, and `libs` (`CommonCppHelpers`). Ensure they are initialized before configuring.
- `.clangd` expects the compile database at `build/debug`.
