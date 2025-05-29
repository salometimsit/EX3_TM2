//timsitmelosa@gmail.com
#ifndef SPECIAL_ACTIONS_HPP
#define SPECIAL_ACTIONS_HPP
#include "Action.hpp"
#include <string>

/**
 * @class SpecialAction
 * @brief Abstract class for role-specific special actions.
 * 
 * Inherits from Action and adds a method to determine if the action is valid
 * for a specific role. Used for actions that are only available to certain roles.
 */
class SpecialAction: public Action {
    public:
        /**
        * @brief Determines whether the action is special for the given role.
        * 
        * @param roleName Name of the role to check against.
        * @return true if the action is special for the specified role, false otherwise.
        */
        virtual bool isspecial(const std::string& roleName) const = 0;
};
#endif