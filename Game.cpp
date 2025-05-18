// Game.cpp
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
    std::cout << "[DEBUG] startGame() called\n";
    std::cout << "[DEBUG] players count: " << playerManager.players.size() << "\n";

    for (size_t i = 0; i < playerManager.players.size(); ++i) {
        if (!playerManager.players[i]) {
            std::cout << "[ERROR] player " << i << " is null\n";
        } else {
            std::cout << "[DEBUG] player " << i << " name: " << playerManager.players[i]->getnameplayer() << "\n";
        }
    }
    if (playerManager.isplayervalid()) {
        cout << "Game started with " << playerManager.players.size() << " players." << endl;
      
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
    
    if (currentPlayerIndex < 0 || currentPlayerIndex >= playerManager.players.size() || !playerManager.players[currentPlayerIndex]) {
        std::cerr << "[ERROR] Invalid currentPlayerIndex: " << currentPlayerIndex << "\n";
        return;
    }
    
    Player& currentPlayer = *playerManager.players[currentPlayerIndex];
    for (auto& [target, cooldown] : currentPlayer.arrestCooldown) {
        if (cooldown > 0) --cooldown;
    }
    std::cout << "[DEBUG] Arrest block check: " << currentPlayer.getnameplayer()
          << ", blocked? " << isarrestblocked(currentPlayer) << "\n";
    currentPlayer.unblockAllActions();
    std::cout << "[DEBUG] unblockAllActions() called for player " << currentPlayer.getnameplayer() << "\n";
    if (action.isType("Arrest")) {
        std::string currentName = currentPlayer.getnameplayer();
        if (isarrestblocked(currentPlayer)) {
            throw std::runtime_error("You are blocked from using Arrest this turn (Spy effect).");
        }
    }
    Player* targetPlayer = nullptr;
    if (currentPlayer.getrole()->getrolename() == "Merchant") {
        currentPlayer.getrole()->rolespecialities(currentPlayer, *this);
    }
    // Check if player has more than 10 coins and must play coup
    if (currentPlayer.getcoins() > 10 && !action.isType("Coup")) {
        throw std::runtime_error("You have more than 10 coins. You must play coup.");
    }
    cout << "Players vector size: " << playerManager.players.size() << endl;
    
    
    if (playerManager.isplayerindexvalid(targetIndex)) {
        
        targetPlayer = playerManager.players[targetIndex].get();
        std::cout << "[DEBUG] Playing action: " << action.getactionname() << "\n";
        if (targetPlayer&& action.isType("Sanction")) {
            Player* target = playerManager.players[targetIndex].get();
            if (target && target->getrole() && target->getrole()->getrolename() == "Judge") {
                if (currentPlayer.getcoins() < 4) {
                    throw std::runtime_error("You need at least 4 coins to sanction a Judge.");
                }
            }
        }
        action.playcard(currentPlayer, *targetPlayer);
        if (currentPlayer.getrole()) {
            currentPlayer.getrole()->roleonaction(currentPlayer, action, targetPlayer);  // 🔁 MISSING RIGHT NOW
        }
        if (targetPlayer && targetPlayer->getrole()) {
            std::cout << "[DEBUG] Target role: " << targetPlayer->getrole()->getrolename() << "\n";
            targetPlayer->getrole()->roledefence(*targetPlayer, action, currentPlayer);
        }
        if (targetPlayer&&action.isType("Coup")) {
            
                playerManager.eliminateplayer(targetIndex);
                if (targetIndex < currentPlayerIndex) {
                    currentPlayerIndex--;
                }
                std::cout << "[DEBUG] Target role: ";
                if (currentPlayerIndex >= playerManager.players.size()) {
                    currentPlayerIndex = 0;
                }
    
        }
        

    } 
    else {
        std::cout << "[DEBUG] Playing non-targeted action: " << action.getactionname() << "\n";
        action.playcard(currentPlayer);
        if (currentPlayer.getrole()) {
            currentPlayer.getrole()->roleonaction(currentPlayer, action, targetPlayer);
        }
       
    }
    if (action.isType("Bribe")) {
        bribebonus = 2;  // Give two extra turns
    }

    //clearArrestBlock(currentPlayer); // Clear the block after the action
    clearArrestBlock();
    if (!checkGameOver()) {
        if (bribebonus > 0) {
            std::cout << "[DEBUG] Bribe bonus turn, remaining: " << bribebonus << "\n";
            bribebonus--;  // one used
            return;        // stay on same player
        } else {
            moveToNextPlayer();
        }
    }
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
    // if (playerManager.players[currentPlayerIndex]) {
    //     playerManager.players[currentPlayerIndex]->unblockAllActions();
    //     std::cout << "[DEBUG] unblockAllActions() called for player " 
    //               << playerManager.players[currentPlayerIndex]->getnameplayer() << "\n";
    // }
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
    if (currentPlayerIndex < 0 || currentPlayerIndex >= playerManager.players.size()) {
        std::cout << "[ERROR] getCurrentPlayer(): invalid index\n";
        return nullptr;
    }
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
    if (index < 0 ) {
        std::cerr << "[ERROR] getPlayerByIndex: index out of bounds: " << index << "\n";
        return nullptr;
    }
    return playerManager.getPlayerByIndex(index);
}

void Game::blockaction(Player& blocker, const Action& action, Player& attacker){
    if(blocker.getrole()){
        if(blocker.getrole()->canblock(action)){
            blocker.getrole()->roledefence(blocker,action,attacker);
        }
    }
    else{
        throw std::runtime_error("blocker has no role");
    }
}
bool Game::canblock(const Action& action) const {
    return playerManager.isplayerindexvalid(currentPlayerIndex) &&
           playerManager.players[currentPlayerIndex]->getrole()->canblock(action);
}