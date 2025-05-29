//timsitmelosa@gmail.com
#include "Gamelogic/Game.hpp"
#include "Players/Player.hpp"
#include "Players/PlayerManager.hpp"
#include "Actions/ActionFactory.hpp"
#include "Roles/RoleFactory.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
using namespace std;

/**
 * @brief Blocks the "Arrest" action for the specified player for their next turn.
 * @param player The player to protect from arrest.
 */
void Game::blockarrestfornext( Player& player) {
        arrestblocknext.insert(player.getnameplayer());
}
/**
 * @brief Removes the arrest block for the current player after their turn.
 */
void Game::clearArrestBlock() {
    if (currentPlayerIndex >= 0 && currentPlayerIndex < playerManager.players.size() && playerManager.players[currentPlayerIndex]) {
        arrestblocknext.erase(playerManager.players[currentPlayerIndex]->getnameplayer());
    }
}
/**
 * @brief Checks if a player is currently protected from the "Arrest" action.
 * @param player The player to check.
 * @return true if the player is protected, false otherwise.
 */
bool Game::isarrestblocked( Player& player) {
    return arrestblocknext.count(player.getnameplayer()) > 0;
}
/**
 * @brief Adds a new player to the game.
 * @param name The player's name.
 * @throws std::runtime_error if the maximum player count is reached.
 */
void Game::addPlayer(const string& name) {
    // Add a player if we haven't reached the max player count
    Player* player = new Player(name);
    if (playerManager.addPlayer(player)) {
    } else {
        throw std::runtime_error("Maximum number of players reached");
    }
}
/**
 * @brief Starts the game and validates player setup.
 * @throws std::runtime_error if player setup is invalid.
 */
void Game::startGame() {
    for (size_t i = 0; i < playerManager.players.size(); ++i) {
        if (!playerManager.players[i]) {
            std::cout << "[ERROR] player " << i << " is null\n";
        }
    }
    if (playerManager.isplayervalid()) {
        currentPlayerIndex = 0;
        gameOver = false;
    } else {
        throw std::runtime_error("Invalid number of players");
    }
}
 /**
* @brief Executes a player's action during their turn.
* @param action The action to perform.
* @param targetIndex Optional index of the targeted player (-1 if none).
*/

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

    bool wasCoupBlocked = currentPlayer.isActionBlocked("Coup");
    currentPlayer.unblockAllActions();

    if (action.isType("Arrest") && isarrestblocked(currentPlayer)) {
        throw std::runtime_error("You are blocked from using Arrest this turn (Spy effect).");
    }

    Player* targetPlayer = nullptr;

    if (currentPlayer.getrole()->getrolename() == "Merchant") {
        currentPlayer.getrole()->rolespecialities(currentPlayer, *this);
    }

    if (currentPlayer.getcoins() > 10 && !action.isType("Coup")) {
        throw std::runtime_error("You have more than 10 coins. You must play coup.");
    }

    if (playerManager.isplayerindexvalid(targetIndex)) {
        targetPlayer = playerManager.players[targetIndex];

        if (targetPlayer && action.isType("Sanction")) {
            if (targetPlayer->getrole() && targetPlayer->getrole()->getrolename() == "Judge") {
                if (currentPlayer.getcoins() < 4) {
                    throw std::runtime_error("You need at least 4 coins to sanction a Judge.");
                }
            }
        }

        action.playcard(currentPlayer, *targetPlayer);

        if (currentPlayer.getrole()) {
            currentPlayer.getrole()->roleonaction(currentPlayer, action, targetPlayer);
        }

    bool coupWasBlocked = false;

    if (targetPlayer && targetPlayer->getrole()) {
        if (!action.isType("Coup")) {
            targetPlayer->getrole()->roledefence(*targetPlayer, action, currentPlayer);
        }

        // GUI will call blockaction() manually if player chooses to block,
        // so here we only check whether the action was already blocked.
        if (action.isType("Coup") && wasCoupBlocked) {
            coupWasBlocked = true;
        }
    }
        if (action.isType("Coup")) {
            if (!coupWasBlocked) {
                playerManager.eliminateplayer(targetIndex);
                int curridx = currentPlayerIndex;
                if (targetIndex < curridx) {
                    currentPlayerIndex--;
                }
                size_t plarcount= playerManager.players.size();
                if (currentPlayerIndex >= plarcount) {
                    currentPlayerIndex = 0;
                }
            }
            clearArrestBlock();
            if (!checkGameOver()) {
                moveToNextPlayer();
            }
            return;
        }

    } else {
        action.playcard(currentPlayer);
        if (currentPlayer.getrole()) {
            currentPlayer.getrole()->roleonaction(currentPlayer, action, nullptr);
        }
    }

    if (action.isType("Bribe")) {
        bribebonus = 2;
    }

    clearArrestBlock();

    if (!checkGameOver()) {
        if (bribebonus > 0) {
            std::cout << "[DEBUG] Bribe bonus turn, remaining: " << bribebonus << "\n";
            bribebonus--;
            return;
        } else {
            moveToNextPlayer();
        }
    }
}



