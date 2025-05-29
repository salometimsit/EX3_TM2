//timsitmelosa@gmail.com
#include "doctest.h"
#include "Gamelogic/Game.hpp"
#include "Actions/AllAction.hpp"
#include "Roles/AllRole.hpp"
#include "Players/Player.hpp"

TEST_CASE("Full game simulation with all roles") {
    Game game;
    
    // Create 6-player game
    game.addPlayer("Alice");    // Will be Governor
    game.addPlayer("Bob");      // Will be Spy
    game.addPlayer("Charlie");  // Will be Baron
    game.addPlayer("Diana");    // Will be Judge
    game.addPlayer("Eve");      // Will be Merchant
    game.addPlayer("Frank");    // Will be General
    
    game.startGame();
    
    // Assign specific roles to each player
    game.getPlayerByIndex(0)->setrole(new Governor());
    game.getPlayerByIndex(1)->setrole(new Spy());
    game.getPlayerByIndex(2)->setrole(new Baron());
    game.getPlayerByIndex(3)->setrole(new Judge());
    game.getPlayerByIndex(4)->setrole(new Merchant());
    game.getPlayerByIndex(5)->setrole(new General());
    
    // Give everyone some starting coins
    for (int i = 0; i < 6; ++i) {
        game.getPlayerByIndex(i)->setcoins(3);
    }
    
    CHECK(game.playersList().size() == 6);
    CHECK(game.turn() == "Alice");
    
    // Round 1: Basic actions
    // Alice (Governor) uses Tax - should get 3 coins (2 + 1 bonus)
    game.playTurn(Tax());
    CHECK(game.getPlayerByIndex(0)->getcoins() == 6); // 3 + 2 + 1
    CHECK(game.turn() == "Bob");
    
    // Bob (Spy) uses Gather
    game.playTurn(Gather());
    CHECK(game.getPlayerByIndex(1)->getcoins() == 4);
    CHECK(game.turn() == "Charlie");
    
    // Charlie (Baron) uses Tax (can't access special ability)
    game.playTurn(Tax());
    CHECK(game.getPlayerByIndex(2)->getcoins() == 5); // 3 + 2
    CHECK(game.turn() == "Diana");
    
    // Diana (Judge) uses Tax
    game.playTurn(Tax());
    CHECK(game.getPlayerByIndex(3)->getcoins() == 5);
    CHECK(game.turn() == "Eve");
    
    // Eve (Merchant) should get passive income (has 3+ coins)
    int eveCoinsBeforeTurn = game.getPlayerByIndex(4)->getcoins();
    game.playTurn(Gather());
    // Merchant gets +1 at start of turn if 3+ coins, then +1 from Gather
    CHECK(game.getPlayerByIndex(4)->getcoins() == eveCoinsBeforeTurn + 2);
    CHECK(game.turn() == "Frank");
    
    // Frank (General) uses Tax
    game.playTurn(Tax());
    CHECK(game.getPlayerByIndex(5)->getcoins() == 5);
    CHECK(game.turn() == "Alice");
    
    // Round 2: Targeted actions
    // Alice sanctions Bob
    game.playTurn(Sanction(), 1);
    CHECK(game.getPlayerByIndex(0)->getcoins() == 3); // 6 - 3
    CHECK(game.getPlayerByIndex(1)->isActionBlocked("Tax"));
    CHECK(game.getPlayerByIndex(1)->isActionBlocked("Gather"));
    
    // Bob tries to arrest Charlie
    game.playTurn(Arrest(), 2);
    CHECK(game.getPlayerByIndex(1)->getcoins() == 5); // 4 + 1
    CHECK(game.getPlayerByIndex(2)->getcoins() == 4); // 5 - 1
    
    // Game state consistency checks
    CHECK(game.playersList().size() == 6);
    
    // Verify all players still have correct roles
    CHECK(game.getPlayerByIndex(0)->getrole()->getrolename() == "Governor");
    CHECK(game.getPlayerByIndex(1)->getrole()->getrolename() == "Spy");
    CHECK(game.getPlayerByIndex(2)->getrole()->getrolename() == "Baron");
    CHECK(game.getPlayerByIndex(3)->getrole()->getrolename() == "Judge");
    CHECK(game.getPlayerByIndex(4)->getrole()->getrolename() == "Merchant");
    CHECK(game.getPlayerByIndex(5)->getrole()->getrolename() == "General");
    
    // Round 3: Test coup mechanics
    // Give Charlie enough coins to coup
    game.getPlayerByIndex(2)->setcoins(10);
    game.playTurn(Coup(), 3); // Charlie coups Diana
    CHECK(game.playersList().size() == 5);
    
    // After Diana is eliminated, verify turn continues
    // It should be Eve's turn now
    CHECK(game.turn() == "Eve");
}

