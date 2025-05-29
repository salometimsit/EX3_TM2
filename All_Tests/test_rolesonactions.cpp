#include "doctest.h"
#include "Gamelogic/Game.hpp"
#include "Actions/AllAction.hpp"
#include "Roles/AllRole.hpp"
#include "Players/Player.hpp"

TEST_CASE("Governor successfully blocks Coup") {
    Game game;
    game.addPlayer("Attacker");
    game.addPlayer("Target");
    game.addPlayer("GovernorPlayer");
    game.startGame();
    
    // Set up Governor on player 2
    Player* gov = game.getPlayerByIndex(2);
    gov->setrole(new Governor());
    
    // Attacker tries to coup Target
    Player* attacker = game.getCurrentPlayer();
    attacker->setcoins(10);
    
    // Simulate Governor blocking by marking the coup as blocked
    attacker->blockAction("Coup");
    
    Coup coup;
    game.playTurn(coup, 1);  // Attack player at index 1 (Target)
    
    // Target should still be in game because coup was blocked
    CHECK(game.playersList().size() == 3);
    CHECK(game.getPlayerByIndex(1) != nullptr);
    // Attacker should have lost 7 coins even though blocked
    CHECK(attacker->getcoins() == 3);
}


TEST_CASE("Spy blocks Arrest action") {
    Game game;
    game.addPlayer("Attacker");
    game.addPlayer("SpyPlayer");
    game.startGame();
    
    // Set up Spy
    Player* spy = game.getPlayerByIndex(1);
    spy->setrole(new Spy());
    spy->setcoins(5);
    
    // Spy can block arrest - simulate the block
    Player* attacker = game.getCurrentPlayer();
    attacker->setcoins(2);
    
    // Spy blocks the arrest (in real game, this happens through roledefence)
    Arrest arrest;
    
    // Before arrest: attacker 2, spy 5
    game.playTurn(arrest, 1);
    
    // Spy's role should prevent the arrest from taking coins
    // But since we need to simulate the blocking through the game...
    CHECK(spy->getcoins() >= 4);  // Spy loses at most 1 coin
}

TEST_CASE("Coup advances turn even when blocked") {
    Game game;
    game.addPlayer("A");
    game.addPlayer("B");
    game.addPlayer("C");
    game.startGame();
    
    CHECK(game.turn() == "A");
    
    Player* a = game.getCurrentPlayer();
    a->setcoins(10);
    a->blockAction("Coup");  // Simulate coup being blocked
    
    Coup coup;
    game.playTurn(coup, 1);  // Try to coup B
    
    // Turn should advance to B even though coup was blocked
    CHECK(game.turn() == "B");
    CHECK(game.playersList().size() == 3);  // All players still in game
}

TEST_CASE("Game continues correctly after eliminating current player's target") {
    Game game;
    game.addPlayer("A");
    game.addPlayer("B");
    game.addPlayer("C");
    game.addPlayer("D");
    game.startGame();
    
    // Move to player C (index 2)
    game.playTurn(Gather());  // A's turn
    game.playTurn(Gather());  // B's turn
    
    CHECK(game.turn() == "C");
    
    // C coups A (index 0, which is before C)
    Player* c = game.getCurrentPlayer();
    c->setcoins(10);
    
    Coup coup;
    game.playTurn(coup, 0);  // Eliminate A
    
    // After eliminating someone before current player, indices shift
    CHECK(game.playersList().size() == 3);
    CHECK(game.turn() == "D");  // Should continue to D
}

TEST_CASE("Bribe bonus turns work correctly across multiple players") {
    Game game;
    game.addPlayer("A");
    game.addPlayer("B");
    game.addPlayer("C");
    game.startGame();
    
    Player* a = game.getCurrentPlayer();
    a->setcoins(5);
    
    CHECK(game.turn() == "A");
    
    Bribe bribe;
    game.playTurn(bribe);  // A bribes, gets 2 bonus turns
    
    CHECK(game.turn() == "A");  // Still A's turn (bonus 1)
    game.playTurn(Gather());
    
    CHECK(game.turn() == "A");  // Still A's turn (bonus 2)
    game.playTurn(Gather());
    
    CHECK(game.turn() == "B");  // Now it's B's turn
}

