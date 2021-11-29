#include "Existence.h"

int Existence::setPos(int x, int y){
    pos.x = x;
    pos.y = y;
    return 0;
}

Position Existence::getPos(){
    return pos;
}

Object::Object(int x, int y) : Existence() {
    setPos(x, y);
    homeostasis_ = LIFE;
}

//----------------------------------------------

Actant::Actant(int x, int y) : Existence() {
    setPos(x, y);
}

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
    //Socket 통신으로 파이썬과 cpp가 소통할 예정.
    return true;
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
}