//timsitmelosa@gmail.com
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
    
    // Play a turn by performing the given action. If the action targets another player, specify the target index.
    void playTurn(const Action& action, int targetIndex = -1);

    // Advance the turn to the next player in sequence.
    void moveToNextPlayer();

    // Check if the game has reached a win/lose condition.
    bool checkGameOver();

    // Finalize the game and perform any necessary cleanup.
    //void endGame();

    // Return the current number of players in the game.
    int countplayers() const { return playerManager.playerCount(); }

    // Block an action by another player, using the given blocker and action info.
    void blockaction(Player& blocker, const Action& action, Player& attacker);

    // Determine whether the specified action is eligible to be blocked.
    bool canblock(const Action& action) const;

    // Get a list of all player names for display or processing in the GUI.
    std::vector<std::string> playersList();

    // Return the name of the player whose turn it currently is.
    std::string turn() const;

    // Get a pointer to the current player object.
    Player* getCurrentPlayer();

    // Retrieve the current player's coin count.
    int getCurrentPlayerCoins();

    // Get the role of the current player (e.g., Duke, Assassin).
    std::string getCurrentPlayerRole();

    // Find the index of a player by their name.
    int getPlayerIndexByName(const std::string& name);

    // Retrieve a player object by their index in the player list.
    Player* getPlayerByIndex(int index);
};

#endif 