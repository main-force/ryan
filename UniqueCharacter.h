#ifndef RYAN_UNIQUECHARACTER_H
#define RYAN_UNIQUECHARACTER_H

#include <iostream>

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

// UniqueCharacter은 개체의 고유 속성이자, 외부에서 볼 수 있는 개체의 고유 속성의 집합임.
class UniqueCharacter {
public:
    UniqueCharacter() {
        this->color_ = Color{0,0,0};
    }
    explicit UniqueCharacter(Color color) : color_(color) {}
private:
    Color color_{};
};

#endif //RYAN_UNIQUECHARACTER_H
