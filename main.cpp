#include <iostream>
#include <vector>
#include <unordered_map>
#define HOMEOSTASIS_NUM 2
#define PERSONALITY_NUM 5
//--------------------------------------

enum Personality {
    OPENESS, //개방성
    CONSCIENTIOUSNESS, //성실성
    EXTRAVERSION, //외향성
    AGREEABLENESS, //우호성
    NEUROTICISM, //신경증
};

enum Homeostasis {
    LIFE,
    HAPPINESS,
};

struct Color {
    int red;
    int green;
    int blue;
};

//---------------------------------

// UniqueCharacter은 개체의 고유 속성이자, 외부에서 볼 수 있는 개체의 고유 속성의 집합임.
class UniqueCharacter {
public:
    explicit UniqueCharacter(Color color) : color_(std::move(color)) {}
private:
    Color color_;
};

class Object {
private:
    Homeostasis homeostasis_;
    UniqueCharacter unique_character_;
};

//=============================================
class Behavior {
public:
    Behavior() {
        Personality personality_arr[PERSONALITY_NUM] =
                { OPENESS, CONSCIENTIOUSNESS, EXTRAVERSION, AGREEABLENESS, NEUROTICISM };
        for(auto personality : personality_arr) {
            personality_property_[personality] = .0;
        }
        can_pass_homeostasis_ = false;
    }
    std::unordered_map<Personality, double> personality_property();
    bool IsEscapeBehavior();
protected:
    std::unordered_map<Personality, double> personality_property_;
    bool can_pass_homeostasis_;
};

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
//Until here. Solve 프로세스 설계할 차례

//==========================================

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

bool Actant::isSafe() {
    if (homeostasis_[LIFE] <= 20) return false;
    else return true;
}

UniqueCharacter Actant::FindSolverCharacter() {
    for(auto kv : IsDangerHomeostasisElementMap()) {
        if(kv.second) {
            // Calculate what character is needed.
        }
    }
    // Test Case임. 나중에는 계산해서 만드는걸로 바꿔야됨.
    return UniqueCharacter(Color{ 255, 100, 0 });
}

bool Actant::Solve(UniqueCharacter target_character) {
    //Solve를 구현하려면, 실 세계가 필요해.. 실세계 구현 방법을 알아내자.
    //Python으로 세계 구현하는게 우선이니까 일단 구현할거임.
    //Socket 통신으로 파이썬과 cpp가 소통할 예정.
}

std::unordered_map<Homeostasis, bool> Actant::IsDangerHomeostasisElementMap() {
    std::unordered_map<Homeostasis, bool> danger_element_map;
    // DoLater 더 간단하게 수정할 수 있음.
    for(auto kv : homeostasis_) {
        bool is_danger = false;
        if (kv.first == LIFE) {
            if(kv.second < 20) {
                is_danger = true;
            }
        }
        danger_element_map.insert({kv.first, is_danger});
    }

    return danger_element_map;
};

class BehaviorManager {
public:
    void PassPropertyToActant(std::unordered_map<Personality, double> personality_map, Actant actant);
};

//--------------------------------------

int main() {

    Actant actant1;
    while(1) {
        if (actant1.isSafe()) {
            //추가적인 일을 하면 됨...
        }
        else  { //안전하지 못한 상태일 때
            UniqueCharacter target_character = actant1.FindSolverCharacter();
            //actant1.Solve(target_character);
        }
        break;
    }

    return 0;
}
