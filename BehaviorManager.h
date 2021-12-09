#ifndef RYAN_BEHAVIORMANAGER_H
#define RYAN_BEHAVIORMANAGER_H

#include <unordered_map>
#include "UniqueCharacter.h"
#include "Existence.h"

class BehaviorManager {
public:
    int PassPersonalityToActant(std::unordered_map<Personality, double> personality_map, Actant& actant);
    int PassHomeostasisToActant(std::unordered_map<Homeostasis, double> homeostasis_map, Actant& actant);
};


#endif //RYAN_BEHAVIORMANAGER_H
