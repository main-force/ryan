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

//---------------------------------------
class Behavior { // Until here. 행동 클래스 여러개 제작해야함.
public:
    explicit Behavior(std::unordered_map<Personality, double> personality_property)
        : personality_property_(std::move(personality_property)) {}
    virtual std::unordered_map<Personality, double> PassPersonalityProperty() const = 0;
private:
    std::unordered_map<Personality, double> personality_property_;
};

class LookAround : public Behavior {

};

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

std::unordered_map<Homeostasis, bool> Actant::IsDangerHomeostasisElementMap() {
    std::unordered_map<Homeostasis, bool> danger_element_map;
    // Do Later 더 간단하게 수정할 수 있음.
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
            actant1.Solve(target_character);
        }
        break;
    }

    return 0;
}
