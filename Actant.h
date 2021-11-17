#ifndef RYAN_ACTANT_H
#define RYAN_ACTANT_H

#include <unordered_map>
#include "UniqueCharacter.h"

class Actant {
public:
    bool isSafe();
    UniqueCharacter FindSolverCharacter();
    bool Solve(UniqueCharacter target_character);

private:
    std::unordered_map<Personality, double> personality_;
    std::unordered_map<Homeostasis, double> homeostasis_;
    std::unordered_map<Homeostasis, bool> IsDangerHomeostasisElementMap();
};

//---------------------------------



#endif //RYAN_ACTANT_H
