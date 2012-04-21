#ifndef ENTITY_H
#define ENTITY_H

#include <string>
using namespace std;

class Entity {
protected:
	string *name;

public:
	Entity(string *name = 0) {this->name = name;}

	string *getName() {return name;}
	void setName(string newName) {if (name != 0) *name=newName; else name = new string(newName);}
};

#endif