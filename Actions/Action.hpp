#ifndef ACTION_HPP
#define ACTION_HPP
#include <string>
#include "Player.hpp"
class Action {
public:
    enum class ActionType {
        Arrest,
        Bribe,
        Coup,
        Gather,
        Sanction,
        Tax
    };

private:
    ActionType action;

public:
    Action(ActionType actionType) : action(actionType) {}
    ~Action() = default;
    void playcard(Player& currplayer)const;
    void playcard(Player& currplayer, Player& other)const;
    std::string getactionname() const ;
    bool isType(const std::string& type) const;
};

#endif