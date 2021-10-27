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

class Behavior {
    //TODO
};

class Actant {
public:
    bool isSafe();
    std::unordered_map<Homeostasis, bool> danger_homeostasis_element_map();

private:
    std::unordered_map<Personality, double> personality;
    std::unordered_map<Homeostasis, double> homeostasis;
    Behavior behavior;
};

bool Actant::isSafe() {
    bool result;
    if (homeostasis[LIFE] <= 20) result = false;
    else result = true;

    return result;
}

// Until Here.
std::unordered_map<Homeostasis, bool> Actant::danger_homeostasis_element_map() {
    std::unordered_map<Homeostasis, bool> danger_element_map;
    for(auto kv : homeostasis) {
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

//--------------------------------------
struct Color {
    int red;
    int green;
    int blue;
};

class UniqueCharacteristic {
private:
    Color color;
};

class Object {
private:
    Homeostasis homeostasis;
    UniqueCharacteristic unique_characteristic;
};


//---------------------------------------
int main() {

    Actant actant1;
    while(1) {
        if (actant1.isSafe()) {
            //추가적인 일을 하면 됨...
        }
        else  { //안전하지 못한 상태일 때

        }
        break;
    }

    return 0;
}
