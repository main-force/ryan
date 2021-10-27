#include <iostream>
#define HOMEOSTASIS_NUM 2
//--------------------------------------

struct Personality {
    double openess; //개방성
    double conscientiousness; //성실성
    double extraversion; //외향성
    double agreeableness; //우호성
    double neuroticism; //신경증
};

struct Homeostasis {
    std::size_t size = HOMEOSTASIS_NUM;

    double life;
    double happiness;
};

class Behavior {
    //TODO
};

class Actant {
public:
    bool isSafe();

private:
    Personality personality;
    Homeostasis homeostasis;
    Behavior behavior;
};

bool Actant::isSafe() {
    bool result;
    if (homeostasis.life <= 20) result = false;
    else result = true;

    return result;
}

//TODO: vector로 위험한 인덱스에 true 반환
Actant::find_danger_element{

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