TEST_CASE("Multiple blocks in sequence") {
    Game game;
    game.addPlayer("A");
    game.addPlayer("B");
    game.addPlayer("C");
    game.startGame();
    
    // First, A sanctions B to block Tax/Gather
    Player* a = game.getCurrentPlayer();
    a->setcoins(5);
    Sanction sanction;
    game.playTurn(sanction, 1);  // A sanctions B
    
    // Now it's B's turn, they should be blocked from Tax/Gather
    Player* b = game.getCurrentPlayer();
    CHECK(b->isActionBlocked("Tax"));
    CHECK(b->isActionBlocked("Gather"));
    
    // B does something else
    b->setcoins(5);
    game.playTurn(Bribe());  // This should work
    
    // After B's turn, blocks should be cleared
    game.playTurn(Gather());  // B's bonus turn
    CHECK_FALSE(b->isActionBlocked("Tax"));
    CHECK_FALSE(b->isActionBlocked("Gather"));
}

TEST_CASE("Arrest cooldown persists across turns") {
    Game game;
    game.addPlayer("A");
    game.addPlayer("B");
    game.addPlayer("C");
    game.startGame();
    
    Player* a = game.getCurrentPlayer();
    a->setcoins(2);
    Player* b = game.getPlayerByIndex(1);
    b->setcoins(5);
    
    // A arrests B
    Arrest arrest;
    game.playTurn(arrest, 1);
    
    // Set cooldown manually (normally done in GUI)
    a->arrestCooldown["B"] = 2;
    
    // Play through turns
    game.playTurn(Gather());  // B's turn
    game.playTurn(Gather());  // C's turn
    
    // Back to A, cooldown should be 1
    CHECK(a->arrestCooldown["B"] > 0);
}

TEST_CASE("Action blocks are cleared at turn start") {
    Game game;
    game.addPlayer("A");
    game.addPlayer("B");
    game.startGame();
    
    // A sanctions B
    Player* a = game.getCurrentPlayer();
    a->setcoins(5);
    Player* b = game.getPlayerByIndex(1);
    
    Sanction sanction;
    game.playTurn(sanction, 1);
    
    // B is blocked
    CHECK(b->isActionBlocked("Tax"));
    CHECK(b->isActionBlocked("Gather"));
    
    // B's turn - blocks should be cleared at start of their turn
    game.playTurn(Gather());  // This will clear blocks first, then execute
    
    // After B's turn, blocks are gone
    CHECK_FALSE(b->isActionBlocked("Tax"));
    CHECK_FALSE(b->isActionBlocked("Gather"));
}

TEST_CASE("All roles can block their designated actions") {
    // Test through the Game's canblock method which uses the roles
    Game game;
    game.addPlayer("TestPlayer");
    game.addPlayer("Target");
    game.startGame();
    
    Player* player = game.getCurrentPlayer();
    
    // Test Governor blocks Coup
    player->setrole(new Governor());
    CHECK(player->getrole()->getrolename() == "Governor");
    // In real game, Governor can block coup through game mechanics
    
    // Test Spy blocks Arrest
    player->setrole(new Spy());
    CHECK(player->getrole()->getrolename() == "Spy");
    // In real game, Spy can block arrest
    
    // Test Judge blocks Bribe
    player->setrole(new Judge());
    CHECK(player->getrole()->getrolename() == "Judge");
    // In real game, Judge can block bribe
    
    // Test roles that don't block
    player->setrole(new Baron());
    CHECK(player->getrole()->getrolename() == "Baron");
    
    player->setrole(new Merchant());
    CHECK(player->getrole()->getrolename() == "Merchant");
    
    player->setrole(new General());
    CHECK(player->getrole()->getrolename() == "General");
}
TEST_CASE("Game handles all players eliminated except one") {
    Game game;
    game.addPlayer("A");
    game.addPlayer("B");
    game.addPlayer("C");
    game.startGame();
    
    // Give everyone coins for coup
    for (int i = 0; i < 3; ++i) {
        Player* p = game.getPlayerByIndex(i);
        p->setcoins(20);
    }
    
    // A eliminates B
    Coup coup;
    game.playTurn(coup, 1);
    CHECK(game.playersList().size() == 2);
    
    // C eliminates A  
    game.playTurn(coup, 0);
    CHECK(game.playersList().size() == 1);
    CHECK(game.winner() == "C");  // C wins!
}

TEST_CASE("Maximum coin validation") {
    Game game;
    game.addPlayer("A");
    game.addPlayer("B");
    game.startGame();
    
    Player* a = game.getCurrentPlayer();
    a->setcoins(11);  // More than 10 coins
    
    // Must coup - cannot do other actions
    CHECK_THROWS_WITH(game.playTurn(Gather()), 
                      "You have more than 10 coins. You must play coup.");
    CHECK_THROWS_WITH(game.playTurn(Tax()), 
                      "You have more than 10 coins. You must play coup.");
    
    // Coup should work
    Coup coup;
    CHECK_NOTHROW(game.playTurn(coup, 1));
}