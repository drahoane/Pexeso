#ifndef PEXESO_WINDOW_H
#define PEXESO_WINDOW_H

#include <memory>
#include <iostream>
#include "board.h"

using namespace std;

#define RESET "\x1B[m"   // reset barev
#define BLUE "\x1B[94m" // modrá barva pro karty
#define TXT "\x1B[38;5;208m"    // zlatá barva pro hlášky

class Window {
public:
    /*
     * Konstruktor a destruktor
     */
    Window(shared_ptr<Board>& board);
    ~Window();
    /*
     * Odtraní předchozí výpis z konzole
     * Vykreslí aktuální hrací pole
     */
    void renderBoard();
    /*
     * Nastavení hlášky
     */
    void setAnnouncement(const string &str);

    string announcement;    // hláška

private:
    shared_ptr<Board> board;    // hrací pole
};



#endif //PEXESO_WINDOW_H