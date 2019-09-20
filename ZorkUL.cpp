#include <iostream>
#include <ctime>
#include <QApplication>

using namespace std;
#include "ZorkUL.h"
#include "enemy.h"

ZorkUL::ZorkUL() {
    createRooms();
}

void ZorkUL::createRooms()  {

    aPtr = new Room("a");
        aPtr->addItem(new Item("Health Potion", 1, 1));
    bPtr = new Room("b");
        bPtr->addEnemy(new Enemy("Necromancer", 100, 9, 6));
    cPtr = new Room("c");
        cPtr->addItem(new Item("Stamina Potion", 1, 1));
    dPtr = new Room("d");
        dPtr->addEnemy(new Enemy("Goblin", 80, 8, 7));
    ePtr = new Room("e");
        ePtr->addEnemy(new Enemy("Succubus", 90, 12, 5));
    fPtr = new Room("f");
        fPtr->addItem(new Item("Sword", 1, 1));
    gPtr = new Room("g");
        gPtr->addEnemy(new Enemy("Cyclops", 130, 10, 4));
    hPtr = new Room("h");
    iPtr = new Room("i");

//             (N, E, S, W)
    aPtr->setExits(fPtr, bPtr, dPtr, cPtr);
    bPtr->setExits(NULL, NULL, NULL, aPtr);
    cPtr->setExits(NULL, aPtr, NULL, NULL);
    dPtr->setExits(aPtr, ePtr, NULL, iPtr);
    ePtr->setExits(NULL, NULL, NULL, dPtr);
    fPtr->setExits(NULL, gPtr, aPtr, hPtr);
    gPtr->setExits(NULL, NULL, NULL, fPtr);
    hPtr->setExits(NULL, fPtr, NULL, NULL);
    iPtr->setExits(NULL, dPtr, NULL, NULL);

    currentRoom = aPtr;

}

/**
 *  Main play routine.  Loops until end of play.
 */

string ZorkUL::map(){
    return "[h] --- [f] --- [g]\n            |         \n            |         \n[c] --- [a] --- [b]\n            |         \n            |         \n[i] --- [d] --- [e]\n\n";
}

string ZorkUL::goRoom(Room *aRoom,Command command) {
	if (!command.hasSecondWord()) {
        return "incomplete input";
	}

	string direction = command.getSecondWord();

	// Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(aRoom, direction);

	if (nextRoom == NULL)
        return "underdefined input";
	else {
		currentRoom = nextRoom;
        return currentRoom->longDescription();
	}
}

string ZorkUL::printWelcome() {
    return "*WELCOME TO ZORK*\n\n" + currentRoom->longDescription() + "\n\n";
}


string ZorkUL::go(Room *aRoom, string direction) {
	//Make the direction lowercase
	//transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
	//Move to the next room
    Room* nextRoom = currentRoom->nextRoom(aRoom, direction);
    if (nextRoom == aRoom)
        return("direction null\n" + currentRoom->longDescription() + "\n");
	else
	{
		currentRoom = nextRoom;
        return currentRoom->longDescription() + "\n";
	}
}

string ZorkUL::teleport() {
    srand(time(0));
    Room* rooms[] = {aPtr, bPtr, cPtr, dPtr, ePtr, fPtr, gPtr, hPtr, iPtr};
    int random = rand() % 9;
    currentRoom = rooms[random];
    return currentRoom->longDescription() + "\n\n";
    }


