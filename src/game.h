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
    /*
     * Konstruktor a destruktor
     */
    Game();
    ~Game();
    /*
     * Vytvoří hrací pole na základě rozměrů zadaných hráčem
     */
    void createBoard();
    /*
     * Zavolá createBoard() pro získání hrací plochy a inicializuje hru jako takovou a vlákna
     */
    void start();
    /*
     * Součástí metody loadCoords()
     * Načte input uživatele z konzole
     * První souřadnici přepíše na int
     * Vrací pair jakožto jednu souřadnici
     */
    pair<size_t, size_t> loadInput(const string &str);
    /*
     * Zkontroluje zda uživatel nechce opustit hru (zadal q) -> hra se ukončí
     * Jinak načte pair vrácený předchozí metoodu a zkontroluje, jestli je souřadnice validní
     * Jestliže ano, poskytně souřadnice metodě play(), jinak nastaví odpovídající hlášku
     */
    pair<size_t, size_t> loadCoords();

    volatile bool isRunning = false;    // udává zda hra běží nebo byla ukončena
private:
    shared_ptr<Board> board;    // hrací plocha
    unique_ptr<Window> window;  // okno pro vykreslování hracího pole a hlášek

    int ply1guesses = 0;    // počet uhádnutí hráče 1
    int ply2guesses = 0;    // počet uhádnutí hráče 2

    int ply = 1;    // aktuální hráč (player1 / player2)
    bool singlePly = true;  // hra (ne)byla navolena jako singleplayer
    vector<Tile> openedCells;   // vektor odhalených karet
    int guessedCells = 0;   // počet karet, kterým se našla dvojice

    mutex mtx;
    condition_variable cvarIncrement;   // cv pro vlákno určené na připočítávání pokusů
    condition_variable cvarRender;  // cv pro vlákno určené na vykreslování hracího pole a hlášek

    /*
     *  Ústřední metoda celé hry
     *  Pokud v předchozím kole aktuální hráč neuhádl dvojici a byl zvolen multiplayer, změní aktuálního hráče
     *  Načte si dvoje souřadnice
     *  Zkontroluje zda se znaky na vybraných souřadnicích shodují
     *  Pokud ne, nastaví hlášku a otočí karty zpět, v opačném případě inkrementuje počet odhalených karet
     *  Jestliže je počet odhalených karet roven rozměrům hracího pole, ohlásí výhru a ukončí hru
     */
    void play();
    /*
     * Doplňková metoda pro renderBoard() ve třídě board
     */
    void render();
    /*
     * Inkrementuje odpovídající proměnnou, jež určuje počet uhádnutí
     */
    void incrementGuesses();
};

#endif //PEXESO_GAME_H