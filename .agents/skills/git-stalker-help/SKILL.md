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
- `--get-target F "<file>"`: query a file's stored mapping targets.
- `--get-target r "<repository-name>"`: return the target repository name as stored in JSON.
- `--get-target f "<function-name>"`: return mapped file/function targets, identifying the containing file for a target function.

For target-query examples and result interpretation, read `../git-stalker-get-target/SKILL.md`.

Help prints to standard output and exits without starting the TUI. It still initializes a logfile under `/home/<user>/.gitstalker/gitstalker_logs/`, where `<user>` comes from `USERNAME`, falling back to `USER`.

Options after help are not processed. For the full usage reference, read `../git-stalker-cli/SKILL.md`.
