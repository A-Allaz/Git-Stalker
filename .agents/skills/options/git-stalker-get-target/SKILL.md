---
name: git-stalker-get-target
description: Query stored Git-Stalker mappings with --get-target using repository (r), file (F), or function (f) mode. Use when finding or interpreting a repository, file, or function's mapping targets.
---

# Query mapping targets

Treat all three target modes as supported. Modes are case-sensitive: `r` selects a repository, `F` a file, and `f` a function.

## Commands and results

### Repository (`r`)

```bash
git-stalker --get-target r "/absolute/path/to/repo"
```

Supply the origin repository's path. The result is the mapped target repository's path. Preserve the returned path rather than replacing it with a directory basename.

### File (`F`)

```bash
git-stalker --get-target F "/absolute/path/to/file.ts"
```

Supply the source file path. Results include a heading followed by target paths or function targets formatted as `functionName at file://<path>`. Do not assume every output line is a directly openable file URI.

### Function (`f`)

```bash
git-stalker --get-target f "/absolute/path/to/file.ts" "<function-name>"
```

Supply the containing file's path and the source function's exact name as two separate arguments. File targets are paths; function targets include the function name and containing file, formatted as `functionName at file://<path>`. Preserve this distinction; do not invent a function name for a file-only target.

If the source function name is ambiguous across files or repositories, ask which containing file the user means.

## Running the command

Use the installed `git-stalker`. If it is unavailable, use the built `./git-stalker` from the project root. Do not install or rebuild unless requested. Quote names and paths containing spaces.

For diagnostic logging, put verbosity before the query:

```bash
git-stalker --verbose 2 --get-target r "/absolute/path/to/repo"
git-stalker --verbose 2 --get-target F "/absolute/path/to/file.ts"
git-stalker --verbose 2 --get-target f "/absolute/path/to/file.ts" "<function-name>"
```

Always supply a mode and all its required arguments. Queries exit without starting the interactive UI.

## File path handling

- Resolve which file the user means. If a basename is ambiguous, ask or inspect the workspace rather than choosing arbitrarily.
- Prefer an absolute path. File mode converts relative paths to absolute, lexically normalized paths relative to the current working directory; it does not search all repositories by basename or resolve symlinks to a canonical path.
- The stored file name must match that resulting path exactly. `file.ts` works only when the working directory makes it resolve to the stored path.
- Repository queries also accept relative paths resolved from the current working directory. Function names must match exactly; do not treat them as paths.

## Stored mapping prerequisites

The command queries existing mappings, not inferred relationships from Git history. It reads JSON files from `/home/<user>/.gitstalker/gitstalker_mappings/`; `<user>` is `USERNAME`, falling back to `USER`.

Stored repository locations and recorded commits must remain accessible. Stale mappings, including those for unrelated repositories, can cause a query to fail.

## Interpret failures and troubleshoot

- Distinguish an explicit no-target result from a crash, exception, or unexpectedly empty output. Silence is not proof that no mapping exists.
- A file query's empty target list produces `Did not found any mapping target for ...`; this does not by itself distinguish an unknown source file from one with no mapped targets.
- Use `git-stalker --show-logs` to inspect the latest diagnostic log; read `../git-stalker-show-logs/SKILL.md` for details. For more detailed logs on a subsequent query, read `../git-stalker-verbose/SKILL.md`.
- Check exact stored names, file paths, repository locations, and commit availability without editing mappings.
- If the installed command does not support the documented modes, report the observed behavior and a possible version mismatch rather than assuming `r` or `f` is inherently unsupported. Do not rebuild or install without a request.
- Do not automatically delete logs, edit stored mappings, or modify repositories to make a query succeed.
