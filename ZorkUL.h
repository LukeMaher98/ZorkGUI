#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
using namespace std;

class ZorkUL {
private:
	Parser parser;
    Room *aPtr, *bPtr, *cPtr, *dPtr, *ePtr, *fPtr, *gPtr, *hPtr, *iPtr;
	bool processCommand(Command command);
	void printHelp();
    string goRoom(Room *aRoom, Command command);
    void createItems();
    void displayItems();

public:
    ZorkUL();
	void play();
    string go(Room *aRoom, string direction);
    string teleport();
    void createRooms();
    string printWelcome();
    string map();
    Room *currentRoom;
};

#endif /*ZORKUL_H_*/
