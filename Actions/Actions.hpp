/**
This class is going to be a Factory class for all types of cards in the game 
 */
#ifindef ACTIONS_HPP
#define ACTIONS_HPP
#include <string>
class Action{
    private:
        std::string actionname;
    public:
        Action(const std::string& actionName) : name(actionname) {}
        std::string getName() const { return actionname; }
        bool isType(const std::string& type) const {
            return name == type;
        }
}
#endif