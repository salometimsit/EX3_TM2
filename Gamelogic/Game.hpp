// Game.hpp - Improved
#ifndef GAME_HPP
#define GAME_HPP
#pragma once
#include <unordered_set>
#include "Roles/RoleFactory.hpp"
#include "Players/Player.hpp"
#include "Players/PlayerManager.hpp"
#include "Actions/ActionFactory.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

/**
 * @class Game
 * @brief Manages the state and flow of the game including players, turns, and actions.
 */
class Game {
private:
    size_t currentPlayerIndex;
    bool gameOver;
    PlayerManager playerManager;
    int bribebonus = 0; 
    
public:
    Game() : currentPlayerIndex(0), gameOver(false), bribebonus(0) {}
    std::unordered_set<std::string> arrestblocknext;
    /** Prevents Arrest action against a player for the next turn. */
    void blockarrestfornext( Player& player);
    /** Clears all arrest blocks after turn resolution. */
    void clearArrestBlock();
    /** Checks if a player is protected from Arrest. */
    bool isarrestblocked( Player& player);
    /** Adds a new player to the game. */
    void addPlayer(const std::string& name);
    /** Prepares and starts the game */
    void startGame();
    std::string winner() const;
    
    void playTurn(const Action& action, int targetIndex=-1);
    void moveToNextPlayer();
    bool checkGameOver();
    void endGame();
    int countplayers() const { return playerManager.playerCount(); }
    void blockaction(Player& blocker, const Action& action, Player& attacker);
    bool canblock(const Action& action) const; // Check if the action can be blocked
    // Helper methods for GUI
    std::vector<std::string> playersList();
    std::string turn() const;
    Player* getCurrentPlayer();
    int getCurrentPlayerCoins();
    std::string getCurrentPlayerRole();
    int getPlayerIndexByName(const std::string& name);
    Player* getPlayerByIndex(int index);
};

#endif // GAME_HPP