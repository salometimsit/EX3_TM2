//timsitmelosa@gmail.com
#include "doctest.h"
#include "Gamelogic/Game.hpp"
#include "Roles/AllRole.hpp"
#include "Actions/AllAction.hpp"
TEST_CASE("Game throws on start with only one player") {
    Game game;
    game.addPlayer("OnlyOne");
    CHECK_THROWS(game.startGame());
}
TEST_CASE("Adding players and starting the game") {
    Game game;
    CHECK_NOTHROW(game.addPlayer("Salome"));
    CHECK_NOTHROW(game.addPlayer("Itay"));
    CHECK_NOTHROW(game.startGame());
    CHECK(game.turn() == "Salome");
}

TEST_CASE("Player with 11 coins must do Coup") {
    Game game;
    game.addPlayer("P1");
    game.addPlayer("P2");
    game.startGame();
    Player* current = game.getCurrentPlayer();
    current->setcoins(11);
    CHECK_THROWS_WITH(game.playTurn(Gather()), "You have more than 10 coins. You must play coup.");
}

TEST_CASE("Coup eliminates player from game") {
    Game game;
    game.addPlayer("A");
    game.addPlayer("B");
    game.startGame();
    Player* current = game.getCurrentPlayer();
    current->setcoins(10);
    Coup coup;
    game.playTurn(coup, 1);  // A עושה coup על B

    CHECK(game.playersList().size() == 1);
    CHECK(game.playersList()[0] == "A");
}

TEST_CASE("Winner is declared correctly") {
    Game game;
    game.addPlayer("Winner");
    game.addPlayer("Loser");
    game.startGame();

    Player* current = game.getCurrentPlayer();
    current->setcoins(10);
    Coup coup;
    game.playTurn(coup, 1);
    CHECK(game.winner() == "Winner");
}

TEST_CASE("Turn rotates correctly (no bribe)") {
    Game game;
    game.addPlayer("A");
    game.addPlayer("B");
    game.startGame();

    Gather gather;
    CHECK(game.turn() == "A");
    game.playTurn(gather);
    CHECK(game.turn() == "B");
    game.playTurn(gather);
    CHECK(game.turn() == "A");
}

TEST_CASE("Bribe grants extra turn") {
    Game game;
    game.addPlayer("A");
    game.addPlayer("B");
    game.startGame();

    Player* current = game.getCurrentPlayer();
    current->setcoins(5);
    Bribe bribe;
    game.playTurn(bribe);

    // לא עובר לשחקן הבא עדיין
    CHECK(game.turn() == "A");
    game.playTurn(Gather());
    CHECK(game.turn() == "A");
    game.playTurn(Gather());
    CHECK(game.turn() == "B");
}
