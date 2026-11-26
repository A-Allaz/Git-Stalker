---
name: git-stalker-storage
description: Write, edit, and validate Git-Stalker JSON mapping storage files using the existing storage.json schema and the ~/.gitstalker/gitstalker_mappings directory convention.
---

# Git-Stalker Mapping Storage

Use this skill when creating or editing persisted repository, file, or function mappings, or changing their serialization code.

## Source of truth

Read `src/storage/storage_handler.cpp` and `src/storage/json_handler.cpp` from the repository root before changing storage behavior. The repository's `storage.json` illustrates the schema, but is a legacy example location, not the destination for new mapping files.

## Location and filenames

- Store JSON files in `~/.gitstalker/gitstalker_mappings/` (a directory, not a single file).
- Create the directory if necessary. Resolve `~` to the user's home directory; do not write a literal tilde into a filesystem path.
- Join repository names in their supplied order with underscores, then append `.json`: `<origin-name>_<target-name>.json`. This matches `save_repositories(vector<Repository*>)`.
- Example: `~/.gitstalker/gitstalker_mappings/deploy-infra_deploy-infra-on-premise.json`.
- Keep the schema used by `storage.json`; the new convention changes the location and filename, not the JSON structure.
- For C++ persistence, use `save_repositories(repositories)` and existing serializers rather than introducing a separate schema or restoring the old filename argument.
- Current C++ code derives the home path as `/home/<USERNAME-or-USER>`; do not confuse that implementation limitation with portable home-directory resolution.

## JSON structure

The root is an object with a `repositories` array. Include both repositories involved in the mapping, with their referenced files and functions so the loader can resolve targets.

Each repository contains:

- `name`: exact repository name.
- `location`: repository filesystem path, normally absolute.
- `last_commit`: actual Git commit OID for that repository. Never fabricate one; the loader looks it up through libgit2.
- `mapped_to`: target repository name, or the string `"NULL"` for no repository mapping.
- `files`: array of file records. Existing serializers may omit this key for repositories with no files.

Each file contains:

- `name`: exact file path used by the application, normally absolute.
- `mapped_to`: array of mapping objects (see below).
- `functions`: array of function records; existing serializers may omit this key for files without functions.

Each function contains:

- `name`: exact function name, without a `FUNC-` prefix.
- `starting_line` and `ending_line`: integer source line positions matching the parsed source.
- `mapped_to`: array of mapping objects.

## Mapping objects

Use the same mapping representation for both file and function sources:

```json
[
    {"name": "FILE-/absolute/path/to/target.ts"},
    {"name": "FUNC-targetFunction", "file_name": "/absolute/path/to/target.ts"}
]
```

- File target: `{"name": "FILE-<exact target file path>"}`.
- Function target: `{"name": "FUNC-<exact function name>", "file_name": "<exact containing file path>"}`. Always include `file_name` to disambiguate functions.
- No mapping: `[{"name": "NULL"}]`. This is a string sentinel, not JSON `null`. Do not mix the sentinel with real mappings.
- Prefixes belong only in mapping references, not in the `name` fields of repository, file, or function records.
- Multiple targets are separate objects in the array. Avoid duplicate entries.
- Mappings are directional. Do not invent reverse mappings; write them only when requested.
- A file/function target must exist in the repository named by its source repository's `mapped_to`. That target repository must be available in the same mapping document for reliable resolution.

## Safe writing and validation

1. Read the existing destination before editing. Preserve unrelated repositories, files, functions, and mappings. `save_repositories` overwrites the destination document; it does not merge it.
2. Confirm repository names, locations, file paths, function names, line positions, and commit IDs against the actual repositories. Obtain a current commit with `git -C <repository-path> rev-parse HEAD` only when a current snapshot is intended; preserve stored commit IDs otherwise.
3. Keep target references consistent with the records in the document. Preserve repository `mapped_to` values unless the requested change requires updating them.
4. Serialize valid JSON using four-space indentation (`json.dump(4)` in the existing C++ writer).
5. For manual edits, validate syntax with `python3 -m json.tool <path-to-json>` and check all references before replacing the original. Prefer a temporary file in the same directory followed by an atomic rename for manual/scripted writes.
6. Do not modify live user storage merely to test this skill. Use temporary fixtures for validation.

When changing serializer or loader code, check round-trip behavior for file-to-file, file-to-function, function-to-file, function-to-function, multiple targets, and unmapped objects. The current loader iterates directory entries without filtering extensions, so keep backups and non-JSON helper files outside the mappings directory.
