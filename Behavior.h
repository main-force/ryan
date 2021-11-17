#ifndef RYAN_BEHAVIOR_H
#define RYAN_BEHAVIOR_H

#include <unordered_map>
#include "UniqueCharacter.h"

class Behavior {
public:
    Behavior();
    std::unordered_map<Personality, double> personality_property();
    bool IsEscapeBehavior();
protected:
    std::unordered_map<Personality, double> personality_property_;
    bool can_pass_homeostasis_;
};


class BehaviorManager {
public:
    void PassPropertyToActant(std::unordered_map<Personality, double> personality_map, Actant actant);
};


#endif //RYAN_BEHAVIOR_H
