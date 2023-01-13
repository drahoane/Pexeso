#ifndef PEXESO_WINDOW_H
#define PEXESO_WINDOW_H

#include <memory>
#include <iostream>
#include "board.h"

using namespace std;

#define RESET "\x1B[m"   // reset barev
#define BLUE "\x1B[94m"
#define WIN "\x1B[38;5;208m"

class Window {
public:
    Window(shared_ptr<Board>& board);
    ~Window();

    void renderBoard();
    void setAnnouncement(const string &str);

    string announcement;

private:
    shared_ptr<Board> board;
};



#endif //PEXESO_WINDOW_H
