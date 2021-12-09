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

std::unordered_map<Personality, double>& Behavior::getPersonalityPropertyMap() {
    return personality_property_;
}

int Behavior::Start(Actant& actant) {
    // will override.
    return 0;
}

//===================================

int MonitoringHomeostasis::Start(Actant& actant) {
    // 현재 가장 문제인 건 life라고 가정함.
    Homeostasis problem_homeostasis = LIFE;
    double problem_value_before_behave = actant.getHomeostasis(problem_homeostasis);
    SolveIssue(problem_homeostasis, problem_value_before_behave).Start(actant);
}

//===========================================
SolveIssue::SolveIssue(Homeostasis homeostasis, double value) {
    problem_homeostasis = homeostasis;
    value_homeostasis = value;
}

int SolveIssue::Start(Actant& actant) {
    // 값을 기반으로 기억상의 Object/행동/Can't solve  LookAround로 전달함.
    // 근데 그 매커니즘이 중요함...


}

//-----------------------------------------------------
LookAround::LookAround() {
    std::cout << "LookAround called" << std::endl;
    personality_property_[OPENESS] = 0.1;
    can_pass_homeostasis_ = false;
}
//-----------------------------------------------------
