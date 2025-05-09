#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "PlayerManager.hpp"
#include <random>
#include <algorithm>

bool PlayerManager::addPlayer(unique_ptr<Player> player) {
    if (players.size() >= MAX_PLAYERS) {
        throw std::runtime_error("Maximum number of players reached cannot add more players");
    }
    players.push_back(move(player));
    return true; 
}


bool PlayerManager::isplayervalid() const {
    if(players.size() < MIN_PLAYERS) {
        throw std::runtime_error("Not enough players to start the game");
    }
    if(players.size() > MAX_PLAYERS) {
        throw std::runtime_error("Too many players to start the game");
    }
    return true;
}

bool PlayerManager::isplayerindexvalid(int index) {
    if(index < 0 || static_cast<size_t>(index) >= players.size()) {
        return false;
    }
    return true;
}

void PlayerManager::shuffleplayers() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(players.begin(), players.end(), g);
}

void PlayerManager::eliminateplayer(int index) {
    if (index < 0 || static_cast<size_t>(index) >= players.size()) {
        throw std::out_of_range("Invalid player index");
    }
    players.erase(players.begin() + index);
}

size_t PlayerManager::playerCount() const {
    return players.size();
}
Player* PlayerManager::getPlayerByIndex(int index) {
    if (index >= 0 && index < players.size() && players[index]) {
        return players[index].get();
    }
    return nullptr;
}

int PlayerManager::getPlayerIndex(const std::string& playerName) {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i] && players[i]->getnameplayer() == playerName) {
            return i;
        }
    }
    return -1;
}

int PlayerManager::getPlayerCoins(int index) {
    Player* player = getPlayerByIndex(index);
    if (player) {
        return player->getcoins();
    }
    return 0;
}

std::string PlayerManager::getPlayerRole(int index) {
    Player* player = getPlayerByIndex(index);
    if (player) {
        return player->getrole()->getrolename();
    }
    return "Unknown";
}
