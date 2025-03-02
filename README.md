# Minesweeper

## Project Description

Minesweeper is a classic logic game where the player must uncover all the tiles on the board that do not contain mines. The game is written in C++ using the SFML library for handling graphics and events.

## System Requirements

- C++ Compiler
- SFML library (version 2.6.1 or newer)

## Features

- **Main Menu**: Allows selecting the difficulty level (easy, medium, extreme, custom).
- **Gameplay**: Uncovering tiles, marking mines with flags, and resetting the game.
- **Custom Settings**: Allows the user to define the board width, height, and number of mines.

## Why This Decomposition?

The project is divided into the following classes: `Game`, `Board`, `Field`, `Menu`, and `CustomSettings` to improve code organization and manage game functionality more efficiently:

- **Game**: Handles the main game logic, user interaction, and rendering. This class also manages user inputs like mouse clicks and updates the game state.
- **Board**: Represents the game board, manages mines, and tracks tile states. It stores the state of each cell, handles mine generation, and calculates the number of adjacent mines.
- **Field**: Represents a single tile on the board, storing information about its state (mine, flag, uncovered). It tracks whether a tile contains a mine, is flagged, is uncovered, and the number of adjacent mines.
- **Menu**: Provides the user interface for selecting game settings. It handles the display of the main menu and processes the user's difficulty selection.
- **CustomSettings**: Allows users to define custom game settings. It provides options for the board's width, height, and number of mines.

## Computational Logic

### `Board` Class

#### Key Methods:

- **void RevealField(int y, int x) noexcept**: Reveals the tile at the given coordinates. If the tile contains a mine, the game is marked as lost and all mines are revealed. If the tile has no adjacent mines, neighboring tiles are revealed recursively.

- **void GenerateMines(int y, int x) noexcept**: Randomly places mines on the board while avoiding the area around the first click to ensure a safe start for the player.

- **void CalculateAdjacentMines() noexcept**: Calculates the number of adjacent mines for each tile by iterating through the board and incrementing mine counters for neighboring cells.

- **void RevealAdjacentFields(int y, int x) noexcept**: Recursively reveals neighboring tiles for a tile with no adjacent mines.

- **void RevealBombs() noexcept**: Reveals all mines on the board, usually triggered when the game is lost to show the player the mine locations.

### `Game` Class

The `Game` class operates on two vectors: a logical one stored in the `Board` class and a graphical one responsible for rendering.

#### Key Methods:

- **void handleMouseEvent(sf::Event event)**: Processes mouse events such as clicks, identifies which tile was clicked, and performs the corresponding actions (e.g., uncovering a tile or placing a flag).

- **void draw()**: Renders all game elements, including the board, flag counter, timer, and the game state emoji.

- **void leftClick(int y, int x)**: Handles left mouse clicks on a tile at coordinates (y, x). It uncovers the tile and, if it's the first click, triggers mine generation.

- **void rightClick(int y, int x)**: Handles right mouse clicks on a tile at coordinates (y, x), toggling a flag on or off.

- **void gameOver(int y, int x)**: Marks the game as lost, reveals all mines, and displays incorrectly flagged tiles. It also updates the emoji to indicate the player lost.

- **void wonGame(int y, int x)**: Marks the game as won, places flags on all mines, and updates the emoji to a winning face.

## Unit Testing

The project includes unit tests implemented using the Google Test framework. The tests cover:

- The `CustomSettings` class constructor.
- Input handling for the `CustomSettings` class.
- The `Menu` class constructor.
- Input handling for the `Menu` class.

## Authors

The project was created by Adrian Garbowski (@AdrianeQQ) and Tobiasz Kownacki as part of the Object-Oriented Programming course.


