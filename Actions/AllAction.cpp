#include "AllAction.hpp"

#include "Player.hpp"

#include <iostream>



std::string Arrest::getactionname() const {
    return "Arrest";
}

bool Arrest::isType(const std::string& type) const {
    return type == "Arrest";
}

void Arrest::playcard(Player& currplayer) const {

}

void Arrest::playcard(Player& currplayer, Player& other) const {
    currplayer.addcoin(1);
other.removecoin(1);
}

std::string Bribe::getactionname() const {
    return "Bribe";
}

bool Bribe::isType(const std::string& type) const {
    return type == "Bribe";
}

void Bribe::playcard(Player& currplayer) const {
    currplayer.removecoin(4);
}

void Bribe::playcard(Player& currplayer, Player& other) const {
    currplayer.removecoin(4);
}

std::string Coup::getactionname() const {
    return "Coup";
}

bool Coup::isType(const std::string& type) const {
    return type == "Coup";
}

void Coup::playcard(Player& currplayer) const {
    currplayer.removecoin(7);
}

void Coup::playcard(Player& currplayer, Player& other) const {
    currplayer.removecoin(7);
}

std::string Gather::getactionname() const {
    return "Gather";
}

bool Gather::isType(const std::string& type) const {
    return type == "Gather";
}

void Gather::playcard(Player& currplayer) const {
    currplayer.addcoin(1);
}

void Gather::playcard(Player& currplayer, Player& other) const {
    currplayer.addcoin(1);
}

std::string Sanction::getactionname() const {
    return "Sanction";
}

bool Sanction::isType(const std::string& type) const {
    return type == "Sanction";
}

void Sanction::playcard(Player& currplayer) const {
    currplayer.removecoin(3);
}

void Sanction::playcard(Player& currplayer, Player& other) const {
    currplayer.removecoin(3);
other.blockAction("Tax");
other.blockAction("Gather");
std::cout << "[DEBUG] " << other.getnameplayer() << " was sanctioned (Tax & Gather blocked)\n";
}

std::string Tax::getactionname() const {
    return "Tax";
}

bool Tax::isType(const std::string& type) const {
    return type == "Tax";
}

void Tax::playcard(Player& currplayer) const {
    std::cout << "[DEBUG] Entering Tax::playcard for " << currplayer.getnameplayer() << "\n";
if (currplayer.getrole()) {
    std::cout << "[DEBUG] Role name: " << currplayer.getrole()->getrolename() << "\n";
} else {
    std::cout << "[DEBUG] Role is null!\n";
}
currplayer.addcoin(2);
}

void Tax::playcard(Player& currplayer, Player& other) const {
    currplayer.addcoin(2);
}