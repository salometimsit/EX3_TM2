#ifndef SPECIAL_ACTIONS_HPP
#define SPECIAL_ACTIONS_HPP
#include "Action.hpp"
#include <string>
class SpecialAction: public Action {
    public:
        virtual bool isspecial(const std::string& roleName) const = 0;
};
#endif