# Git-Stalker
GIT-STALKER is a git tracker made to identify and sort in chronological order the changes made in a given git repository "REPO A", and map them to an other repository "REPO B" allowing to maintain both repository without a need for a fork or other duplication method. This also allows for 2 ethods in the repos, with different names but same logic to be mapped to each other

# TO-DO
 - [ ] File class: name, mapped_to file (optional)
 - [ ] Instruction class: file, line, mapped_to line (optional)
 - [ ] Block class: starting line, ending line, instruction array
 - [ ] Function class: name, file, origin, mapped_to (optional), starting line, ending line, instructions array (sorted) and/or block array (sorted)

 - [ ] CLI interface: selecting repos (scanning file system), mapping interface (GIT-STALKER parses the repos and propose a mapping interface in the CLI) 
 - [ ] Mapping data structure and file extension (one mapping file per origin file)
 - [ ] History (storage) system