#ifndef ALLROLE_HPP
#define ALLROLE_HPP

#include "Role.hpp"
#include "Player.hpp"
#include "Actions/Action.hpp"
#include "Actions/AllAction.hpp"
#include "Actions/SpecialActions.hpp"
#include "Actions/ActionFactory.hpp"

#include "Game.hpp"
class Governor:public Role {
    std::string getrolename() const override{return "Governor";} 
    int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const override;
    void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const override;
    void roledefence(Player& currplayer, const Action& action, Player& other) const override;
    bool canblock(const Action& action) const override;
    std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const override;
};
class Spy:public Role {
    std::string getrolename() const override{return "Spy";} 
    int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const override;
    void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const override;
    void roledefence(Player& currplayer, const Action& action, Player& other) const override;
    bool canblock(const Action& action) const override;
    std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const override;
};
class Baron:public Role {
    std::string getrolename() const override{return "Baron";}
    int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const override;
    void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const override;
    void roledefence(Player& currplayer, const Action& action, Player& other) const override;
    bool canblock(const Action& action) const override;
    std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const override;
};
class Judge:public Role {
    std::string getrolename() const override{return "Judge";} 
    int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const override;
    void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const override;
    void roledefence(Player& currplayer, const Action& action, Player& other) const override;
    bool canblock(const Action& action) const override;
    std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const override;
};
class Merchant:public Role {
    std::string getrolename() const override{return "Merchant";}
    int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const override;
    void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const override;
    void roledefence(Player& currplayer, const Action& action, Player& other) const override;
    bool canblock(const Action& action) const override;
    std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const override;
};
class General:public Role {
    std::string getrolename() const override{return "General";}
    int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const override;
    void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const override;
    void roledefence(Player& currplayer, const Action& action, Player& other) const override;
    bool canblock(const Action& action) const override;
    std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const override;
};

#endif

