#ifndef ROLE_FACTORY_HPP
#define ROLE_FACTORY_HPP

#include "Role.hpp"
#include "AllRole.hpp"
#include <memory>
#include <string>
#include <stdexcept>
/**
 * @class RoleFactory
 * @brief Factory class responsible for creating Role instances based on role names.
 * 
 * Uses the Factory design pattern to abstract the construction of specific Role subclasses.
 */
class RoleFactory {

    public:
        /**
        * @brief Creates a Role object based on the provided role name.
        * 
        * @param roleName The name of the role to instantiate.
        * @return A unique_ptr to the created Role instance.
        * @throws std::invalid_argument if the role name is unrecognized.
        */
        static std::unique_ptr<Role> createRole(const std::string& roleName);
};
#endif