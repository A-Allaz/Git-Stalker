---
name: git-stalker-logging
description: Follow Git-Stalker logging and error-handling conventions when implementing diagnostics, exceptions, or verbosity control.
---

# Skill: Git-Stalker Error & Log Handling

Use this skill when implementing logging, error reporting, exceptions, and verbosity control in git-stalker.

## Logging & Error Rules

- **Logging Function**: Use `log(string message)` for logging. It formats output to `cerr` with timestamp prefix (`[YYYY-MM-DD_HH-MM-SS_ms]`).
- **Error Prefix**: All error messages must be explicitly prefixed with `[ERROR]`:
  ```cpp
  log("[ERROR] Failed to get HEAD reference");
  ```
- **Exceptions & Failures**:
  - For critical runtime failures, use `__throw_runtime_error("...")`.
  - For non-fatal or recoverable errors, log with `[ERROR]` and assign fallback/null values (`nullptr`, `false`).
- **Verbosity**: Respect the global verbosity level (`extern int verbose;`, range 0 to 2) configured via `--verbose`.
