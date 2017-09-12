#ifndef MINESWEEPER_HPP_
#define MINESWEEPER_HPP_
#include <vector> 
using namespace std;
// Class for the Minesweeper Game.
class Minesweeper {
public:
  Minesweeper();
  // initialize an easy, intermediate or hard game
  Minesweeper(char c); 
  void initialize();
  void print() const; 
  bool click(int row, int col);
private:
    // board_ for numbers and mine, revealed_ for whether a grid is revealed 
    // m is total mine count, and tot is total unrevealed non-mine grids
    // The player wins when tot == 0;
    vector<vector<char>> board_;
    vector<vector<int>> revealed_;
    int m = 10, tot = 0;
};
#endif