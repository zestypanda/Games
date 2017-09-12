#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Snake {
public:
    Snake();
    Snake(int r, int c); 
    void print(); // print current board_
    bool move(char c); // move the snake
    void next_food(); // randomly put a food
private:
    // board_ with '2' as snake head, '1' as snake body, 'F' as food
    // body_ is the positions of snake body
    vector<vector<char>> board_;
    queue<pair<int,int>> body_;
    int m_ = 8, n_= 10, len_ = 1;
};

#endif