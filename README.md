# Games

Implemented Command Line Based Games in C++ (MineSweeper and Snake game)

Designed an AI minesweeper solver (well handle intermediate level)

In Minesweeper game, two 2D vectors are used to hold game board and state. In constructor, mine positions in the game board are initialized by random number generator, other grids are filled with the count of surrounding mines. It has member functions of click, mark and unmark when a coordinate is given. 

The AI minesweeper solver is implemented using BFS, which compares the value of each grid with the count of marked mines and unrevealed grids surrounding it. If no process after a certain amount of iteration (double board size), click a new grid. 