/**
 * @brief Advances the game to the next active player.
 */
void Game::moveToNextPlayer() {
    int playerCount = playerManager.players.size();
    if (playerCount == 0) return;
    
    // Find the next active player
    int nextIndex = currentPlayerIndex;
    int currindex= currentPlayerIndex;
    do {
        nextIndex = (nextIndex + 1) % playerCount;
        // Complete one full cycle without finding a player
        if (nextIndex == currindex) break;
    } while (!playerManager.players[nextIndex]);
    
    currentPlayerIndex = nextIndex;
}
/**
 * @brief Checks if only one player remains.
 * @return true if the game is over, false otherwise.
 */
bool Game::checkGameOver() {
    int activePlayers = 0;
    
    for (size_t i = 0; i < playerManager.players.size(); i++) {
        if (playerManager.players[i]) {
            activePlayers++;
      
        }
    }
    
    if (activePlayers == 1) {
        gameOver = true;
       // endGame();
        return true;
    }
    return false;
}
/**
 * @brief Ends the game and announces the winner.
 */
// void Game::endGame() {

// }

/**
 * @brief Gets the name of the last remaining player.
 * @return Name of the winner or "No winner" if none found.
 */
std::string Game::winner() const {
    if (!gameOver) {
        throw std::runtime_error("Game is still active - no winner yet");
    }
    
    for (const auto& player : playerManager.players) {
        if (player) {
            return player->getnameplayer();
        }
    }
    return "No winner";
}
/**
 * @brief Lists the names of all players in the game.
 * @return Vector of player names.
 */
std::vector<std::string> Game::playersList() {
    std::vector<std::string> playerNames;
    for (const auto& player : playerManager.players) {
        if (player) {
            playerNames.push_back(player->getnameplayer());
        }
    }
    return playerNames;
}
/**
 * @brief Gets the name of the player whose turn it is.
 * @return Player name or empty string if invalid.
 */
std::string Game::turn() const {
    if (currentPlayerIndex >= 0 && 
        currentPlayerIndex < playerManager.players.size() && 
        playerManager.players[currentPlayerIndex]) {
        return playerManager.players[currentPlayerIndex]->getnameplayer();
    }
    return "";
}

/**
 * @brief Retrieves a pointer to the current player.
 * @return Pointer to current player, or nullptr if invalid.
 */
Player* Game::getCurrentPlayer() {
    if (currentPlayerIndex < 0 || currentPlayerIndex >= playerManager.players.size()) {
        std::cout << "[ERROR] getCurrentPlayer(): invalid index\n";
        return nullptr;
    }
    if (currentPlayerIndex >= 0 && 
        currentPlayerIndex < playerManager.players.size() && 
        playerManager.players[currentPlayerIndex]) {
        return playerManager.players[currentPlayerIndex];
    }
    return nullptr;
}

/**
 * @brief Gets the coin count of the current player.
 * @return Number of coins, or 0 if invalid.
 */
int Game::getCurrentPlayerCoins() {
    Player* current = getCurrentPlayer();
    if (current) {
        return current->getcoins();
    }
    return 0;
}
/**
 * @brief Gets the role name of the current player.
 * @return Role name or "Unknown" if not assigned.
 */
std::string Game::getCurrentPlayerRole() {
    Player* current = getCurrentPlayer();
    if (current&&current->getrole()) {
        return current->getrole()->getrolename();
    }
    return "Unknown";
}
/**
 * @brief Finds a player by name.
 * @param name Name of the player to find.
 * @return Index of the player or -1 if not found.
 */
int Game::getPlayerIndexByName(const std::string& name) {
    for (size_t i = 0; i < playerManager.players.size(); ++i) {
        if (playerManager.players[i] && playerManager.players[i]->getnameplayer() == name) {
            return i;
        }
    }
    return -1;
}
/**
 * @brief Retrieves a pointer to the player at the given index.
 * @param index Index of the player.
 * @return Pointer to player, or nullptr if invalid.
 */
Player* Game::getPlayerByIndex(int index) {
    if (index < 0 ) {
        std::cerr << "[ERROR] getPlayerByIndex: index out of bounds: " << index << "\n";
        return nullptr;
    }
    return playerManager.getPlayerByIndex(index);
}
/**
 * @brief Resolves a blocking attempt from one player against another.
 * @param blocker Player attempting the block.
 * @param action Action to block.
 * @param attacker Player performing the action.
 */
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
/**
 * @brief Checks whether the current player can block the given action.
 * @param action The action in question.
 * @return true if blockable, false otherwise.
 */
bool Game::canblock(const Action& action) const {
    return playerManager.isplayerindexvalid(currentPlayerIndex) &&
           playerManager.players[currentPlayerIndex]->getrole()->canblock(action);
}