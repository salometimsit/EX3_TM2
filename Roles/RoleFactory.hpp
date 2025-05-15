#ifndef ROLE_FACTORY_HPP
#define ROLE_FACTORY_HPP

#include "Role.hpp"
#include "AllRole.hpp"
#include <memory>
#include <string>
#include <stdexcept>
class RoleFactory {

    public:
        static std::unique_ptr<Role> createRole(const std::string& roleName);
};
#endif