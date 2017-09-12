#include "Minesweeper.hpp"
#include <iostream>
using namespace std;

int main() {
    char play = 'Y';
    // Allow continuous replays
    while (play == 'Y') {
        // Initialize a game
        cout << "************************" << endl;
        cout << "Welcome! Do You Want Easy, Intermediate or Hard E/I/H?" << endl;
        char c;
        cin >> c;
        Minesweeper game(c);
        game.initialize();
        game.print();
        while (true) {
            // Click a position. If invalid, nothing changes 
            cout << "Please Input An Coordinate" << endl;
            int row, col;
            cin >> row >> col;
            // Check whether game is over, i.e. win or lose
            if (!game.click(row, col)) {
                cin >> play;
                break;
            }
            game.print();
        }
    }
}