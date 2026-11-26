---
name: git-stalker-help
description: Display or explain git-stalker --help and -h. Use when the user wants built-in terminal help without starting the interactive UI.
---

# Display CLI help

Run:

```bash
git-stalker --help
# Equivalent:
git-stalker -h
```

If the command is unavailable but a built binary exists in the project root, use `./git-stalker --help`. Do not rebuild or install without a request.

Explain the available options and all three supported target modes:

- `--verbose X`: log verbosity from 0 to 2.
- `--clean-logs`: delete application logs.
- `--show-logs`: display the latest existing log.
- `--get-target F "<file>"`: query a file's stored mapping targets.
- `--get-target r "<repository-path>"`: query the mapped target repository's path.
- `--get-target f "<file>" "<function-name>"`: query a function's mapped file/function targets, identifying the containing file for a target function.

For target-query examples and result interpretation, read `../git-stalker-get-target/SKILL.md`.

Help prints to standard output and exits without starting the TUI. Running help can create a log under `/home/<user>/.gitstalker/gitstalker_logs/`, where `<user>` comes from `USERNAME`, falling back to `USER`.

Run help on its own: `--show-logs` takes precedence over help, and combining actions can prevent help from being displayed. Some versions may omit `--show-logs` from the help text. For the full usage reference, read `../git-stalker-cli/SKILL.md`.
