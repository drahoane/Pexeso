#include "game.h"

#include <iostream>
#include <istream>
#include <sstream>
#include <thread>
#include <mutex>

#define CHANGE_PLAYER(p) p == 1 ? 2 : 1

using namespace std;


Game::Game() = default;

Game::~Game() = default;

void Game::createBoard() {
    cout << "      :::::::::  :::::::::: :::    ::: :::::::::: ::::::::   :::::::: " << "\n";
    cout << "     :+:    :+: :+:        :+:    :+: :+:       :+:    :+: :+:    :+: " << "\n";
    cout << "    +:+    +:+ +:+         +:+  +:+  +:+       +:+        +:+    +:+  " << "\n";
    cout << "   +#++:++#+  +#++:++#     +#++:+   +#++:++#  +#++:++#++ +#+    +:+   " << "\n";
    cout << "  +#+        +#+         +#+  +#+  +#+              +#+ +#+    +#+    " << "\n";
    cout << " #+#        #+#        #+#    #+# #+#       #+#    #+# #+#    #+#     " << "\n";
    cout << "###        ########## ###    ### ########## ########   ########       " << "\n";
    cout << "\n";

    while (true) {
        size_t x = 0, y = 0, z = 0, w = 0;
        string str;

        cout << "Number of players (max 2): " << endl;
        getline(cin, str);
        if (!isdigit(str[0])) {
            cout << "Invalid input" << endl;
            continue;
        }
        w = stoul(str);
        w == 2 ? singlePly = false : singlePly = true;

        cout << "Height: " << endl;
        getline(cin, str);
        if (!isdigit(str[0])) {
            cout << "Invalid input" << endl;
            continue;
        }
        x = stoul(str);
        cout << "Width: " << endl;
        getline(cin, str);
        if (!isdigit(str[0])) {
            cout << "Invalid input" << endl;
            continue;
        }
        y = stoul(str);
        cout << "Seed: " << endl;
        getline(cin, str);
        if (!isdigit(str[0])) {
            cout << "Invalid input" << endl;
            continue;
        }
        z = stoul(str);

        if ((x * y) % 2 == 0 && !(x == 0 || y == 0) && (x*y <= 30)) {
            board = make_shared<Board>(x, y, z);
            return;
        }

        cout << "Size of the board needs to be divisible by 2, less than 30 and not 0" << endl;
    }
}

void Game::start() {
    createBoard();
    window = make_unique<Window>(board);
    isRunning = true;

    std::thread t1(&Game::render, this);
    std::thread t2(&Game::play, this);
    std::thread t3(&Game::incrementGuesses, this);

    t1.join();
    t2.join();
    t3.join();
}

void Game::play() {
    while (isRunning) {
        unique_lock<std::mutex> lg(mtx);
        lg.unlock();

        if (!singlePly && window->announcement != "It's a match")
            ply = CHANGE_PLAYER(ply);

        auto coords1 = loadCoords();
        if(coords1.first == -1)
            break;
        board->openCell(coords1);
        auto coords2 = loadCoords();
        if(coords2.first == -1)
            break;
        board->openCell(coords2);

        if (board->getTile(coords1).second != board->getTile(coords2).second) {
            window->setAnnouncement("Try again");
            cvarRender.notify_one();
            this_thread::sleep_for(std::chrono::seconds(3));
            board->closeCell(coords1);
            board->closeCell(coords2);
        } else {
            window->setAnnouncement("It's a match");
            cvarRender.notify_one();
            this_thread::sleep_for(std::chrono::seconds(3));
            guessedCells += 2;
            if (guessedCells == (board->getWidth()*board->getHeight())) {
                window->setAnnouncement("You have won");
                cvarRender.notify_one();
                this_thread::sleep_for(std::chrono::seconds(1));
                !singlePly ? window->setAnnouncement("Player 1 had " + to_string(ply1guesses) + " guesses\n" "Player 2 had" + to_string(ply2guesses) + " guesses") : window->setAnnouncement("It took you " + to_string(ply1guesses) + " guesses to finish");
                this_thread::sleep_for(std::chrono::seconds(1));
                isRunning = false;
            }
        }
        cvarRender.notify_one();
    }
    cvarRender.notify_all();
    cvarIncrement.notify_all();
}

pair<size_t, size_t> Game::loadInput(const string &str) {
    stringstream ss(str);
    char x = 0;
    int y = 0;
    ss >> x;
    ss >> y;
    x -= 65;
    return {x, y};
}

pair<size_t, size_t> Game::loadCoords() {
    window->setAnnouncement("Insert coords");
    cvarRender.notify_one();
    while (isRunning) {
        string str;
        getline(cin, str);
        if (str == "q") {
            isRunning = false;
            cvarRender.notify_all();
            cvarIncrement.notify_all();
            return {-1, -1};
        }
        auto coords = loadInput(str);
        if (coords.first < board->getHeight() && coords.second < board->getWidth()) {
            if (!board->getTile(coords).first) {
                cvarIncrement.notify_one();
                return coords;
            }
            window->setAnnouncement("Cell is already opened, try again");
            cvarRender.notify_one();
        } else {
            window->setAnnouncement("Invalid coordinates, try again");
            cvarRender.notify_one();
        }
        cvarIncrement.notify_one();
    }
    return {-1, -1};
}

void Game::render() {
    while (isRunning) {
        unique_lock<std::mutex> lg(mtx);
        cvarRender.wait(lg);
        window->renderBoard();
    }
}

void Game::incrementGuesses() {
    while (isRunning) {
        unique_lock<std::mutex> lg(mtx);
        cvarIncrement.wait(lg);
        ply == 1 ? ply1guesses++ : ply2guesses++;
    }
}