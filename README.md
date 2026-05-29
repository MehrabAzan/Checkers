# Checkers

A simple graphical checkers game written in C++ with SFML. The player controls the white pieces and plays against a black computer opponent that uses minimax with alpha-beta pruning.

## Features

- 8x8 checkers board rendered with SFML
- Human player controls white pieces
- Bot controls black pieces
- Diagonal movement and jump captures
- King promotion when a piece reaches the opposite side
- Basic win detection when one side has no pieces remaining

## Project Structure

```text
.
|-- main.cpp      # SFML window, input handling, turn flow, and win checks
|-- Board.h/.cpp  # Board setup, rendering, movement, captures, and promotion
|-- Piece.h/.cpp  # Piece state and SFML shape drawing
|-- Bot.h/.cpp    # Black-piece AI using minimax and board evaluation
`-- .gitignore
```

## Requirements

- C++17-compatible compiler
- SFML 3.x development libraries
- An `arial.ttf` font file available in the working directory when running the game

The game currently loads the font with:

```cpp
Font font("arial.ttf");
```

If the file is missing, copy a compatible font into the run directory as `arial.ttf` or update `main.cpp` to point to a font that exists on your system.

## Build

This repository does not include a build system yet, so compile all source files together and link SFML.

Example with `g++`:

```sh
g++ -std=c++17 main.cpp Board.cpp Piece.cpp Bot.cpp -o checkers -lsfml-graphics -lsfml-window -lsfml-system
```

If SFML is installed outside your compiler's default search paths, add include and library paths:

```sh
g++ -std=c++17 main.cpp Board.cpp Piece.cpp Bot.cpp -o checkers -I path/to/SFML/include -L path/to/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
```

On Windows, make sure the required SFML DLLs are available next to the executable or on your `PATH`.

## Run

```sh
./checkers
```

On Windows, the executable may be named:

```sh
checkers.exe
```

## How to Play

1. White moves first.
2. Left-click a white piece to select it.
3. Left-click a valid destination square to move it.
4. Move diagonally by one square, or jump diagonally by two squares to capture an opposing piece.
5. The black bot moves automatically after the player makes a valid move.
6. A piece that reaches the opposite end of the board is promoted to a king and shown with a yellow outline.

## Current Notes

- Forced captures and multi-jump turns are not enforced.
- There is no menu, restart button, or score screen.
- A future improvement would be to add a small build system such as CMake.
