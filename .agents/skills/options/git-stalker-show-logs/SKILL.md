---
name: git-stalker-show-logs
description: Display the latest Git-Stalker log with --show-logs. Use when the user wants to view recent application logs, inspect the last run, or understand how the latest log is selected and displayed.
---

# Show the latest application log

```bash
git-stalker --show-logs
```

If using the built binary in the project root rather than an installed command:

```bash
./git-stalker --show-logs
```

This is a noninteractive, read-only action: it prints the latest existing log and exits without launching the UI, initializing a new log, or deleting logs.

## Selection and output

Logs are read from:

```text
/home/<user>/.gitstalker/gitstalker_logs/
```

`<user>` comes from `USERNAME`, falling back to `USER`. This path is not derived from `HOME` or XDG variables.

- Only regular files with the exact `.log` extension are considered, directly inside this directory (not recursively).
- The latest log is selected by filesystem modification time, not by its filename. Equal modification times have no guaranteed tie-breaking order.
- The entire selected log is printed to standard output, with ANSI colors: red for lines containing `[ERROR]`, magenta for `[WARNING]`, and white otherwise. Error coloring takes precedence if both markers occur on a line.
- The command does not accept a filename, count, filtering, or follow/tail argument.
- `--show-logs` takes precedence over `--verbose`, `--help`, `--get-target`, and `--clean-logs`, regardless of argument order. Prefer running it alone.
- It displays existing messages only; it cannot increase the verbosity of an earlier run. Read `../git-stalker-verbose/SKILL.md` if the user needs more detailed logs from a future run.

## Empty logs and failures

- An existing directory without matching log files produces no output and exits successfully. An empty selected file also produces no output.
- A missing or inaccessible log directory can cause the command to fail rather than produce an empty result.
- If the selected file cannot be opened, the command prints `Could not open log file <path>` to standard error but still returns success. Do not rely on the exit status alone to confirm logs were displayed.

Report observed errors and distinguish an empty result from a missing or inaccessible directory. Inspect the actual directory and permissions if needed; do not delete logs or run `--clean-logs` as a troubleshooting step.

Logs can contain repository paths and other diagnostic data. Summarize relevant excerpts rather than exposing unrelated log contents when responding to the user.
