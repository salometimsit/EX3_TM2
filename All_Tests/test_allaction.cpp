
#include "doctest.h"

#include "Actions/AllAction.hpp"
#include "Roles/AllRole.hpp"
#include "Players/Player.hpp"

// עוזר ליצירת שחקנים עם תפקיד
Player* makeplayerforaction(const std::string& name, Role* role = nullptr, int coins = 0) {
    Player* p = new Player(name);
    p->setcoins(coins);
    if (role) {
        p->setrole(role);
    }
    return p;
}

TEST_CASE("Gather adds 1 coin") {
    Player* p = makeplayerforaction("P");
    Gather g;
    g.playcard(*p);
    CHECK(p->getcoins() == 1);
    delete p;
}

TEST_CASE("Tax adds 2 coins") {
    Player* p = makeplayerforaction("P");
    Tax t;
    t.playcard(*p);
    CHECK(p->getcoins() == 2);
    delete p;
}

TEST_CASE("Bribe removes 4 coins") {
    Player* p = makeplayerforaction("P", nullptr, 5);
    Bribe b;
    b.playcard(*p);
    CHECK(p->getcoins() == 1);
    delete p;
}

TEST_CASE("Bribe throws when not enough coins") {
    Player* p = makeplayerforaction("P", nullptr, 2);
    Bribe b;
    CHECK_THROWS(b.playcard(*p));
    delete p;
}

TEST_CASE("Coup removes 7 coins") {
    Player* p = makeplayerforaction("P", nullptr, 10);
    Coup c;
    c.playcard(*p);
    CHECK(p->getcoins() == 3);
    delete p;
}

TEST_CASE("Arrest vs regular role: +1 to current, -1 to target") {
    Player* attacker = makeplayerforaction("Attacker", nullptr, 0);
    Player* target = makeplayerforaction("Target", new Spy(), 5);
    Arrest a;
    a.playcard(*attacker, *target);
    CHECK(attacker->getcoins() == 1);
    CHECK(target->getcoins() == 4);
    delete attacker;
    delete target;
}

TEST_CASE("Arrest vs Merchant: target loses 2, attacker gains nothing") {
    Player* attacker = makeplayerforaction("Attacker", nullptr, 0);
    Player* target = makeplayerforaction("Merchant", new Merchant(), 5);
    Arrest a;
    a.playcard(*attacker, *target);
    CHECK(attacker->getcoins() == 0);
    CHECK(target->getcoins() == 3);
    delete attacker;
    delete target;
}

TEST_CASE("Sanction removes 3 coins and blocks gather/tax") {
    Player* attacker = makeplayerforaction("Attacker", nullptr, 10);
    Player* target = makeplayerforaction("Target", new General(), 5);
    Sanction s;
    s.playcard(*attacker, *target);
    CHECK(attacker->getcoins() == 7);
    CHECK(target->isActionBlocked("Gather"));
    CHECK(target->isActionBlocked("Tax"));
    delete attacker;
    delete target;
}

TEST_CASE("Baroninvest gives +3 coins net gain") {
    Player* p = makeplayerforaction("Baron", new Baron(), 5);
    Baroninvest bi;
    bi.playcard(*p);
    CHECK(p->getcoins() == 8);  // 5 - 3 + 6
    delete p;
}

TEST_CASE("Governorblocktax blocks Tax action") {
    Player* gov = makeplayerforaction("Gov", new Governor(), 5);
    Player* target = makeplayerforaction("Target", nullptr, 5);
    Governorblocktax gbt;
    gbt.playcard(*gov, *target);
    CHECK(target->isActionBlocked("Tax"));
    delete gov;
    delete target;
}
TEST_CASE("Arrest throws if target has 0 coins") {
    Player* attacker = makeplayerforaction("A", nullptr, 0);
    Player* target = makeplayerforaction("T", nullptr, 0);
    Arrest a;
    CHECK_THROWS(a.playcard(*attacker, *target)); 
    delete attacker;
    delete target;
}
TEST_CASE("Coup throws if not enough coins") {
    Player* attacker = makeplayerforaction("A", nullptr, 6);  // not enough
    Player* target = makeplayerforaction("T", nullptr, 5);
    Coup c;
    CHECK_THROWS(c.playcard(*attacker, *target));
    delete attacker;
    delete target;
}
TEST_CASE("Sanction throws if not enough coins") {
    Player* attacker = makeplayerforaction("S", nullptr, 2);  // needs 3
    Player* target = makeplayerforaction("T", nullptr, 5);
    Sanction s;
    CHECK_THROWS(s.playcard(*attacker, *target));
    delete attacker;
    delete target;
}
TEST_CASE("Baroninvest throws if not enough coins") {
    Player* p = makeplayerforaction("Baron", new Baron(), 2);
    Baroninvest bi;
    CHECK_THROWS(bi.playcard(*p));
    delete p;
}
TEST_CASE("Governorblocktax does nothing when used alone") {
    Player* gov = makeplayerforaction("Gov", new Governor(), 5);
    Governorblocktax gbt;
    CHECK_NOTHROW(gbt.playcard(*gov));  // this version has empty body
    delete gov;
}
TEST_CASE("Calling single-player Arrest has no effect") {
    Player* p = makeplayerforaction("Solo", nullptr, 5);
    Arrest a;
    CHECK_NOTHROW(a.playcard(*p));  // Defined to do nothing
    CHECK(p->getcoins() == 5);
    delete p;
}