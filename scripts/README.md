# Wonkey scripts

- **wake** is a command line tool (CLI) to compile your Wonkey sources
- **wide** is a Wonkey integrated development environment (IDE)

All sources are written in Wonkey and are available in `src` directory.

## `rebuildall.*`

Clean and build all, in order:
- **wake**
- **modules**, in `modules` directory
- **wide**
- **launcher**, rename it to "Wonkey (...)"
- **makedocs**

## `rebuildwake.*` : clean and build **wake**

Clean and build **wake** in release mode to `bin/<host>` directory.

## `rebuildwide.*`: clean and build **wide**

Clean and build **wide** in release mode to `bin/<host>` directory.

## `rebuildlauncher.*`: clean and build **launcher**

Clean and build **launcher** in release mode to root directory.

## `rebuildmods.*` : clean and build **modules**

Clean and build all **modules** in debug and release mode.

## `makedocs.*`: generate sources documentation

Generate sources documentation to `docs` directory.

## Notes

All `update**.*` scripts do the same but don't clean before. it's faster if you don't need to rebuild everything.