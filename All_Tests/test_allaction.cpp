
#include "doctest.h"

#include "Actions/AllAction.hpp"
#include "Roles/AllRole.hpp"
#include "Players/Player.hpp"

// עוזר ליצירת שחקנים עם תפקיד
std::unique_ptr<Player> makeplayerforaction(const std::string& name, std::unique_ptr<Role> role = nullptr, int coins = 0) {
    auto p = std::make_unique<Player>(name);
    p->setcoins(coins);
    if (role) {
        p->setrole(std::move(role));
    }
    return p;
}

TEST_CASE("Gather adds 1 coin") {
    auto p = makeplayerforaction("P");
    Gather g;
    g.playcard(*p);
    CHECK(p->getcoins() == 1);
}

TEST_CASE("Tax adds 2 coins") {
    auto p = makeplayerforaction("P");
    Tax t;
    t.playcard(*p);
    CHECK(p->getcoins() == 2);
}

TEST_CASE("Bribe removes 4 coins") {
    auto p = makeplayerforaction("P", nullptr, 5);
    Bribe b;
    b.playcard(*p);
    CHECK(p->getcoins() == 1);
}

TEST_CASE("Bribe throws when not enough coins") {
    auto p = makeplayerforaction("P", nullptr, 2);
    Bribe b;
    CHECK_THROWS(b.playcard(*p));
}

TEST_CASE("Coup removes 7 coins") {
    auto p = makeplayerforaction("P", nullptr, 10);
    Coup c;
    c.playcard(*p);
    CHECK(p->getcoins() == 3);
}

TEST_CASE("Arrest vs regular role: +1 to current, -1 to target") {
    auto attacker = makeplayerforaction("Attacker", nullptr, 0);
    auto target = makeplayerforaction("Target", std::make_unique<Spy>(), 5);
    Arrest a;
    a.playcard(*attacker, *target);
    CHECK(attacker->getcoins() == 1);
    CHECK(target->getcoins() == 4);
}

TEST_CASE("Arrest vs Merchant: target loses 2, attacker gains nothing") {
    auto attacker = makeplayerforaction("Attacker", nullptr, 0);
    auto target = makeplayerforaction("Merchant", std::make_unique<Merchant>(), 5);
    Arrest a;
    a.playcard(*attacker, *target);
    CHECK(attacker->getcoins() == 0);
    CHECK(target->getcoins() == 3);
}

TEST_CASE("Sanction removes 3 coins and blocks gather/tax") {
    auto attacker = makeplayerforaction("Attacker", nullptr, 10);
    auto target = makeplayerforaction("Target", std::make_unique<General>(), 5);
    Sanction s;
    s.playcard(*attacker, *target);
    CHECK(attacker->getcoins() == 7);
    CHECK(target->isActionBlocked("Gather"));
    CHECK(target->isActionBlocked("Tax"));
}

TEST_CASE("Baroninvest gives +3 coins net gain") {
    auto p = makeplayerforaction("Baron", std::make_unique<Baron>(), 5);
    Baroninvest bi;
    bi.playcard(*p);
    CHECK(p->getcoins() == 8);  // 5 - 3 + 6
}

TEST_CASE("Governorblocktax blocks Tax action") {
    auto gov = makeplayerforaction("Gov", std::make_unique<Governor>(), 5);
    auto target = makeplayerforaction("Target", nullptr, 5);
    Governorblocktax gbt;
    gbt.playcard(*gov, *target);
    CHECK(target->isActionBlocked("Tax"));
}
