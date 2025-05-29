//timsitmelosa@gmail.com
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
Action* ActionFactory::createAction(const std::string& actionName)  {
    if (actionName == "Gather") {
        return new Gather();
    } else if (actionName == "Tax") {
        return new Tax();
    } else if (actionName == "Bribe") {
        return new Bribe();
    } else if (actionName == "Coup") {
        return new Coup();
    } else if (actionName == "Arrest") {
        return new Arrest();
    } else if (actionName == "Sanction") {
        return new  Sanction();
    } else if (actionName == "Baroninvest") {
        return new Baroninvest();
    } else if(actionName=="Governorblocktax"){
        return new Governorblocktax();
    }else if (actionName == "Judgeblockbribe") {
    return new Judgeblockbribe();
    }else {
        throw std::invalid_argument("Invalid action name");
    }
}