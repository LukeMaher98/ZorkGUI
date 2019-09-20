#ifndef ENEMY_H
#define ENEMY_H
#include "hero.h"
#include "item.h"
#include "Character.h"
#include <string>
#include <vector>

class Enemy : public Character
{
private:
    int attackVal;
    int dodgeVal;
    int maxHealth;
public:
    Enemy(string name, int health, int attackVal, int dodgeVal);
    int getAttackVal();
    void setAttackVal(int attackVal);
    int getDodgeVal();
    void setDodgeVal(int dodgeVal);
    int getMaxHealth();
};

#endif // ENEMY_H
