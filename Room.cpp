#include "Room.h"
#include "Command.h"
#include "enemy.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

Room::Room(string description) {
    this->description = description;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west) {
    if (north != NULL)
        exits["north"] = north;
    if (east != NULL)
        exits["east"] = east;
    if (south != NULL)
        exits["south"] = south;
    if (west != NULL)
        exits["west"] = west;
}

string Room::longDescription() {
    return "room = " + description + ".\n" + displayItem() + "\n" + displayEnemy() + "\n" + exitString();
}

string Room::name() {
    return description;
}

string Room::exitString() {
    string returnString = "exits =";
    for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
        // Loop through map
        returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
    return returnString;
}

Room* Room::nextRoom(Room *aRoom, string direction) {
    map<string, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
    if (next == exits.end())
        return aRoom; // if exits.end() was returned, there's no room in that direction.
    return next->second; // If there is a room, remove the "second" (Room*)
                // part of the "pair" (<string, Room*>) and return it.
}

void Room::addItem(Item *inItem) {
    //cout <<endl;
    //cout << "Just added" + inItem->getLongDescription();
    itemsInRoom.push_back(*inItem);
}

void Room::addEnemy(Enemy *inChar) {
    enemies.push_back(*inChar);
}

string Room::displayItem() {
    string tempString = "items in room = ";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        tempString = "no items in room";
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x].getLongDescription() + "  " ;
            x++;
            }
        }
    return tempString;
    }

string Room::displayEnemy() {
    string tempString = "enemies in room = ";
    int nmez = (enemies.size());
    if (enemies.size() < 1) {
        tempString = "no enemies in room";
    }
    else if (enemies.size() > 0) {
       int x = (0);
        for (int n = nmez; n > 0; n--) {
            tempString = tempString + enemies[x].shortDescription() + "  " + to_string(enemies[x].getHealth()) + "/" + to_string((enemies[x].getMaxHealth()));
            x++;
            }
        }
    return tempString;
}

int Room::numberOfItems() {
    return itemsInRoom.size();
}

vector<Enemy> Room::getEnemy(){
    return enemies;
}

Enemy* Room::enemy() {
    vector <Enemy>::iterator it = enemies.begin();            // change what was 1 to 2
    return &(*it);
}

Item* Room::item() {
    vector <Item>::iterator it = itemsInRoom.begin();            // change what was 1 to 2
    return &(*it);
}

void Room::removeItem() {
    vector <Item>::iterator it = itemsInRoom.begin();            // change what was 1 to 2
    itemsInRoom.erase(it);
}

int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        return false;
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInRoom[x].getLongDescription());
            if (tempFlag == 0) {
                itemsInRoom.erase(itemsInRoom.begin()+x);
                return x;
            }
            x++;
            }
        }
    return -1;
}


