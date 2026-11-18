# Skill: Git-Stalker Naming Conventions

Use this skill when naming variables, functions, classes, enums, and constants in git-stalker.

## Naming Rules

- **Variables & Function Parameters**: `snake_case` 
  *Examples:* `repository_name`, `available_repositories`, `loaded_repositories`, `file_list`, `last_commit`.
- **Functions & Methods**: `snake_case` 
  *Examples:* `update_last_commit`, `parse_repositories`, `load_repositories`, `select_repositories`, `build_log_timestamp`.
- **Classes & Structs**: PascalCase / Capitalized 
  *Examples:* `Repository`, `File`, `Function`, `RepositoryParser`.
- **Enums**: PascalCase for enum types (`Status`), UPPER_CASE for enum values (`NEW`, `STABLE`, `CHANGED`, `DELETED`).
- **Constants & Header Guards**: UPPER_CASE with double underscores (`__REPOSITORY_H__`).
