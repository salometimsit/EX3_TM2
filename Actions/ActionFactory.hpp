#ifndef ACTION_FACTORY_HPP
#define ACTION_FACTORY_HPP

#include <memory>
#include <string>
#include <stdexcept>
#include "Action.hpp"

/**
 * @class ActionFactory
 * @brief Factory class for creating Action objects.
 * 
 * Provides a static method to instantiate Action-derived objects based on a given action name.
 */
class ActionFactory {
public:
    /**
     * @brief Creates an instance of a derived Action class.
     * This static method selects and constructs the appropriate Action subclass
     * based on the provided action name string.
     * @param actionName The name of the action to create.
     * @return A unique_ptr to the created Action object.
     * @throws std::invalid_argument if the actionName does not match any known action types.
     */
    static std::unique_ptr<Action> createAction(const std::string& actionName);
};

#endif
