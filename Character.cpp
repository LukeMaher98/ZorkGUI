#include "Character.h"


using namespace std;

string Character::shortDescription()
{
  return this->name;
}

int Character::getHealth(){
    return this->health;
}

void Character::setName(string name){
    this->name = name;
}

string Character::getName(){
    return this->name;
}

string Character::getStatus(){
    return this->status;
}

void Character::setStatus(string stat){
    this->status = stat;
}

bool Character::checkHealth(){
    if(this->health > 0){
        return true;
    }
    else{
        return false;
    }
}

void Character::setDead(){
    this->health = 0;
    this->status = "dead";
}







