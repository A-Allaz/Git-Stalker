# Git-Stalker
GIT-STALKER is a git tracker made to identify and sort in chronological order the changes made in a given git repository "REPO A", and map them to an other repository "REPO B" allowing to maintain both repository without a need for a fork or other duplication method. This also allows for 2 ethods in the repos, with different names but same logic to be mapped to each other

# Supported Languages

## Typescript

# TO-DO
 - [x] File class: name, mapped_to file (optional)
 - [x] Function class: name, file, origin, mapped_to (optional), starting line, ending line

 - [ ] CLI interface: selecting repos (scanning file system), mapping interface (GIT-STALKER parses the repos and propose a mapping interface in the CLI) 
 - [ ] Mapping data structure and file extension (one mapping file per origin file)
 - [ ] History (storage) system

# UI inputs
 - When starting, Git-Stalker must suggest to go back to previous work (2 repos already mapped to one another)
 - Selecting repose: Git-Stalker look in the file tree for git repos -> show them to the user -> user selects source repo (A) -> user select target repo (B) -> Git stalker mapps them to one  an other and enter mapping configuration.
 - Parses function names -> select a function in repo A -> select an element in repo B -> maps fun(A) to elem(B)
 - Blocks are first to be selected manually (live selection in the interface would be too much work) with entry and end line numbers.
