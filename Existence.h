#ifndef RYAN_EXISTENCE_H
#define RYAN_EXISTENCE_H

#include <unordered_map>
#include "UniqueCharacter.h"

enum ExistenceType {
    NONE,
    OBJ,
    ACT,
};

class Position {
public:
    int x;
    int y;
};

class Existence {
public:
    int setPos(int x, int y);
    Position getPos();

    virtual ExistenceType getType();
private:
    Position pos;
};

class Object : public Existence{
public:
    Object(int x, int y);
    ExistenceType getType() override;
private:
    ExistenceType type = OBJ;
    Homeostasis homeostasis_;
    UniqueCharacter unique_character_;
};

class Actant : public Existence{
public:
    Actant(int x, int y);
    bool isSafe();
    UniqueCharacter FindSolverCharacter();
    bool Solve(UniqueCharacter target_character);
    ExistenceType getType() override;
private:
    ExistenceType type = ACT;
    std::unordered_map<Personality, double> personality_;
    std::unordered_map<Homeostasis, double> homeostasis_;
    std::unordered_map<Homeostasis, bool> IsDangerHomeostasisElementMap();
};

class None : public Existence{
public:
    ExistenceType getType() override;
private:
    ExistenceType type = NONE;
};

#endif //RYAN_EXISTENCE_H
