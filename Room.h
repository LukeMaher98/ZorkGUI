#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "enemy.h"
using namespace std;
using std::vector;

class Room {

private:
	string description;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;
    vector <Enemy> enemies;

public:
    vector<Enemy> getEnemy();
    void removeItem();
    Item* item();
    int numberOfItems();
    int numberOfEnemies();
    Enemy* enemy();
	Room(string description);
	void setExits(Room *north, Room *east, Room *south, Room *west);
    string longDescription();
    Room* nextRoom(Room *aRoom, string direction);
    void addItem(Item *inItem);
    void addEnemy(Enemy *inChar);
    string displayItem();
    string displayEnemy();
    int isItemInRoom(string inString);
    string name();
};

#endif
