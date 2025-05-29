//timsitmelosa@gmail.com
#ifndef ALLROLE_HPP
#define ALLROLE_HPP
#include "Role.hpp"
#include "Players/Player.hpp"
#include "Actions/Action.hpp"
#include "Actions/AllAction.hpp"
#include "Actions/SpecialActions.hpp"
#include "Actions/ActionFactory.hpp"

#include "Gamelogic/Game.hpp"
/**
 * @class Governor
 * @brief A role that can block certain actions and may influence taxation mechanics.
 */
class Governor:public Role {
    std::string getrolename() const override{return "Governor";} 
    int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const override;
    void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const override;
    void roledefence(Player& currplayer, const Action& action, Player& other) const override;
    bool canblock(const Action& action) const override;
    std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const override;
};
//---------------------------------------------------------------------------------------------
/**
 * @class Spy
 * @brief A role focused on covert interaction, potentially gathering or manipulating information.
 */
class Spy:public Role {
    std::string getrolename() const override{return "Spy";} 
    int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const override;
    void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const override;
    void roledefence(Player& currplayer, const Action& action, Player& other) const override;
    bool canblock(const Action& action) const override;
    std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const override;
};
//---------------------------------------------------------------------------------------------
/**
 * @class Baron
 * @brief A role emphasizing investment and economic advantage through special actions.
 */
class Baron:public Role {
    std::string getrolename() const override{return "Baron";}
    int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const override;
    void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const override;
    void roledefence(Player& currplayer, const Action& action, Player& other) const override;
    bool canblock(const Action& action) const override;
    std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const override;
};
//---------------------------------------------------------------------------------------------
/**
 * @class Judge
 * @brief A role associated with control, law enforcement, or reactive authority over actions.
 */
class Judge:public Role {
    std::string getrolename() const override{return "Judge";} 
    int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const override;
    void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const override;
    void roledefence(Player& currplayer, const Action& action, Player& other) const override;
    bool canblock(const Action& action) const override;
    std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const override;
};
//---------------------------------------------------------------------------------------------
/**
 * @class Merchant
 * @brief A role focused on wealth generation, likely vulnerable to economic targeting.
 */
class Merchant:public Role {
    std::string getrolename() const override{return "Merchant";}
    int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const override;
    void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const override;
    void roledefence(Player& currplayer, const Action& action, Player& other) const override;
    bool canblock(const Action& action) const override;
    std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const override;
};
//---------------------------------------------------------------------------------------------
/**
 * @class General
 * @brief A military or defense-oriented role, potentially protecting allies or resisting attacks.
 */
class General:public Role {
    std::string getrolename() const override{return "General";}
    int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const override;
    void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const override;
    void roledefence(Player& currplayer, const Action& action, Player& other) const override;
    bool canblock(const Action& action) const override;
    std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const override;
};

#endif