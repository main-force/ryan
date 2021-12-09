#ifndef RYAN_BEHAVIOR_H
#define RYAN_BEHAVIOR_H

#include <unordered_map>
#include "Existence.h"
#include "UniqueCharacter.h"

// 이건 다른 행동들을 만들기 위한 클래스일 뿐..
class Behavior {
public:
    Behavior();
    bool IsEscapeBehavior();
    std::unordered_map<Personality, double>& getPersonalityPropertyMap();
    virtual int Start(Actant& actant);
protected:
    std::unordered_map<Personality, double> personality_property_;
    std::unordered_map<std::string, std::function<int(Behavior&, Actant&)>> available_behavior_map;
    bool can_pass_homeostasis_;
};
// ---------------------------------------------------------------

class MonitoringHomeostasis : public Behavior {
public:
    int Start(Actant& actant) override;
};

class SolveIssue : public Behavior {
public:
    SolveIssue(Homeostasis homeostasis, double value);
    int Start(Actant& actant) override;
private:
    Homeostasis problem_homeostasis;
    double value_homeostasis;
};

class LookAround : public Behavior {
public:
    LookAround();
};

//Root behavior은 lookup 또는 DoNothing 임.



#endif //RYAN_BEHAVIOR_H
