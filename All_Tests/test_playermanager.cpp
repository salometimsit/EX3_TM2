//timsitmelosa@gmail.com
#include "doctest.h"

#include "Players/PlayerManager.hpp"
#include "Players/Player.hpp"
#include "Roles/AllRole.hpp"
#include "Actions/ActionFactory.hpp"
#include "Actions/AllAction.hpp"
#include "Gamelogic/Game.hpp"

TEST_CASE("Getting role of invalid player index returns 'Unknown'") {
    PlayerManager manager;
    CHECK(manager.getPlayerRole(0) == "Unknown");
}

TEST_CASE("Governor does not gain extra coin from non-Tax action") {
    Player g("Greg");
    g.setrole(new Governor());
    int before = g.getcoins();

    Gather gather;
    g.getrole()->roleonaction(g, gather);  // Should not affect coins
    CHECK(g.getcoins() == before);
}
TEST_CASE("Spy blocks arrest only for the target") {
    Game game;
    Player spy("SpyGuy");
    spy.setrole(new Spy());

    Player target("Victim");
    target.setrole(new General());
    target.addcoin(3);

    spy.getrole()->rolespecialities(spy, game, &target);

    CHECK(game.isarrestblocked(target));
    CHECK_FALSE(game.isarrestblocked(spy));
}
TEST_CASE("Judge does not react to non-Sanction action") {
    Game game;
    Player judge("Judge");
    judge.setrole(new Judge());

    Player attacker("Bob");
    attacker.setcoins(5);

    Action* tax = ActionFactory::createAction("Tax");
    CHECK_NOTHROW(judge.getrole()->roledefence(judge, *tax, attacker));
    delete tax;

    CHECK(attacker.getcoins() == 5);  // no penalty
}
TEST_CASE("Merchant with less than 2 coins cannot pay arrest penalty") {
    Player m("Shopkeep");
    m.setrole(new Merchant());
    m.setcoins(1);

    Player attacker("Thief");

    Action* arrest = ActionFactory::createAction("Arrest");
    CHECK_THROWS(m.getrole()->roledefence(m, *arrest, attacker));
    delete arrest;
}
TEST_CASE("General blocks Coup and loses no coins") {
    Player general("Shield");
    general.setrole(new General());
    general.setcoins(3);

    Player attacker("Attacker");
    attacker.setcoins(10);

    Action* coup = ActionFactory::createAction("Coup");
    general.getrole()->roledefence(general, *coup, attacker);
    delete coup;

    // Attacker loses 7 coins (done in Game), but general unaffected
    CHECK(general.getcoins() == 3);
}
TEST_CASE("Cannot add more than 6 players") {
    PlayerManager manager;
    for (int i = 0; i < 6; ++i) {
        CHECK_NOTHROW(manager.addPlayer(new Player("P" + std::to_string(i))));
    }

    Player* overflow = new Player("Overflow");
    CHECK_THROWS(manager.addPlayer(overflow));
    delete overflow;  // ✅ clean up manually
}
TEST_CASE("Add and retrieve players") {
    PlayerManager manager;

    Player* alice = new Player("Alice");
    alice->setrole(new Governor());

    Player* bob = new Player("Bob");
    bob->setrole(new Spy());

    CHECK(manager.addPlayer(alice));
    CHECK(manager.addPlayer(bob));
    CHECK(manager.playerCount() == 2);

    CHECK(manager.getPlayerByIndex(0)->getnameplayer() == "Alice");
    CHECK(manager.getPlayerByIndex(1)->getnameplayer() == "Bob");

    CHECK(manager.getPlayerIndex("Alice") == 0);
    CHECK(manager.getPlayerIndex("Bob") == 1);

    CHECK(manager.getPlayerRole(0) == "Governor");
    CHECK(manager.getPlayerRole(1) == "Spy");

    CHECK(manager.getPlayerCoins(0) == 0);
    CHECK(manager.getPlayerCoins(1) == 0);
}

