// Game.hpp - Improved
#ifndef GAME_HPP
#define GAME_HPP

#include <unordered_set>
#include "Roles/RoleFactory.hpp"
#include "Player.hpp"
#include "PlayerManager.hpp"
#include "Actions/ActionFactory.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>


class Game {
private:
    PlayerManager playerManager;
    int currentPlayerIndex;
    
public:
    bool gameOver;
    Game() : gameOver(false), currentPlayerIndex(0) {}
    std::unordered_set<std::string> arrestblocknext;
    void blockarrestfornext( Player& player) {
        arrestblocknext.insert(player.getnameplayer());
    }
    void clearArrestBlock( Player& player) {
        arrestblocknext.erase(player.getnameplayer());
    }
    bool isarrestblocked( Player& player) {
        return arrestblocknext.count(player.getnameplayer()) > 0;
    }
    
    void addPlayer(const std::string& name);
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