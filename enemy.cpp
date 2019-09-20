#include "hero.h"
#include "item.h"
#include "Character.h"
#include "enemy.h"
#include <string>
#include <vector>

Enemy::Enemy(string name, int health, int attackVal, int dodgeVal)
{
    this->setName(name);
    this->maxHealth = health;
    setHealth(*this, health);
    this->attackVal = attackVal;
    this->dodgeVal = dodgeVal;
    this->setStatus("none");
}

int Enemy::getAttackVal(){
    return this->attackVal;
}

void Enemy::setAttackVal(int attackVal){
    this->attackVal = attackVal;
}

int Enemy::getDodgeVal(){
    return this->dodgeVal;
}

void Enemy::setDodgeVal(int dodgeVal){
    this->dodgeVal = dodgeVal;
}

int Enemy::getMaxHealth(){
    return this->maxHealth;
}


