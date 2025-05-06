/**
This class needs to be a Strategy/factory one- so the other roles use it
 */
//make as interface:
#ifndef ROLE_STRATEGY_HPP
#define ROLE_STRATEGY_HPP
class Player;
class ActionStrategy;
class Rolestrategy{
    public:
        virtual ~Rolestrategy();
        virtual void abilities(Player& currplayer,ActionStrategy& action, Player* other);
        virtual std::string getrolename();
        virtual bool isrole(const std::string& type)const;
        virtual bool canblock(const std::string& action)const;
};
#endif