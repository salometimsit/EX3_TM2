#include "Governor.hpp"
bool  Governor::canblock(const std::string& action)const{
    if(action.isType("Tax")){
        return True;
    }
    return False;
}