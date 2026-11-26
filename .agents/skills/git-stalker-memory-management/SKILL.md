---
name: git-stalker-memory-management
description: Follow Git-Stalker memory ownership, raw-pointer cleanup, member access, and formatting conventions when modifying C++ code.
---

# Skill: Git-Stalker Memory Management & Style

Use this skill when managing pointers, memory cleanup, member access, namespaces, and code formatting in git-stalker.

## Memory & Style Rules

- **Collections & Pointers**: Manage object collections using `std::vector<Type*>` storing raw pointers.
- **Destructor Cleanup**: Owning classes must explicitly delete child pointers and free external library resources (e.g., `git_commit_free`) in destructors:
  ```cpp
  Repository::~Repository(){
      if(this->get_file_list_size()){
          for(auto file: this->file_list){ delete file; }
      }
      if(this->last_commit != nullptr){ git_commit_free(this->last_commit); }
  }
  ```
- **Member Access**: Always use `this->` explicitly when accessing class members inside methods (`this->repository_name = name;`).
- **Namespaces & Formatting**:
  - Place `using namespace std;` at the top of headers and source files.
  - Use `namespace fs = filesystem;` for `std::filesystem`.
  - Opening braces (`{`) must be placed on the same line as signatures, conditionals, and loops.
  - Indentation: 4 spaces.
