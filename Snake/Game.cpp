#include "Snake.hpp"
#include <iostream>
using namespace std;

int main() {
    char play = 'Y';
    while (play == 'Y' || play == 'y') {
        cout << "Welcome to the Snake Game! Do You Want to Specific a Board Size? Y/N" << endl;
        char c;
        cin >> c;
        int x = 8, y = 10;
        if (c == 'Y' || c == 'y') {
             cout << "Please Input Rows and Columns:" << endl; 
             cin >> x >> y;
             // too big a board
             if (x <= 0 || x > 1000 || y <= 0 || y > 1000) {
                 cout << "Board Size Invalid" << endl;
                 continue;
             }     
        }
        Snake game(x, y);
        game.print();
        while (true) {
             // up, down, left, and right move
             cout << "Please Input Your Next Move, W/S/A/D:" << endl;
             char dir;
             cin >> dir;
             if (!game.move(dir)) {
                 cin >> play;
                 break;
             }
             game.print();
        }
    }
}