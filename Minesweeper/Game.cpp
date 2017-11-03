#include "Minesweeper.hpp"
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    // Initialize a game
    cout << "************************" << endl;
    cout << "Welcome! Do You Want Easy, Intermediate or Hard E/I/H?" << endl;
    string input;
    getline(cin,input);
    istringstream iss(input);
    char c;
    if (iss >> c) {
        Minesweeper game(c);
        game.print();
        cout << "Do You Want to Try AI Solver? Y/N" << endl;
        getline(cin,input);
        istringstream iss(input);
        char c;
        if (iss >> c && (c == 'Y' || c == 'y')) {
            game.solverAI();
        }
        while (true) {
            // Input a position. If invalid, nothing changes 
            cout << "Please Input An Coordinate" << endl;
            getline(cin,input);
            istringstream iss(input);
            int row, col;
            if (iss >> row >> col) {
                cout << "Do You Want Click, Mark or UnMark C/M/U?" << endl;
                char c;
                getline(cin,input);
                istringstream iss(input);
                if (iss >> c) {
                    if (c == 'C' || c == 'c')
                       game.click(row, col);
                    else if (c == 'M' || c == 'm')
                       game.mark(row, col);
                    else if (c == 'U' || c == 'u')
                       game.unmark(row, col);
                }
            }
        }
    }
}