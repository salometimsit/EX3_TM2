#include "Role.hpp"

// Provide a definition for the virtual destructor
Role::~Role() {}

std::unique_ptr<SpecialAction> Role::getspecial(Game&, Player&, Player*) const {
    return nullptr;
}