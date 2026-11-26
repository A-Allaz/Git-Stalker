---
name: git-stalker-structure
description: Follow Git-Stalker file organization, header and source separation, include paths, and header-guard conventions when organizing C++ code.
---

# Skill: Git-Stalker Code Structure & Repartition

Use this skill when organizing files, defining headers/source separation, header guards, and include paths for git-stalker.

## Guidelines

- **Repartition**:
  - Headers (`include/`): All class and function declarations. Must mirror the exact directory structure of `src/`.
  - Sources (`src/`): All implementations and method definitions.
- **Header Guards**:
  - Wrap every header and source file in standard preprocessor guards using uppercase with double underscores:
    ```cpp
    #ifndef __FILENAME_H__
    #define __FILENAME_H__

    // ... declarations ...

    #endif
    ```
  - Source `.cpp` files also follow this convention (`#ifndef __FILENAME_CPP__`).
- **Includes**:
  - Use angle brackets (`<>`) with paths relative to include roots (e.g., `#include <utils/logger.h>`, `#include <repository/repository.h>`).
