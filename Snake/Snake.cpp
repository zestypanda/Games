#include "Snake.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
using namespace std;

Snake::Snake() {
    board_ = vector<vector<char>>(m_, vector<char>(n_, ' '));
    board_[0][0] = '2';
    body_.push({0,0});
    next_food();
}

Snake::Snake(int r, int c): m_(r), n_(c), len_(1){
    board_ = vector<vector<char>>(m_, vector<char>(n_, ' '));
    board_[0][0] = '2';
    body_.push({0,0});
    next_food();
}

inline void Snake::print() {
    cout << "*****************" << endl;
    for (int i = 0; i < m_; i++) {
        for (int j = 0; j < n_; j++) 
             cout << board_[i][j] << ' ';
        cout << '*' << endl;
    }
    cout << "*****************" << endl;
}

bool Snake::move (char c) {
    int dz = 0, dx = 0;
    if (c == 'w' || c == 'W')
        dz = -1;
    else if (c == 's' || c == 'S')
        dz = 1;
    else if (c == 'a' || c == 'A')
        dx = -1;
    else if (c == 'd' || c == 'D')
        dx = 1;
    else
        return true;
    int row = body_.back().first, col = body_.back().second;
    row += dz;
    col += dx;
    // snake hits the wall or itself
    if (row < 0 || row >= m_ || col < 0 || col >= n_ || (board_[row][col] == '1' && body_.front() != make_pair(row, col))) {
        print();
        cout << "Sorry, You Lose! Do You Want To Replay? Y/N" << endl;
        return false;
    }
    // update snake body and head after eating food
    else if (board_[row][col] == 'F') {
        body_.push({row, col});
        board_[row-dz][col-dx] = '1';
        board_[row][col] = '2';
        len_++;
        if (len_ == m_*n_) {
            print();
            cout << "Congratulations, You Win! Do You Want To Replay? Y/N" << endl;
            return false;
        }
        next_food();
    }
    // update snake
    else {
        int r0 = body_.front().first, c0 = body_.front().second;
        body_.pop();
        board_[r0][c0] = ' ';
        if (board_[row-dz][col-dx] != ' ') board_[row-dz][col-dx] = '1';
        body_.push({row, col});
        board_[row][col] = '2';
    }   
    return true;
}

void Snake::next_food() {
    srand(time(NULL));
    while (true) {
       int k = rand()%(m_*n_), r = k/n_, c = k%n_;
       if (board_[r][c] != '1') {
           board_[r][c] = 'F';
           break;
       }    
    }
}