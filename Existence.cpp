#include "Existence.h"

int Existence::setPos(int x, int y){
    pos.x = x;
    pos.y = y;
    return 0;
}

Position Existence::getPos(){
    return pos;
}

ExistenceType Existence::getType() {
    return OBJ;
}

int Existence::RunOnce(std::vector<std::vector<Existence*>>& world_matrix) {
    // Do Nothing
    return 0;
}

//---------------------Object---------------------

Object::Object(int x, int y, double life) : Existence() {
    setPos(x, y);
    homeostasis_[LIFE] = life;
}

ExistenceType Object::getType() {
    return type;
}

int Object::setHomeostasis(Homeostasis homeostasis, double value) {
    homeostasis_[homeostasis] = value;
    return 0;
}

double Object::getHomeostasis(Homeostasis homeostasis) {
    return homeostasis_[homeostasis];
}

//---------------------Actant-------------------

Actant::Actant(int x, int y) : Existence() {
    setPos(x, y);
    homeostasis_[LIFE] = 100.0;
    sight = 2;
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

ExistenceType Actant::getType() {
    return type;
}

int Actant::RunOnce(std::vector<std::vector<Existence*>>& world_matrix) {
    // Decrease life 1 per one phase.
    setHomeostasis(LIFE, getHomeostasis(LIFE) - 1.0);

}

int Actant::setHomeostasis(Homeostasis homeostasis, double value) {
    homeostasis_[homeostasis] = value;
    return 0;
}

double Actant::getHomeostasis(Homeostasis homeostasis) {
    return homeostasis_[homeostasis];
}

//---------------------None------------------
ExistenceType None::getType() {
    return type;
}