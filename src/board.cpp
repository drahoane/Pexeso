#include "board.h"
#include <random>
#include <iostream>


Board::Board(size_t height, size_t width, size_t seed)
        : height(height), width(width)
{
    std::random_device dev;
    mt19937 generator(seed ? seed : dev()); // seed the generator
    uniform_int_distribution<> range4postX(0, height-1); // define the range
    uniform_int_distribution<> range4postY(0, width-1); // define the range

    vector<pair<bool, char>> row;

    cells = vector<vector<pair<bool, char>>>(height, vector<pair<bool, char>>(width));

    char value = 33;
    int counter = 0;
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            cells[i][j].second = value;
            if (++counter % 2 == 0)
                value++;
        }
    }

    int postX = range4postX(generator);     // generate numbers
    int postY = range4postY(generator);     // generate numbers

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            swap(cells[postX][postY].second, cells[i][j].second);
            postX = range4postX(generator);
            postY = range4postY(generator);

        }
    }
}

Board::~Board() = default;

size_t Board::getWidth() const {
    return width;
}

size_t Board::getHeight() const {
    return height;
}

const Tile &Board::getTile(size_t x, size_t y) const {
    if (x >= height || y >= width)
        throw std::out_of_range("Out of range!");
    return cells[x][y];
}

const Tile &Board::getTile(pair<size_t, size_t> coords) const {
    return getTile(coords.first, coords.second);
}

void Board::openCell(size_t x, size_t y) {
    if (x >= height || y >= width)
        throw std::out_of_range("Out of range!");
    cells[x][y].first = true;
}

void Board::openCell(pair<size_t, size_t> coords) {
    openCell(coords.first, coords.second);
}

void Board::closeCell(size_t x, size_t y) {
    if (x >= height || y >= width)
        throw std::out_of_range("Out of range!");
    cells[x][y].first = false;
}

void Board::closeCell(pair<size_t, size_t> coords) {
    closeCell(coords.first, coords.second);
}
