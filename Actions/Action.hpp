#ifndef ACTION_HPP
#define ACTION_HPP

#include <string>
class Player;
class Game;

class Action {
public:
    virtual void playcard(Player& currplayer) const = 0;
    virtual void playcard(Player& currplayer, Player& other) const = 0;
    virtual std::string getactionname() const = 0;
    virtual bool isType(const std::string& type) const = 0;
    virtual ~Action() = default;
};

#endif