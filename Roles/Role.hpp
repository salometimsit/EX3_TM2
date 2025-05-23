#ifndef ROLE_HPP
#define ROLE_HPP
#include <string>
#include <memory>
#include "Actions/Action.hpp"
#include "Actions/SpecialActions.hpp"
class Game;
// #include "Actions/Actionstrategy.hpp"
class Actionstrategy;
class Player;
class Action;
/**
 * @class Role
 * @brief Abstract base class for defining player roles in the game.
 * 
 * Each role defines its unique abilities, reactions to actions, and 
 * interaction capabilities with the game's mechanics.
 */
class Role {
public:
    Role() = default;

    /**
     * @brief Virtual destructor to allow proper cleanup of derived classes.
     */
    virtual ~Role();
    /**
     * @brief Executes role-specific logic, potentially affecting the player or game.
     * @param currplayer The player performing the action.
     * @param game Reference to the game state.
     * @param other Optional pointer to another player involved.
     * @return An integer representing the result or effect magnitude of the specialty.
     */
    virtual int rolespecialities(Player& currplayer, Game& game, Player* other = nullptr) const = 0;
    /**
     * @brief Handles the role's response when an action is taken by or against the player.
     * @param currplayer The player affected.
     * @param actionname The action being processed.
     * @param other Optional pointer to the other player involved.
     */
    virtual void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const = 0;
    /**
     * @brief Defines how the role defends or reacts to an incoming action from another player.
     * @param currplayer The player being defended.
     * @param action The action being defended against.
     * @param other The player who initiated the action.
     */
    virtual void roledefence(Player& currplayer, const Action& action, Player& other) const = 0;
    /**
     * @brief Returns the name of the role.
     * @return A string representing the role's name.
     */
    virtual std::string getrolename() const = 0;
    /**
     * @brief Determines if the role can block a specific action.
     * 
     * @param action The action to potentially block.
     * @return true if the role can block the action, false otherwise.
     */
    virtual bool canblock(const Action& action) const = 0;
    /**
     * @brief Returns a special action that the role can perform, if any.
     * @param game Reference to the game state.
     * @param user The player using the special action.
     * @param target Optional target player for the special action.
     * @return A unique pointer to a SpecialAction, or nullptr if none is available.
     */
    virtual std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const;
};

#endif