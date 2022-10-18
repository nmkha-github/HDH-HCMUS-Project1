#pragma once
#include <iostream>
#include <string>

class ATTRIBUTES
{
protected:
	std::string name;
	int size;
	int type;
	int firstSector;
	int level;

public:
	ATTRIBUTES(std::string name, int size, int level, int firstSector);

	std::string getName();

	int getSize();

	std::string getType();

	int getFirstSector();

	void printID();

	static std::string leveling(int level);
};

