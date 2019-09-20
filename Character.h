#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "item.h"

#include <string>
using namespace std;
#include <vector>
using std::vector;


class Character {
    friend void setHealth(Character &c, int heal){
        c.health = heal;
    }
private:
    string name;
    int health;
    string status;
public:
    bool checkHealth();
	string shortDescription();
    void setName(string name);
    string getName();
    string getStatus();
    void setStatus(string stat);
    int getHealth();
    void setDead();
};


#endif /*CHARACTER_H_*/
