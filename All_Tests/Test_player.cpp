
#include "doctest.h"
#include "Players/Player.hpp"
#include "Roles/RoleFactory.hpp"

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
