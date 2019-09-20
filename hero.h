#ifndef HERO_H
#define HERO_H
#include "item.h"
#include "Character.h"
#include <string>
#include <vector>

using namespace std;

class Hero : public Character
{
    friend class MainWindow;
    friend void setStamina(Hero &c, int stam){
        c.stamina = stam;
    }
private:
     bool Sword;
     vector<Item> itemsInCharacter;
     int killcount;
     bool canFight;
     int stamina;
public:
    Hero();
    string longDescription();
    bool victory();
    bool attack(Character *target);
    bool take(Item *taken);
    vector<Item> getItems();
    void setDead();
    int getStamina();
    bool checkStamina();

    template < class T >
    bool fightResult(const T a, const T b){
        if(a > b){
            return true;
        }
        else {
            return false;
        }
    }

    void operator++ (int) {
        killcount++;
    }

    void operator + (Item *item) {
        itemsInCharacter.push_back(*item);
        delete item;
    }
    void operator - (int i) {
        vector<Item>::iterator it = itemsInCharacter.begin();
        for(int z = 0; z < i; z++){
            it++;
        }
        this->itemsInCharacter.erase(it);
    }
};

#endif // HERO_H
