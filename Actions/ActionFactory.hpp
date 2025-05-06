#ifndef ACTION_FACTORY_HPP
#define ACTION_FACTORY_HPP

#include <string>
#include <stdexcept>
class Actionfactory{
    public:
        static std::unique_ptr<Actionstrategy> createAction(const std::string& actionName) {
            if (actionName == "Gather") {
                return std::make_unique<Gather>();
            } else if(actionName=="Tax"){
                return std::make_unique<Tax>();
            }else if(actionName=="Bribe"){
                return std::make_unique<Bribe>();
            } else if (actionName == "Arrest") {
                return std::make_unique<Arrest>();
            }else if (actionName == "Sanction") {
                return std::make_unique<Sanction>();
            }else if (actionName == "Coup") {
                return std::make_unique<Coup>();
            }
            else{
                throw std::invalid_argument("Invalid action name");
            }
};
#endif