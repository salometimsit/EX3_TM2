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
Role* RoleFactory::createRole(const std::string& roleName) {
    if (roleName == "Governor") {
        return new Governor();
    } else if (roleName == "Spy") {
        return new Spy();
    } else if (roleName == "Baron") {
        return new Baron();
    } else if (roleName == "General") {
        return new General();
    } else if (roleName == "Judge") {
        return new Judge();
    } else if (roleName == "Merchant") {
        return new Merchant();
    } else {
        throw std::invalid_argument("Invalid role name");
    }
}