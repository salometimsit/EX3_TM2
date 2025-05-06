#ifndef GENERAL_HPP
#define GENERAL_HPP
#include "ActionStrategy.hpp"
#include "Player.hpp"
#include "Rolestrategy.hpp"

class General:public Rolestrategy{
    public: 
        virtual std::string getrolename()override const{return "General"};
        virtual bool isrole(const std::string& type)const{return getrolename()==type();}
        virtual bool canblock(const std::string& action)const;
};
#endif















