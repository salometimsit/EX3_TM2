#include "RoleFactory.hpp"
#include "AllRole.hpp"
#include "Actions/ActionFactory.hpp"
#include "Actions/AllAction.hpp"
/**
 * @brief Instantiates a Role object based on the provided role name.
 * Maps string identifiers to their corresponding Role-derived classes using std::make_unique.
 * @param roleName The name of the role to instantiate.
 * @return std::unique_ptr<Role> A unique pointer to the created Role object.
 * @throws std::invalid_argument If the role name does not match any known Role type.
 */
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