TEST_CASE("Eliminate player") {
    PlayerManager manager;

    Player* c = new Player("Charlie");
    c->setrole(new Merchant());

    Player* d = new Player("Dana");
    d->setrole(new General());

    manager.addPlayer(c);
    manager.addPlayer(d);

    CHECK(manager.playerCount() == 2);

    manager.eliminateplayer(0);  // deletes Charlie
    CHECK(manager.playerCount() == 1);
    CHECK(manager.getPlayerByIndex(0)->getnameplayer() == "Dana");
}

TEST_CASE("Player index validation") {
    PlayerManager manager;

    CHECK_FALSE(manager.isplayerindexvalid(0));

    Player* eve = new Player("Eve");
    eve->setrole(new Judge());

    manager.addPlayer(eve);

    CHECK(manager.isplayerindexvalid(0));
    CHECK_FALSE(manager.isplayerindexvalid(1));
}


TEST_CASE("Governor gains coin on Tax action") {
    Game game;
    Player gov("Greg");
    gov.setrole(new Governor());

    int before = gov.getcoins();
    Action* tax = ActionFactory::createAction("Tax");
    gov.getrole()->roleonaction(gov, *tax);
    delete tax;

    CHECK(gov.getcoins() == before + 1);
}

TEST_CASE("Spy blocks arrest and reveals coins") {
    Game game;
    Player spy("SpyGuy");
    spy.setrole(new Spy());

    Player target("Target");
    target.setrole(new Merchant());
    target.addcoin(3);

    int coins = spy.getrole()->rolespecialities(spy, game, &target);
    CHECK(coins == 3);
}

TEST_CASE("Baron investment converts 3 coins into 6") {
    Game game;
    Player baron("Investor");
    baron.setrole(new Baron());
    baron.addcoin(3);

    baron.getrole()->rolespecialities(baron, game);
    CHECK(baron.getcoins() == 6);
}

TEST_CASE("Judge penalizes attacker on Sanction") {
    Game game;
    Player judge("Lawkeeper");
    judge.setrole(new Judge());

    Player attacker("Thief");
    attacker.addcoin(2);

    Action* sanction = ActionFactory::createAction("Sanction");
    judge.getrole()->roledefence(judge, *sanction, attacker);
    delete sanction;

    CHECK(attacker.getcoins() == 1);
}

TEST_CASE("Merchant gains 1 coin if he has 3 or more") {
    Game game;
    Player merchant("Shopkeep");
    merchant.setrole(new Merchant());
    merchant.addcoin(3);

    int gained = merchant.getrole()->rolespecialities(merchant, game);
    CHECK(gained == 1);
    CHECK(merchant.getcoins() == 4);
}

TEST_CASE("General gains 1 coin if arrested") {
    Game game;
    Player general("Commander");
    general.setrole(new General());

    Player attacker("Enemy");

    Action* arrest = ActionFactory::createAction("Arrest");
    general.getrole()->roledefence(general, *arrest, attacker);
    delete arrest;

    CHECK(general.getcoins() == 1);
}

TEST_CASE("PlayerManager maintains correct state after elimination") {
    PlayerManager manager;
    Player* a = new Player("Alice");
    Player* b = new Player("Bob");
    Player* c = new Player("Charlie");

    a->setrole(new Governor());
    b->setrole(new Spy());
    c->setrole(new Merchant());

    manager.addPlayer(a);
    manager.addPlayer(b);
    manager.addPlayer(c);

    manager.eliminateplayer(1); // Remove Bob

    CHECK(manager.playerCount() == 2);
    CHECK(manager.getPlayerByIndex(0)->getnameplayer() == "Alice");
    CHECK(manager.getPlayerByIndex(1)->getnameplayer() == "Charlie");
    CHECK(manager.getPlayerIndex("Bob") == -1);
}

