#ifndef PEXESO_GAME_H
#define PEXESO_GAME_H

#include <ostream>
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "board.h"
#include "window.h"

using namespace std;


class Game {
public:
    Game();
    ~Game();

    void createBoard();
    void start();

    pair<size_t, size_t> loadInput(const string &str);
    pair<size_t, size_t> loadCoords();

    volatile bool isRunning = false;
private:
    //void openCell(char x, int y);

    shared_ptr<Board> board;
    unique_ptr<Window> window;
    //ostream &outputStream;     // odkaz na vystupni proud (std::cout)
    string text;               // text vypisovany pod hraci plochou

    int guesses = 0;
    int guesses2 = 0;

    int ply = 1;
    bool singlePly = true;
    vector<Tile> openedCells;
    int guessedCells = 0;

    mutex mtx;
    condition_variable cvarIncrement;
    condition_variable cvarRender;


    void play();
    void render();
    void incrementGuesses();
};

#endif //PEXESO_GAME_H
