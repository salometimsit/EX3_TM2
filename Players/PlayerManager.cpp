//timsitmelosa@gmail.com
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "Players/PlayerManager.hpp"
#include "Players/Player.hpp"
#include <random>
#include <algorithm>
/**
 * @brief Destroys the manager and releases ownership of all `Player` objects.
 */
PlayerManager::~PlayerManager() {
    for (Player* p : players) {
        delete p;
    }
}
/**
 * @param player Raw pointer to a heap‑allocated Player (manager assumes ownership).
 * @return `true` if the player is successfully added.
 * @throw std::runtime_error if the player limit (MAX_PLAYERS) has been reached.
 */
bool PlayerManager::addPlayer(Player* player) {
    if (players.size() >= MAX_PLAYERS) {
        throw std::runtime_error("Maximum number of players reached cannot add more players");
    }
    players.push_back(player);
    return true;
}

/**
 * @brief Validates the current player count against MIN/MAX constants.
 * @return `true` if the player count is within the legal range.
 * @throw std::runtime_error if the count is outside the allowed limits.
 */
bool PlayerManager::isplayervalid() const {
    if(players.size() < MIN_PLAYERS) {
        throw std::runtime_error("Not enough players to start the game");
    }
    if(players.size() > MAX_PLAYERS) {
        throw std::runtime_error("Too many players to start the game");
    }
    return true;
}
/**
 * @param index Index of the player to validate.
 * @return `true` if `index` is within the bounds of the vector; otherwise `false`.
 */
bool PlayerManager::isplayerindexvalid(int index)const {
    if(index < 0 || static_cast<size_t>(index) >= players.size()) {
        return false;
    }
    return true;
}

/**
 * @brief Removes a player from the game and cleans up its memory.
 * @param index Index of the player to eliminate.
 * @throw std::out_of_range if the index is invalid.
 */
void PlayerManager::eliminateplayer(int index) {
    if (index < 0 || static_cast<size_t>(index) >= players.size()) {
        throw std::out_of_range("Invalid player index");
    }
    delete players[index];
    players.erase(players.begin() + index);
}
/**
 * @return The current number of players managed.
 */
size_t PlayerManager::playerCount() const {
    return players.size();
}
/**
 * @brief Retrieves a player pointer by index without bounds‑checking exceptions.
 * @param index Index of the player.
 * @return Pointer to the player, or `nullptr` if the index is invalid or empty.
 */
Player* PlayerManager::getPlayerByIndex(int index) {
    int size= players.size();
    if (index >= 0 && index <size && players[index]) {
        return players[index];
        
    }
    return nullptr;
}
/**
 * @brief Finds the first player whose name matches the provided string.
 * @param playerName Case‑sensitive name to search for.
 * @return Zero‑based index if found; otherwise `-1`.
 */
int PlayerManager::getPlayerIndex(const std::string& playerName) {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i] && players[i]->getnameplayer() == playerName) {
            return i;
        }
    }
    return -1;
}
/**
 * @brief Convenience accessor that returns a player's coin total by index.
 * @param index Player index (same rules as getPlayerByIndex).
 * @return Coin count; returns 0 if the index is invalid.
 */
int PlayerManager::getPlayerCoins(int index) {
    Player* player = getPlayerByIndex(index);
    if (player) {
        return player->getcoins();
    }
    return 0;
}
/**
 * @brief Returns the role name associated with the player at `index`.
 * @param index Player index.
 * @return Role name string or "Unknown" if the index/player is invalid.
 */
std::string PlayerManager::getPlayerRole(int index) {
    Player* player = getPlayerByIndex(index);
    if (player) {
        return player->getrole()->getrolename();
    }
    return "Unknown";
}
