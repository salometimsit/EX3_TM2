#ifndef PLAYER_HPP
#define PLAYER_HPP
/**
 * @file Player.hpp
 * @brief Declaration of the Player class and associated utilities.
 *
 * This header defines the Player class used to represent each participant in the game.
 * The class handles coin management, role assignment, and action blocking mechanics.
 *
 * @note This file only contains declarations; the corresponding definitions should be
 *       provided in Player.cpp.
 */

#include <string>
#include <memory>
#include <stdexcept>
#include <random>
#include <ostream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using std::string;
class RoleFactory;  
#include "Roles/Role.hpp"

using namespace std;  
using std::unique_ptr;

/**
 * @class Player
 * @brief Encapsulates the state and behaviour of a single game player.
 *
 * A Player owns a name, a coin balance, and a Role* that describes their current
 * capabilities in the game. The class also tracks which actions are temporarily
 * blocked (e.g. after an arrest) and manages cooldowns for those actions.
 */
class Player{
    private:
        /** Player's display name. */
        std::string name;
        /** Current coin balance. */
        int coins;
        /** Pointer to the player's active role. */
        Role* role = nullptr;
        /** Set of action names currently blocked for this player. */
        std::unordered_set<std::string> blockedactions;

    public:
        /** Map tracking remaining cooldown turns for arrest-related actions. */
        std::unordered_map<std::string, int> arrestCooldown;

        /**
         * @brief Assigns and returns a new Role to the player.
         * @return Pointer to the newly assigned Role instance.
         * @throw std::runtime_error if no roles are available.
         */
        Role* assignroles();

        /**
         * @brief Constructs a Player with the given display name.
         * @param name Unique identifier for the player.
         */
        Player(const std::string& name);

        /**
         * @brief Copy‑constructor.
         * @param other Player instance to copy from.
         */
        Player(const Player& other);

        /**
         * @brief Copy‑assignment operator.
         * @param other Player instance to copy from.
         * @return Reference to this Player after assignment.
         */
        Player& operator=(const Player& other);

        /** Destructor. Releases owned resources. */
        ~Player();

        /**
         * @brief Blocks a specific action for this player.
         * @param actionName Name of the action to block.
         */
        void blockAction(const std::string& actionName);

        /**
         * @brief Removes all currently blocked actions.
         */
        void unblockAllActions();

        /**
         * @brief Checks whether a given action is blocked.
         * @param actionName Name of the action to test.
         * @return true if the action is blocked; otherwise false.
         */
        bool isActionBlocked(const std::string& actionName) const;

        /** @name Accessors */
        std::string getnameplayer() const { return name; } ///< Returns the player's name.
        int getcoins() const { return coins; }             ///< Returns the player's coin count.
        const Role* getrole() const { return role; }       ///< Returns a const pointer to the player's role.
      

        /** @name Mutators */
        void setcoins(int c){coins=c;}                     ///< Sets the player's coin balance.
        void setname(const string& n){name=n;}             ///< Sets the player's display name.
        void setrole(Role* r);                             ///< Assigns a new Role pointer.

        /**
         * @brief Increases the player's coin balance.
         * @param amount Positive number of coins to add.
         */
        void addcoin(int amount);

        /**
         * @brief Decreases the player's coin balance.
         * @param amount Positive number of coins to remove.
         * @throw std::underflow_error if amount exceeds current balance.
         */
        void removecoin(int amount);
};

#endif // PLAYER_HPP
