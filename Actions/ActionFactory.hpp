#ifndef ACTION_FACTORY_HPP
#define ACTION_FACTORY_HPP
#include <memory>
#include <string>
#include <stdexcept>
#include"Action.hpp"
class ActionFactory{
    public:
        static std::unique_ptr<Action> createAction(const std::string& actionName);
};

#endif