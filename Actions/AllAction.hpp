//timsitmelosa@gmail.com
#ifndef ALLACTION_HPP
#define ALLACTION_HPP
#include "SpecialActions.hpp"
#include "Action.hpp"

/**
 * @class Arrest
 * @brief Represents an "Arrest" action in the game.
 * Inherits from Action and implements its interface.
 */
class Arrest : public Action {
public:
    std::string getactionname() const override;
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
};
//--------------------------------------------------------------------------------------------
/**
 * @class Bribe
 * @brief Represents a "Bribe" action.
 */
class Bribe : public Action {
public:
    std::string getactionname() const override;
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
};
//--------------------------------------------------------------------------------------------
/**
 * @class Coup
 * @brief Represents a "Coup" action.
 */
class Coup : public Action {
public:
    std::string getactionname() const override;
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
};
//--------------------------------------------------------------------------------------------
/**
 * @class Gather
 * @brief Represents a "Gather" action, likely used for resource accumulation.
 */
class Gather : public Action {
public:
    std::string getactionname() const override;
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
};
//--------------------------------------------------------------------------------------------
/**
 * @class Sanction
 * @brief Represents a "Sanction" action, possibly to penalize another player.
 */
class Sanction : public Action {
public:
    std::string getactionname() const override;
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
};
//--------------------------------------------------------------------------------------------

/**
 * @class Tax
 * @brief Represents a "Tax" action for extracting resources from others.
 */

class Tax : public Action {
public:
    std::string getactionname() const override;
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
};
//--------------------------------------------------------------------------------------------
/**
 * @class Baroninvest
 * @brief A special action representing an investment by the "Baron" role.
 * Inherits from SpecialAction.
 */
class Baroninvest: public SpecialAction {
public:
    std::string getactionname() const override{return "Baroninvest";};
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
    bool isspecial(const std::string& roleName) const override;
};
//--------------------------------------------------------------------------------------------
/**
 * @class Governorblocktax
 * @brief A special action that allows the "Governor" to block a tax.
 */
class Governorblocktax: public SpecialAction {
    public:
        std::string getactionname() const override{return "Governorblocktax";};
        bool isType(const std::string& type) const override;
        void playcard(Player& currplayer) const override;
        void playcard(Player& currplayer, Player& other) const override;
        bool isspecial(const std::string& roleName) const override;
};
//--------------------------------------------------------------------------------------------
/**
 * @class Judgeblockbribe
 * @brief A special action that allows the "Judge" to block a bribe.
 */
class Judgeblockbribe : public SpecialAction {
public:
    std::string getactionname() const override { return "Judgeblockbribe"; }
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
    bool isspecial(const std::string& roleName) const override;
};
#endif
