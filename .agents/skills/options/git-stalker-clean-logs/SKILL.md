---
name: git-stalker-clean-logs
description: Safely use git-stalker --clean-logs to delete application log files. Use when the user explicitly requests log cleanup or asks what the cleanup command removes.
---

# Clean application logs

This is a destructive operation. Explain its scope before running it. Run it only when the user has requested log deletion; if their intent is ambiguous, ask for confirmation. Preserve relevant diagnostic logs first if the user still needs them.

```bash
git-stalker --clean-logs
```

If using the built binary in the project root rather than an installed command:

```bash
./git-stalker --clean-logs
```

The command recursively removes:

```text
/home/<user>/.gitstalker/gitstalker_logs/
```

`<user>` comes from `USERNAME`, falling back to `USER`. This is not derived from `HOME` or XDG variables.

- This removes all application logs, not just old ones.
- It does not intentionally remove mapping files in the sibling `gitstalker_mappings/` directory or modify Git repositories.
- Do not rely on a persistent cleanup log being left behind.
- Run cleanup as a standalone command. It exits after cleanup; combining it with `--show-logs` displays logs instead of deleting them.
- Do not replace the command with a broad deletion of `.gitstalker/`; that would also remove mapping data.

Report the exit status and any observed errors. If cleanup fails, investigate the actual directory and permissions rather than escalating to a broader deletion.
