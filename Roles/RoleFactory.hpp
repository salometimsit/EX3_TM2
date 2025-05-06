#ifndef ROLE_FACTORY_HPP
#define ROLE_FACTORY_HPP

#include "Role.hpp"
#include <string>
#include <stdexcept>
class RoleFactory {
    public:
        static std::unique_ptr<Role> createRole(const std::string& roleName) {
            if (roleName == "Governor") {
                return std::make_unique<Role>(Role::Type::Governor);
            } else if (roleName == "Spy") {
                return std::make_unique<Role>(Role::Type::Spy);
            } else if (roleName == "Baron") {
                return std::make_unique<Role>(Role::Type::Baron);
            } else if (roleName == "General") {
                return std::make_unique<Role>(Role::Type::General);
            } else if (roleName == "Judge") {
                return std::make_unique<Role>(Role::Type::Judge);
            } else if (roleName == "Merchant") {
                return std::make_unique<Role>(Role::Type::Merchant);
            } else {
                throw std::invalid_argument("Invalid role name");
            }
        }
};
#endif