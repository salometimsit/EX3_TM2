#include "RoleFactory.hpp"
#include "AllRole.hpp"
#include "Actions/ActionFactory.hpp"
#include "Actions/AllAction.hpp"
std::unique_ptr<Role> RoleFactory::createRole(const std::string& roleName) {
    if (roleName == "Governor") {
        return std::make_unique<Governor>();
    } else if (roleName == "Spy") {
        return std::make_unique<Spy>();
    } else if (roleName == "Baron") {
        return std::make_unique<Baron>();
    } else if (roleName == "General") {
        return std::make_unique<General>();
    } else if (roleName == "Judge") {
        return std::make_unique<Judge>();
    } else if (roleName == "Merchant") {
        return std::make_unique<Merchant>();
    } else {
        throw std::invalid_argument("Invalid role name");
    }
}