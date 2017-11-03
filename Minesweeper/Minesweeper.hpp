#ifndef MINESWEEPER_HPP_
#define MINESWEEPER_HPP_
#include <vector> 
// Class for the Minesweeper Game.
class Minesweeper {
public:
  Minesweeper();
  // initialize an easy, intermediate or hard game
  Minesweeper(char c); 
  void initialize();
  void print() const; 
  void click(int row, int col);
  void mark(int row, int col);
  void unmark(int row, int col);
  void solverAI();
private:
    // board_ for numbers and mine, 
    // revealed_ for whether a grid has been explored 
    // m is total mine count, and tot is total grids
    // The player wins when tot == 0;
    std::vector<std::vector<int>> board_;
    std::vector<std::vector<int>> revealed_;
    int m = 10, tot = 0;
};
#endif