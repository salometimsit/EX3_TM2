
#include "doctest.h"
#include "Players/Player.hpp"
#include "Roles/RoleFactory.hpp"



TEST_CASE("Player name setter and getter") {
    Player p("Temp");
    p.setname("NewName");
    CHECK(p.getnameplayer() == "NewName");
}
TEST_CASE("Player setcoins and getcoins") {
    Player p("Lior");
    p.setcoins(7);
    CHECK(p.getcoins() == 7);
}
TEST_CASE("Set role manually and get role name") {
    Player p("Dana");
    Role* r = RoleFactory::createRole("Spy");
    p.setrole(r);
    CHECK(p.getrole()->getrolename() == "Spy");
}
TEST_CASE("Blocking same action twice has no side effect") {
    Player p("Alex");
    p.blockAction("Tax");
    p.blockAction("Tax");
    CHECK(p.isActionBlocked("Tax"));
}
TEST_CASE("Unblocking with nothing blocked") {
    Player p("Noa");
    CHECK_FALSE(p.isActionBlocked("Coup"));
    CHECK_NOTHROW(p.unblockAllActions());  // should be safe
}
TEST_CASE("Assigning a new role replaces old role") {
    Player p("Eden");
    Role* first = RoleFactory::createRole("Spy");
    Role* second = RoleFactory::createRole("Governor");

    p.setrole(first);
    CHECK(p.getrole()->getrolename() == "Spy");

    p.setrole(second);  // old role should be deleted
    CHECK(p.getrole()->getrolename() == "Governor");
}
TEST_CASE("Player coin manipulation") {
    Player p("Alice");

    SUBCASE("Initial coins is 0") {
        CHECK(p.getcoins() == 0);
    }

    SUBCASE("Add coins") {
        p.addcoin(3);
        CHECK(p.getcoins() == 3);
    }

    SUBCASE("Remove coins within limit") {
        p.addcoin(5);
        p.removecoin(2);
        CHECK(p.getcoins() == 3);
    }
    SUBCASE("Add (-1) coins"){
        CHECK_THROWS_AS(p.addcoin(-1), std::runtime_error);
    }

    SUBCASE("Remove coins with exception") {
        CHECK_THROWS_AS(p.removecoin(1), std::runtime_error);
    }
}

TEST_CASE("Player block and unblock actions") {
    Player p("Ari");
    CHECK_FALSE(p.isActionBlocked("Tax"));
    p.blockAction("Tax");
    CHECK(p.isActionBlocked("Tax"));

    p.unblockAllActions();
    CHECK_FALSE(p.isActionBlocked("Tax"));
}

TEST_CASE("Arrest cooldown system") {
    Player p("Salome");
    p.arrestCooldown["Ari"] = 2;

    SUBCASE("Cooldown exists") {
        CHECK(p.arrestCooldown["Ari"] == 2);
    }

    SUBCASE("Cooldown decrement") {
        --p.arrestCooldown["Ari"];
        CHECK(p.arrestCooldown["Ari"] == 1);
    }
}

TEST_CASE("Role is assigned on construction") {
    Player p("Adi");
    CHECK(p.getrole() != nullptr);
    CHECK_FALSE(p.getrole()->getrolename().empty());
}
