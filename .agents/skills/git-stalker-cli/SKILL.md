---
name: git-stalker-cli
description: Explain Git-Stalker's terminal options and select the right command. Use when asked for CLI help, available flags, usage examples, or whether a target mode is supported.
---

# Git-Stalker CLI overview

Use the installed `git-stalker` command. If it is not on PATH, use `./git-stalker` from the project root when a built binary exists. Do not install or rebuild it unless requested. Quote paths containing spaces.

## Options

| Command | Behavior | Detailed skill |
| --- | --- | --- |
| `git-stalker --help` or `git-stalker -h` | Print available flags and exit | `../git-stalker-help/SKILL.md` |
| `git-stalker --verbose 0`, `1`, or `2` | Set log verbosity; without another action, enter the interactive UI | `../git-stalker-verbose/SKILL.md` |
| `git-stalker --clean-logs` | Delete the application's log directory and exit | `../git-stalker-clean-logs/SKILL.md` |
| `git-stalker --get-target r "<repository-name>"` | Return the target repository name as stored in JSON | `../git-stalker-get-target/SKILL.md` |
| `git-stalker --get-target F "<file>"` | Query stored mapping targets for a file and exit | `../git-stalker-get-target/SKILL.md` |
| `git-stalker --get-target f "<function-name>"` | Return mapped file/function targets, including containing files for function targets | `../git-stalker-get-target/SKILL.md` |
| `git-stalker` | Start the interactive repository selection and mapping UI | Requires an interactive terminal |

Read the relevant detailed skill before running an option. Do not launch the interactive UI from a noninteractive agent command just to obtain help.

## Important limitations

- Target modes are case-sensitive: `F` means file, `r` means repository, and `f` means function.
- All three target modes are supported. Use exact stored names for repository and function origins, and a matching path for file origins. Repository results preserve the name stored in JSON; function-target results identify the function and its containing file.
- Options are processed left to right. Help, cleanup, and target queries return immediately. Put `--verbose` before the action, for example `git-stalker --verbose 2 --get-target F "/path/to/file.ts"`.
- Always supply complete arguments. The current CLI's missing-argument checks are incomplete; do not probe it with a bare `--verbose` or incomplete `--get-target`.
- Logs go to files, not normally to the terminal. Even help initializes logging.

These instructions document the supported CLI contract. Check `src/main.cpp`, `src/storage/get_handler.cpp`, and `src/utils/logger.cpp` when diagnosing version/build differences; an installed binary or local checkout may differ from this contract.
