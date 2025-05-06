//all accesories needed like: coins, board game etc
#ifindef GAME_HPP
#define GAME_HPP
#include "Actions/ActionFactory.hpp"
#include "Roles/RoleFactory.hpp"
#include "Player.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
class Game {
    private:
        std::vector<std::unique_ptr<Player>> players;
        int currentPlayerIndex;
        int totalPlayers;
        int totalCoins;
        int maxCoins;
        std::string actionName;
    public:
        Game(int numPlayers, int maxCoins);
        void addPlayer(const std::string& name, const std::string& roleName);
        void startGame();
        void playTurn();
        void performAction(Player& player, const std::string& actionName);
        void endGame();
};