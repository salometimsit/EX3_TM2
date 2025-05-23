#ifndef ACTION_HPP
#define ACTION_HPP
#include <string>
class Player;
class Game;
/**
 * @class Action
 * @brief Abstract base class representing a game action.
 * Provides the interface for various actions that players can perform in the game.
 * Derived classes must implement all pure virtual functions.
 */
class Action {
public:
    /**
     * @brief Executes the action involving only the current player.
     * This method should be overridden to define how the action affects the current player.
     * @param currplayer Reference to the player performing the action.
     */
    virtual void playcard(Player& currplayer) const = 0;
    /**
     * @brief Executes the action involving the current player and another player.
     * This method should be overridden to define how the action affects both players.
     * @param currplayer Reference to the player performing the action.
     * @param other Reference to the other player involved in the action.
     */
    virtual void playcard(Player& currplayer, Player& other) const = 0;
     /**
     * @brief Returns the name of the action.
     * @return A string representing the name of the action.
     */
    virtual std::string getactionname() const = 0;
      /**
     * @brief Checks if the action is of a specified type.
     * @param type A string representing the type to check against.
     * @return True if the action matches the given type, false otherwise.
     */
    virtual bool isType(const std::string& type) const = 0;
    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~Action() = default;
};

#endif