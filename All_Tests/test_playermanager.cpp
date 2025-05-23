
#include "doctest.h"

#include "Players/PlayerManager.hpp"
#include "Players/Player.hpp"
#include "Roles/AllRole.hpp"

// Helper function to create player with optional role using this function to test the specific role because in 
// my original code the role is assigned randomly
// and I cannot test the specific role
std::unique_ptr<Player> makePlayer(const std::string& name, std::unique_ptr<Role> role = nullptr) {
    auto p = std::make_unique<Player>(name);
    if (role) {
        p->setrole(std::move(role));
    }
    return p;
}

TEST_CASE("Add and retrieve player") {
    PlayerManager manager;
    auto player = makePlayer("Salome");
    CHECK(manager.addPlayer(std::move(player)));
    CHECK(manager.playerCount() == 1);
    CHECK(manager.getPlayerByIndex(0)->getnameplayer() == "Salome");
}

TEST_CASE("Adding more than MAX_PLAYERS throws") {
    PlayerManager manager;
    for (int i = 0; i < PlayerManager::MAX_PLAYERS; ++i) {
        CHECK_NOTHROW(manager.addPlayer(makePlayer("Player" + std::to_string(i))));
    }
    CHECK_THROWS(manager.addPlayer(makePlayer("ExtraPlayer")));
}

TEST_CASE("isplayervalid throws for invalid player count") {
    PlayerManager manager;
    CHECK_THROWS(manager.isplayervalid()); // Not enough players
    manager.addPlayer(makePlayer("A"));
    manager.addPlayer(makePlayer("B"));
    CHECK(manager.isplayervalid()); // Should now be valid
}

TEST_CASE("Eliminate player works and updates count") {
    PlayerManager manager;
    manager.addPlayer(makePlayer("P1"));
    manager.addPlayer(makePlayer("P2"));
    CHECK(manager.playerCount() == 2);
    manager.eliminateplayer(0);
    CHECK(manager.playerCount() == 1);
    CHECK(manager.getPlayerByIndex(0)->getnameplayer() == "P2");
}

TEST_CASE("getPlayerIndex and getPlayerCoins/Role") {
    PlayerManager manager;
    auto role = std::make_unique<Governor>();
    auto p = makePlayer("Avi", std::move(role));
    p->setcoins(7);
    manager.addPlayer(std::move(p));

    int index = manager.getPlayerIndex("Avi");
    CHECK(index == 0);
    CHECK(manager.getPlayerCoins(index) == 7);
    CHECK(manager.getPlayerRole(index) == "Governor");
}

TEST_CASE("isplayerindexvalid works as expected") {
    PlayerManager manager;
    manager.addPlayer(makePlayer("P1"));
    CHECK(manager.isplayerindexvalid(0));
    CHECK_FALSE(manager.isplayerindexvalid(1));
    CHECK_FALSE(manager.isplayerindexvalid(-1));
}
