#ifndef PEXESO_BOARD_H
#define PEXESO_BOARD_H

#include <ostream>
#include <vector>

using namespace std;
using Tile = pair<bool, char>;

class Board {
public:
    Board(size_t width, size_t height, size_t seed = 0);
    ~Board();

    size_t getWidth() const;
    size_t getHeight() const;
    const Tile& getTile(size_t x, size_t y) const;
    const Tile& getTile(pair<size_t, size_t> coords) const;

    void openCell(size_t x, size_t y);
    void openCell(pair<size_t, size_t> coords);
    void closeCell(size_t x, size_t y);
    void closeCell(pair<size_t, size_t> coords);

private:
    size_t width, height;
    vector<vector<Tile>> cells;

};

#endif //PEXESO_BOARD_H
