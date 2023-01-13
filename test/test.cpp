#include "../src/game.h"
#include "catch.hpp"


TEST_CASE("Terminating game", "[Game]") {
    SECTION("Inserting q as coord terminates program") {
        Game g;
        auto coo = g.loadInput("1 2");
        REQUIRE(coo.first == 1);
        REQUIRE(coo.second == 2);
        REQUIRE(g.isRunning);
    }
}