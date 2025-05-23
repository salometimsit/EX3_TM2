#include "ActionFactory.hpp"
#include "Action.hpp" // or BaseAction.hpp
#include "AllAction.hpp"


/**
 * @brief Creates an Action object based on the given action name.
 * This function maps string identifiers to their corresponding Action-derived classes.
 * It uses std::make_unique to instantiate the correct class and return it as a unique_ptr.
 * @param actionName The name of the action to instantiate.
 * @return std::unique_ptr<Action> A unique pointer to the created Action object.
 * @throws std::invalid_argument If the action name does not correspond to a known Action type.
 */
std::unique_ptr<Action> ActionFactory::createAction(const std::string& actionName) {
    if (actionName == "Gather") {
        return std::make_unique<Gather>();
    } else if (actionName == "Tax") {
        return std::make_unique<Tax>();
    } else if (actionName == "Bribe") {
        return std::make_unique<Bribe>();
    } else if (actionName == "Coup") {
        return std::make_unique<Coup>();
    } else if (actionName == "Arrest") {
        return std::make_unique<Arrest>();
    } else if (actionName == "Sanction") {
        return std::make_unique<Sanction>();
    } else if (actionName == "Baroninvest") {
        return std::make_unique<Baroninvest>();
    } else if(actionName=="Governorblocktax"){
        return std::make_unique<Governorblocktax>();
    }else {
        throw std::invalid_argument("Invalid action name");
    }
}