TEST_CASE("Stress test with rapid eliminations") {
    Game game;
    
    // Create 6 players
    for (int i = 0; i < 6; ++i) {
        game.addPlayer("Player" + std::to_string(i));
    }
    game.startGame();
    
    // Give everyone enough coins for multiple coups
    for (int i = 0; i < 6; ++i) {
        game.getPlayerByIndex(i)->setcoins(30);
    }
    
    CHECK(game.playersList().size() == 6);
    
    // Round 1: Player0 eliminates Player1
    CHECK(game.turn() == "Player0");
    game.playTurn(Coup(), 1);
    CHECK(game.playersList().size() == 5);
    
    // Player2's turn (index shifted after elimination)
    CHECK(game.turn() == "Player2");
    game.playTurn(Coup(), 2); // Eliminates Player3
    CHECK(game.playersList().size() == 4);
    
    // Player4's turn
    CHECK(game.turn() == "Player4");
    game.playTurn(Coup(), 3); // Eliminates Player5
    CHECK(game.playersList().size() == 3);
    
    // Back to Player0
    CHECK(game.turn() == "Player0");
    game.playTurn(Coup(), 1); // Eliminates Player2
    CHECK(game.playersList().size() == 2);
    
    // Player4's turn - final coup
    CHECK(game.turn() == "Player4");
    game.playTurn(Coup(), 0); // Eliminates Player0
    CHECK(game.playersList().size() == 1);
    CHECK(game.winner() == "Player4");
    
}
TEST_CASE("Role abilities and defenses") {
    Game game;
    
    // Create players
    game.addPlayer("Baron");
    game.addPlayer("Judge");
    game.addPlayer("Merchant");
    game.addPlayer("General");
    
    game.startGame();
    
    // Assign roles
    game.getPlayerByIndex(0)->setrole(new Baron());
    game.getPlayerByIndex(1)->setrole(new Judge());
    game.getPlayerByIndex(2)->setrole(new Merchant());
    game.getPlayerByIndex(3)->setrole(new General());
    
    // Test Baron's defense against Sanction
    game.getPlayerByIndex(0)->setcoins(5);
    game.getPlayerByIndex(1)->setcoins(5);
    
    // Baron's turn - skip to Judge
    game.playTurn(Gather());
    CHECK(game.getPlayerByIndex(0)->getcoins() == 6);
    
    // Judge sanctions Baron
    CHECK(game.turn() == "Judge");
    game.playTurn(Sanction(), 0);
    CHECK(game.getPlayerByIndex(1)->getcoins() == 2); 
    // Baron should gain +1 from being sanctioned
    CHECK(game.getPlayerByIndex(0)->getcoins() == 7); 
    
    // Merchant's turn - test passive income
    CHECK(game.turn() == "Merchant");
    game.getPlayerByIndex(2)->setcoins(3); // Set to exactly 3
    int merchantCoinsBefore = game.getPlayerByIndex(2)->getcoins();
    game.playTurn(Gather());
    // Should get +1 passive income, +1 from Gather
    CHECK(game.getPlayerByIndex(2)->getcoins() == merchantCoinsBefore + 2);
    
    // General's turn - test defense against Arrest
    CHECK(game.turn() == "General");
    game.getPlayerByIndex(3)->setcoins(2);
    game.playTurn(Arrest(), 0); // Arrest Baron
    // General should gain coins from arresting
    CHECK(game.getPlayerByIndex(3)->getcoins() == 3); 
    CHECK(game.getPlayerByIndex(0)->getcoins() == 6); 
    
    // Back to Baron - let's test Judge's penalty for being sanctioned
    CHECK(game.turn() == "Baron");
    game.playTurn(Sanction(), 1); // Sanction the Judge
    CHECK(game.getPlayerByIndex(0)->getcoins() == 2); 
    // Judge's defense: attacker loses 1 coin (already paid 3 for sanction)
    CHECK(game.getPlayerByIndex(1)->getcoins() == 2); 
}