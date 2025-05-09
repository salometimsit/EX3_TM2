// Game.hpp - Improved
#ifndef GAME_HPP
#define GAME_HPP


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
    
    void addPlayer(const std::string& name);
    void startGame();
    std::string winner() const;
    void playTurn(const Action& action, int targetIndex=-1);
    void moveToNextPlayer();
    bool checkGameOver();
    void endGame();
    int countplayers() const { return playerManager.playerCount(); }
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