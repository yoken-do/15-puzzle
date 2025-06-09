


## 15-puzzle

A fully customizable version of the "15-Puzzle" game.

## Installation

1. **Clone the repository**
```bash
git clone https://github.com/yoken-do/15-puzzle.git
cd 15-puzzle
```

2. **Create the** `sessions/` **directory (required for saving game states)**
```bash
mkdir sessions
```

3. **Compile the project**

Run `./compile.bat` to install.

**Note:** If you run `./compile.bat` without modifications, the project will compile into `./test.exe`.

## Game Modes

**Standard Mode:**

Run the program from the command line without arguments.

Example: `test.exe`

**Backward Mode:**

Run the program with the -backward flag.

Example: `test.exe -backward`

**Custom Map Mode:**

Run the program with the map name as an argument.

Example: `test.exe planets`

**Backward Mode with Custom Map:**

Run the program with both the map name and the -backward flag.

Example: `test.exe planets -backward`

## Controls
**WASD** or **Arrow Keys** - move the empty tile

**N** - undo a move (Backward mode only)

**Q** - quit the game

**ESC** - show help

