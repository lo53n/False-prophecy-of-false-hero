#ifndef ITEMS_WEAPONS_WEAPONSLOADER
#define ITEMS_WEAPONS_WEAPONSLOADER

#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>


#include "../../StructsEnums.h"

class WeaponsLoader{

public:


	void loadFromFile();



	WeaponsLoader();
	~WeaponsLoader();

private:
	enum TAGVALUE{
		NAME,
		HANDLE,
		SIZE,
		TYPE,
		PRIMARY_MULTIPLIER,
		PRIMARY_MULTIPLIER_VALUE,
		SECONDARY_MULTIPLIER,
		SECONDARY_MULTIPLIER_VALUE,
		SPEED,
		MIN_DMG,
		MAX_DMG,
		STR_REQ,
		END_REQ,
		AGI_REQ,
		DEX_REQ,
		INT_REQ,
		WIL_REQ,
	};

	//std::vector<std::string> weaponvector;
	std::vector<std::string> output;

	Weapon_struct currentData;

private:
	void parseLine(std::string stringLine);
	void parseTag(std::vector<std::string> &output);
	int checkTag(std::string tag);
	void prepareStruct();

	void showStruct();

};



#endif //!ITEMS_WEAPONS_WEAPONSLOADER