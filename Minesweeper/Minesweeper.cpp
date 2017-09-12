#include "Minesweeper.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Implementing member functions
// default is easy game
Minesweeper::Minesweeper(): m(10), tot(54){
     board_ = vector<vector<char>>(10, vector<char>(10, ' '));
     revealed_ = vector<vector<int>>(10, vector<int>(10, 0));
}
// construct easy, intermediate and hard games
// easy game, 8 x 8 grids with 10 mines
// intermediate game, 16 x 16 grids with 40 mines
// hard game, 24 x 24 grids with 99 mines
Minesweeper::Minesweeper(char c) {
      if (c == 'I') {
          board_ = vector<vector<char>>(18, vector<char>(18, ' '));
          revealed_ = vector<vector<int>>(18, vector<int>(18, 0));
          m = 40;
          tot = 156;
      }
      else if (c == 'H') {
          board_ = vector<vector<char>>(26, vector<char>(26, ' '));
          revealed_ = vector<vector<int>>(26, vector<int>(26, 0));
          m = 99;
          tot = 477;
      }
      else {
          board_ = vector<vector<char>>(10, vector<char>(10, ' '));
          revealed_ = vector<vector<int>>(10, vector<int>(10, 0));
          m = 10;
          tot = 54;
      }
}
// randomly distribute mines and initialize the board_
void Minesweeper::initialize () {
     int n = board_.size();
      int cnt = 1;
      for (int j = 2; j < n; j++) {
          board_[0][j] = '0' + cnt/10;
          board_[1][j] = '0' + cnt%10;
          board_[j][0] = '0' + cnt/10;
          board_[j][1] = '0' + cnt%10; 
          cnt++;
      }
      for (int i = 0; i < 2; i++) {
          for (int j = 0; j < n; j++) {
              revealed_[i][j] = 1;
              revealed_[j][i] = 1;
          }
      }
      n -= 2;
      srand(time(NULL));
      for (int i = 0; i < m;) {
          int k = rand()%(n*n);
          int row = k/n, col = k%n;
          if (board_[row+2][col+2] == ' ') {
              board_[row+2][col+2] = 'M';
              i++;
          }
      }
      for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
              if (board_[i+2][j+2] == 'M') continue;
              int cnt = 0;
              for (int ii = -1; ii <= 1; ii++) {
                  for (int jj = -1; jj <= 1; jj++) {
                       int r = i+ii, c = j+jj;
                       if (r >= 0 && r < n && c >= 0 && c < n && board_[r+2][c+2] == 'M')
                           cnt++;
                  }
              }
              board_[i+2][j+2] = cnt? '0'+cnt : 'B';
           }
      }
} 
// print current revealed board_ after each move
void Minesweeper::print() const {
      int n = board_.size();
      cout << "************************" << endl;
      for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
              if (revealed_[i][j]) 
                  cout << board_[i][j] <<  ' ';
              else
                  cout << 'E' << ' ';
          }
          cout << endl;
      }
}
// click a grid of given coordinates; if invalid, do nothing
// if no mines surrounding the grid, recursively click neighbors
// When game is over, i.e. win or lose, return false
bool Minesweeper::click(int row, int col) { 
      int n = board_.size();
      // invalid or already revealed
      if (row <= 0 || row > n-2 || col <= 0 || col > n-2 || revealed_[row+1][col+1]) return true;
      row++;
      col++;
      revealed_[row][col] = 1;
      tot--;
      if (board_[row][col] == 'M') {
          print();
          cout << "Sorry, You Lose. Replay Y/N?" << endl;
          return false;
      }
      else if (board_[row][col] == 'B') {
          for (int i = -2; i <= 0; i++) {
              for (int j = -2; j <= 0; j++) {
                   click(row+i, col+j);
              }
          }
      }
      if (tot == 0) {
          print();
          cout << "Congratulations! You Win. Replay Y/N?" << endl;
          return false;
      }
      return true;
}