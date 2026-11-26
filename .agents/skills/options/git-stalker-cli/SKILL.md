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
| `git-stalker --show-logs` | Display the latest existing log and exit | `../git-stalker-show-logs/SKILL.md` |
| `git-stalker --get-target r "<repository-path>"` | Query the mapped target repository's path and exit | `../git-stalker-get-target/SKILL.md` |
| `git-stalker --get-target F "<file>"` | Query stored mapping targets for a file and exit | `../git-stalker-get-target/SKILL.md` |
| `git-stalker --get-target f "<file>" "<function-name>"` | Query mapped file/function targets for a function and exit | `../git-stalker-get-target/SKILL.md` |
| `git-stalker` | Start the interactive repository selection and mapping UI | Requires an interactive terminal |

Read the relevant detailed skill before running an option. Do not launch the interactive UI from a noninteractive agent command just to obtain help.

## Important limitations

- Target modes are case-sensitive: `F` means file, `r` means repository, and `f` means function.
- All three target modes are supported. Supply a repository path for `r`, a file path for `F`, and a file path plus an exact function name as separate arguments for `f`.
- Run one action per command. `--show-logs` takes precedence over all other options, regardless of argument order. Help, cleanup, and target queries exit after their action.
- Put `--verbose` before the action, for example `git-stalker --verbose 2 --get-target F "/path/to/file.ts"`.
- Always supply complete, valid arguments; do not run a bare `--verbose` or incomplete `--get-target`.
- Logs go to files, not normally to the terminal. Use `--show-logs` to display the latest existing log.
- If the installed command behaves differently, report the command, observed output, and possible version mismatch. Do not install or rebuild without a request.
