#include "Role.hpp"
using std namespace;
Role::Role(Type type) : type_(type) {}
string Role::getrolename() const{
    switch(type_){
        case Type::Governor:return "Governor";
        case Type::Spy:return "Spy";
        case Type::Baron:return "Baron";
        case Type::Judge:return "Judge";
        case Type::Merchant:return "Merchant";
        case Type::General:return "General";
        default:return "Unknown";
    }

}
