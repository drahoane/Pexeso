#include "window.h"

#include <sstream>
#include <thread>

using namespace std;


Window::Window(shared_ptr<Board>& board) :
        board(board) {}

Window::~Window() = default;


void Window::renderBoard() {
    cout << "\x1B[H" << flush;
    cout << "\x1B[J" << flush;
    cout << "\x1B[H" << flush;

    for (int i = 0; i < board->getWidth(); i++) {
        cout << "\t" << i;
    }
    cout << "\n\r";


    char rowCoord = 'A';

    for (int i = 0; i < board->getHeight(); i++) {
        cout << rowCoord;
        for (int j = 0; j < board->getWidth(); j++) {
            if (board->getTile(i, j).first)
                cout << "\t" << board->getTile(i, j).second;
            else
                cout << "\t" << BLUE << '@' << RESET;
        }
        rowCoord++;
        cout << "\n\r";
    }
    cout << TXT << announcement << "\n\r" << RESET;
    cout << "> " << flush;
}

void Window::setAnnouncement(const string &str) {
    announcement = str;
}