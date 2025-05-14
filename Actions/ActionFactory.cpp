#include "ActionFactory.hpp"
#include "Action.hpp" // or BaseAction.hpp
#include "AllAction.hpp"

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
    } else {
        throw std::invalid_argument("Invalid action name");
    }
}