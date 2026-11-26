---
name: git-stalker-verbose
description: Use git-stalker --verbose to control logging or diagnose a file-target query. Use when the user wants more detailed logs, verbosity levels, or the location of diagnostic output.
---

# Set log verbosity

Pass exactly one of `0`, `1`, or `2` after `--verbose`. The default is `0`; it does not suppress all logging. Higher values enable additional messages at call sites; `2` is the most detailed supported level.

For a noninteractive file query:

```bash
git-stalker --verbose 2 --get-target F "/absolute/path/to/tlsoptions.ts"
```

Read `../git-stalker-get-target/SKILL.md` for query prerequisites and interpretation. Use `./git-stalker` from the project root if using the local built binary instead of an installed command.

Put `--verbose` before the action for consistent usage. Use `--show-logs` separately to display the latest existing log; it does not change the verbosity of that log.

`git-stalker --verbose 2` alone enters the interactive UI after setting verbosity. Only launch it if the user wants an interactive session and an appropriate terminal is available.

## Find the logs

The application redirects `stderr` to timestamped `.log` files in:

```text
/home/<user>/.gitstalker/gitstalker_logs/
```

`<user>` is selected from `USERNAME`, falling back to `USER`; this directory is not based on `HOME` or XDG variables. Verbose output is not normally printed to the terminal.

Use `git-stalker --show-logs` to display the latest log; read `../git-stalker-show-logs/SKILL.md` for selection rules and failure handling. Share only diagnostic excerpts and avoid exposing unrelated repository data. Do not delete logs while investigating a failure.

Always supply a valid verbosity argument (`0`, `1`, or `2`); do not run a bare `--verbose` or use malformed values.
