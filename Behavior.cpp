#include "Behavior.h"
#define HOMEOSTASIS_NUM 2
#define PERSONALITY_NUM 5

Behavior::Behavior() {
    Personality personality_arr[PERSONALITY_NUM] =
            { OPENESS, CONSCIENTIOUSNESS, EXTRAVERSION, AGREEABLENESS, NEUROTICISM };
    for(auto personality : personality_arr) {
        personality_property_[personality] = .0;
    }
    can_pass_homeostasis_ = false;
}

bool Behavior::IsEscapeBehavior(){
    return can_pass_homeostasis_;
}

std::unordered_map<Personality, double> Behavior::personality_property(){
    return personality_property_;
}

//----------------------------------------
class LookAround : public Behavior {
public:
    LookAround() {
        std::cout << "LookAround called" << std::endl;
        personality_property_[OPENESS] = 0.1;
        can_pass_homeostasis_ = false;
    }
};