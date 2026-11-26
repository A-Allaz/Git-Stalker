---
name: git-stalker-get-target
description: Query stored Git-Stalker mappings with --get-target using repository (r), file (F), or function (f) mode. Use when finding or interpreting a repository, file, or function's mapping targets.
---

# Query mapping targets

Treat all three target modes as supported. Modes are case-sensitive: `r` selects a repository, `F` a file, and `f` a function.

## Commands and results

### Repository (`r`)

```bash
git-stalker --get-target r "<repository-name>"
```

Supply the origin repository's exact name from the mapping JSON. The result is the target repository name as formatted/stored in the JSON, not a filesystem path or file URI. Preserve its spelling and formatting; do not derive a replacement name from a directory basename.

### File (`F`)

```bash
git-stalker --get-target F "/absolute/path/to/tlsoptions.ts"
```

Supply the source file path. File targets are paths; function targets include the target function name and its containing file. The file-query CLI prints a heading and targets prefixed with `file://`. A function target may be rendered as `functionName at filePath`, so do not assume every output line is a directly openable file URI.

### Function (`f`)

```bash
git-stalker --get-target f "<function-name>"
```

Supply the source function's exact stored name. For a mapped file target, report the target file name/path and any function name supplied by the result. For a mapped function target, report the target function's name together with its containing file. Preserve the distinction between a file target and a function target; do not invent a function name for a file-only target.

If the source function name is ambiguous across files or repositories, inspect the mapping records or ask which source the user means. Do not invent an additional CLI disambiguation argument; check the installed command's accepted syntax before adding one.

## Running the command

Use the installed `git-stalker`. If it is unavailable, use the built `./git-stalker` from the project root. Do not install or rebuild unless requested. Quote names and paths containing spaces.

For diagnostic logging, put verbosity before the query:

```bash
git-stalker --verbose 2 --get-target r "<repository-name>"
git-stalker --verbose 2 --get-target F "/absolute/path/to/tlsoptions.ts"
git-stalker --verbose 2 --get-target f "<function-name>"
```

Always supply both a mode and an origin. Queries exit without starting the interactive UI.

## File path handling

- Resolve which file the user means. If a basename is ambiguous, ask or inspect the workspace rather than choosing arbitrarily.
- Prefer an absolute path. File mode converts relative paths to absolute, lexically normalized paths relative to the current working directory; it does not search all repositories by basename or resolve symlinks to a canonical path.
- The stored file name must match that resulting path exactly. `tlsoptions.ts` works only when the working directory makes it resolve to the stored path.
- Do not apply file-path normalization to repository or function names.

## Stored mapping prerequisites

The command queries existing mappings, not inferred relationships from Git history. It reads JSON files from `/home/<user>/.gitstalker/gitstalker_mappings/`; `<user>` is `USERNAME`, falling back to `USER`.

Stored repository locations and commits must remain accessible because loading opens repositories and looks up recorded commits. Unrelated stale mapping files can also cause failures because retrieval loads all mapping files.

## Interpret failures and troubleshoot

- Distinguish an explicit no-target result from a crash, exception, or unexpectedly empty output. Silence is not proof that no mapping exists.
- A file query's empty target list produces `Did not found any mapping target for ...`; this does not by itself distinguish an unknown source file from one with no mapped targets.
- Inspect the matching timestamped log under `/home/<user>/.gitstalker/gitstalker_logs/`; read `../git-stalker-verbose/SKILL.md` for details.
- Check exact stored names, file paths, repository locations, and commit availability without editing mappings.
- If an installed or local binary does not support the documented modes, report a version/build mismatch rather than assuming `r` or `f` is inherently unsupported. Check the actual binary and current source before diagnosing implementation bugs.
- Do not automatically delete logs, edit stored mappings, or modify repositories to make a query succeed.
