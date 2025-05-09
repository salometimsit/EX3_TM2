// Game.cpp - Improved
#include "Game.hpp"
#include "Player.hpp"
#include "PlayerManager.hpp"
#include "Actions/ActionFactory.hpp"
#include "Roles/RoleFactory.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

using namespace std;

void Game::addPlayer(const string& name) {
    // Add a player if we haven't reached the max player count
    Player* player = new Player(name);
    if (playerManager.addPlayer(std::unique_ptr<Player>(player))) {
        cout << "Player " << name << " added to the game." << endl;
    } else {
        throw std::runtime_error("Maximum number of players reached");
    }
}

void Game::startGame() {
    if (playerManager.isplayervalid()) {
        cout << "Game started with " << playerManager.players.size() << " players." << endl;
        playerManager.shuffleplayers();
        currentPlayerIndex = 0;
        gameOver = false;
    } else {
        throw std::runtime_error("Invalid number of players");
    }
}

void Game::playTurn(const Action& action, int targetIndex) {
    if (gameOver) {
        cout << "Game is over. Cannot play turn." << endl;
        return;
    }
    
    Player& currentPlayer = *playerManager.players[currentPlayerIndex];
    Player* targetPlayer = nullptr;
    cout << "Current player: " << currentPlayer.getnameplayer() << endl;
    cout<<"current player index: "<<currentPlayerIndex<<endl;
    std::cout << "[DEBUG] Role: " << (currentPlayer.getrole() ? currentPlayer.getrole()->getrolename() : "null") << std::endl;
   
    
    // Check if player has more than 10 coins and must play coup
    if (currentPlayer.getcoins() > 10 && !action.isType("Coup")) {
        cout << "You have more than 10 coins. You must play Coup." << endl;
        throw std::runtime_error("You have more than 10 coins. You must play coup.");
    }
    cout << "Players vector size: " << playerManager.players.size() << endl;
    
    
    if (playerManager.isplayerindexvalid(targetIndex)) {
        cout<<"enetred if"<<endl;
        targetPlayer = playerManager.players[targetIndex].get();
        action.playcard(currentPlayer, *targetPlayer);
        cout<<"action played: "<<action.getactionname()<<endl;
        
        if (targetPlayer) {
            action.playcard(currentPlayer, *targetPlayer);
            if (action.isType("Coup")) {
                playerManager.eliminateplayer(targetIndex);
            }
        }

    } 
    else {
        cout<<"entered else"<<endl;
        action.playcard(currentPlayer);
    }
    
    moveToNextPlayer();
    checkGameOver();
}

void Game::moveToNextPlayer() {
    int playerCount = playerManager.players.size();
    if (playerCount == 0) return;
    
    // Find the next active player
    int nextIndex = currentPlayerIndex;
    do {
        nextIndex = (nextIndex + 1) % playerCount;
        // Complete one full cycle without finding a player
        if (nextIndex == currentPlayerIndex) break;
    } while (!playerManager.players[nextIndex]);
    
    currentPlayerIndex = nextIndex;
}

bool Game::checkGameOver() {
    std::cout << "Entering checkGameOver()\n";
    int activePlayers = 0;
    int lastIndex = -1;
    
    for (size_t i = 0; i < playerManager.players.size(); i++) {
        std::cout << "Checking player index " << i << "\n";
        if (playerManager.players[i]) {
            std::cout << "Player " << i << " is not null\n";
            activePlayers++;
            lastIndex = i;
        }
    }
    
    if (activePlayers == 1) {
        gameOver = true;
        endGame();
        return true;
    }
    std::cout << "Exiting checkGameOver()\n";
    return false;
}

void Game::endGame() {
    cout << "Game over. " << winner() << " wins!" << endl;

}

std::string Game::winner() const {
    for (const auto& player : playerManager.players) {
        if (player) {
            return player->getnameplayer();
        }
    }
    return "No winner";
}

std::vector<std::string> Game::playersList() {
    std::vector<std::string> playerNames;
    for (const auto& player : playerManager.players) {
        if (player) {
            playerNames.push_back(player->getnameplayer());
        }
    }
    return playerNames;
}

std::string Game::turn() const {
    if (currentPlayerIndex >= 0 && 
        currentPlayerIndex < playerManager.players.size() && 
        playerManager.players[currentPlayerIndex]) {
        return playerManager.players[currentPlayerIndex]->getnameplayer();
    }
    return "";
}


Player* Game::getCurrentPlayer() {
    if (currentPlayerIndex >= 0 && 
        currentPlayerIndex < playerManager.players.size() && 
        playerManager.players[currentPlayerIndex]) {
        return playerManager.players[currentPlayerIndex].get();
    }
    return nullptr;
}

int Game::getCurrentPlayerCoins() {
    Player* current = getCurrentPlayer();
    if (current) {
        return current->getcoins();
    }
    return 0;
}

std::string Game::getCurrentPlayerRole() {
    Player* current = getCurrentPlayer();
    if (current&&current->getrole()) {
        return current->getrole()->getrolename();
    }
    return "Unknown";
}

int Game::getPlayerIndexByName(const std::string& name) {
    for (size_t i = 0; i < playerManager.players.size(); ++i) {
        if (playerManager.players[i] && playerManager.players[i]->getnameplayer() == name) {
            return i;
        }
    }
    return -1;
}
Player* Game::getPlayerByIndex(int index) {
    return playerManager.getPlayerByIndex(index);
}