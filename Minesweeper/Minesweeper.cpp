#include "Minesweeper.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
using namespace std;

// Implementing member functions
// default is easy game
Minesweeper::Minesweeper(): m(10), tot(64){
     board_ = vector<vector<int>>(8, vector<int>(8, 0));
     revealed_ = vector<vector<int>>(8, vector<int>(8, 0));
     initialize();
}
// construct easy, intermediate and hard games
// easy game, 8 x 8 grids with 10 mines
// intermediate game, 16 x 16 grids with 40 mines
// hard game, 24 x 24 grids with 99 mines
Minesweeper::Minesweeper(char c) {
      if (c == 'I' || c == 'i') {
          board_ = vector<vector<int>>(16, vector<int>(16, 0));
          revealed_ = vector<vector<int>>(16, vector<int>(16, 0));
          m = 40;
          tot = 256;
      }
      else if (c == 'H' || c == 'h') {
          board_ = vector<vector<int>>(24, vector<int>(24, 0));
          revealed_ = vector<vector<int>>(24, vector<int>(24, 0));
          m = 99;
          tot = 576;
      }
      else {
          board_ = vector<vector<int>>(8, vector<int>(8, 0));
          revealed_ = vector<vector<int>>(8, vector<int>(8, 0));
          m = 10;
          tot = 64;
      }
      initialize();
}
// randomly distribute mines and initialize the board_
// -10 is mine, -k means k mines surrounding
void Minesweeper::initialize () {
      int n = board_.size();
      // put row and column number 
      srand(time(NULL));
      for (int i = 0; i < m;) {
          int k = rand()%(n*n);
          int row = k/n, col = k%n;
          if (board_[row][col] == 0) {
              board_[row][col] = -10;
              i++;
          }
      }
      for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
              if (board_[i][j] == -10) continue;
              int cnt = 0;
              for (int ii = -1; ii <= 1; ii++) {
                  for (int jj = -1; jj <= 1; jj++) {
                       int r = i+ii, c = j+jj;
                       if (r >= 0 && r < n && c >= 0 && c < n && board_[r][c] == -10)
                           cnt++;
                  }
              }
              board_[i][j] = cnt;
           }
      }
} 
// print current revealed board_ after each move
void Minesweeper::print() const {
      int n = board_.size();
      cout << "************************" << endl;
      cout << 0 << ' ' << 0 << ' ';
      for (int i = 0; i < n; i++) 
          cout << i/10 << ' ';
      cout << endl;
      cout << 0 << ' ' << 0 << ' ';
      for (int i = 0; i < n; i++) 
          cout << i%10 << ' ';
      cout << endl;
      for (int i = 0; i < n; i++) {
          cout << i/10 << ' ' << i%10 << ' ';
          for (int j = 0; j < n; j++) {
              if (revealed_[i][j] == 0)
                  cout << ' ' << ' ';
              else if (revealed_[i][j] == 1) 
                  cout << board_[i][j] << ' ';
              else 
                  cout << 'M' << ' ';
          }
          cout << endl;
      }
}
// click a grid of given coordinates; if invalid, do nothing
// When game is over, i.e. win or lose, return false
void Minesweeper::click(int row, int col) { 
      int n = board_.size();
      // invalid or already revealed
      if (row < 0 || row >= n || col < 0 || col >= n || revealed_[row][col]) return;
      if (board_[row][col] == -10) {
          revealed_[row][col] = 2;
          print();
          cout << "Sorry, You Lose :(" << endl;
          exit(1);
      }
      revealed_[row][col] = 1;
      tot--;
      print();
      if (tot == 0) {
          cout << "Congratulations! You Win :)" << endl;
          exit(0);
      }
}

void Minesweeper::mark(int row, int col) {
      if (revealed_[row][col] || m == 0) return;
      revealed_[row][col] = 2;
      tot--;
      m--;
      print();
      if (tot == 0) {
          cout << "Congratulations! You Win :)" << endl;
          exit(0);
      }
}

void Minesweeper::unmark(int row, int col) {
      if (revealed_[row][col] != 2) return;
      revealed_[row][col] = 0;
      tot++;
      m++;
      print();
}

//click 8 coordinates, hopefully no mine 
//BFS: use a queue to keep coordinates to process
//If searching ends in a possible circle or queue empty, perform new random click
void Minesweeper::solverAI() {
     int n = board_.size();
     queue<pair<int, int>> myq;
     vector<vector<int>> pos = {{0, 0}, {0, n-1}, {n-1, 0}, {n-1, n-1}};
     for (auto& p:pos) {
         click(p[0], p[1]);
         myq.push({p[0], p[1]});
     }
     int limit = 2*n, circle = 0;
     while (true) {
         int sz = myq.size(), row, col;
         if (myq.empty()) {
            int i = 0;
            for (i = 0; i < n*n; i++) {
                if (revealed_[i/n][i%n] == 0) break; 
            }
            click(i/n, i%n);
            row = i/n;
            col = i%n;
         }
         else {
             row = myq.front().first;
             col = myq.front().second;
             myq.pop();
         }
         int n1 = 0, n2 = 0; // n1 mines, n2 unrevealed grids
         for (int i = -1; i <= 1; i++) {
              for (int j = -1; j <= 1; j++) {
                  int r = row + i, c = col + j;
                  if (r < 0 || r == n || c < 0 || c == n) continue;
                  if (revealed_[r][c] == 2) 
                      n1++;
                  else if (revealed_[r][c] == 0)
                      n2++; 
              }
         }
         if (board_[row][col] != n1 && board_[row][col] != n1+n2) {
              myq.push({row, col});
         }
         else {
              for (int i = -1; i <= 1; i++) {
                  for (int j = -1; j <= 1; j++) {
                     int r = row + i, c = col + j;
                     if (r < 0 || r == n || c < 0 || c == n) continue;
                     if (revealed_[r][c] == 0) {
                         if (board_[row][col] == n1) {
                             click(r, c);
                             myq.push({r,c});
                         }
                         else {
                             mark(r,c);
                         }
                     }     
                  }
              }
         }
         if (myq.size() == sz) {
             if (++circle == limit) {
                 int i = 0;
                 for (i = 0; i < n*n; i++) {
                     if (revealed_[i/n][i%n] == 0) break; 
                 }
                 click(i/n, i%n);
                 myq.push({i/n, i%n});
                 circle--;
             }
         }
         else 
             circle = 0;
     }
}
