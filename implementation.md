# Log Sysytem
 - creates a file at each runtime named after the starting timestamp
 - 3 categories:
    - `[<timestamp>] [ERROR]` is for critical errors but that can be overlooked (a repo that wasn't found, a commit that does no exist) or at least not trigger a shutdown.
    - `[<timestamp>] [WARNING]` is for warnings (surprising I know), should be fixed but will not impact the behavior of git-stalker.
    - `[<timestamp>]` is for simple logs.