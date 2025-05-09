#include "ActionFactory.hpp"
std::unique_ptr<Action> ActionFactory::createAction(const std::string& actionName) {
    if (actionName == "Gather") {
        return std::make_unique<Action>(Action::ActionType::Gather);
    } else if (actionName == "Tax") {
        return std::make_unique<Action>(Action::ActionType::Tax);
    } else if (actionName == "Bribe") {
        return std::make_unique<Action>(Action::ActionType::Bribe);
    } else if (actionName == "Coup") {
        return std::make_unique<Action>(Action::ActionType::Coup);
    } else if (actionName == "Arrest") {
        return std::make_unique<Action>(Action::ActionType::Arrest);
    } else if (actionName == "Sanction") {
        return std::make_unique<Action>(Action::ActionType::Sanction);
    }
    
    else{
        throw std::invalid_argument("Invalid action name");
    }
}