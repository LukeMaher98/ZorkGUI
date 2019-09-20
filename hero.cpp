#include "hero.h"
#include "item.h"
#include "enemy.h"
#include <string>
#include <vector>
#include <ctime>

Hero::Hero()
{

    this->setName("Hero");
    this->stamina = 500;
    setHealth(*this, 100);
    this->setStatus("none");
    this->Sword = false;
    this->canFight = true;
    this->killcount = 0;

}

int Hero::getStamina(){
    return this->stamina;
}

string Hero::longDescription()
{
  string ret = "\nHealth: " + std::to_string(this->getHealth()) + " Stamina: " + std::to_string(this->getStamina());
  ret += "\n Item list:\n";
  for (vector<Item>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
    ret += (*i).getLongDescription() + ", ";
    ret += "\n";
  return ret;
}

vector<Item> Hero::getItems(){
    return this->itemsInCharacter;
}

bool Hero::victory(){
    if(this->killcount == 4){
       return true;
    }
    else{
        return false;
    }
}

void Hero::setDead(){
    setHealth(*this, 0);
    setStamina(*this, 0);
    this->setStatus("dead");
    this->canFight = false;

}

bool Hero::attack(Character *nme){
    Enemy *target = static_cast<Enemy*>(nme);
    srand(time(0));
    int random = rand() % 11;
    if(this->Sword){
        random += 2;
    }
    if(fightResult(random, target->getDodgeVal())){
        setHealth(*target, target->getHealth() - 10);
        if(target->checkHealth() == false){
            target->setName(target->getName() + "(dead)");
            target->setStatus("dead");
        }
        return true;
    }
    else{
        setHealth(*this, this->getHealth() - target->getAttackVal());
        return false;
    }

}

bool Hero::take(Item *taken){
    if(taken->getLongDescription() == "Sword"){
        this->Sword = true;
        return true;
    }
    else{
        *this + taken;
        return false;
    }
}

bool Hero::checkStamina(){
    if(this->stamina > 0){
        return true;
    }
    else{
        return false;
    }
}


