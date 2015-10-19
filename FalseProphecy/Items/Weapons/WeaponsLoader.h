#ifndef ITEMS_WEAPONS_WEAPONSLOADER
#define ITEMS_WEAPONS_WEAPONSLOADER

#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>


#include <stdexcept>
#include <memory>


#include "../../StructsEnums.h"
#include "../ItemsHolder.h"
#include "../../Errors/ErrorHandler.h"

class WeaponsLoader{

public:


	void loadFromFile();

	std::vector<Weapon_struct>& getWeaponsData();

	WeaponsLoader(std::shared_ptr<ErrorHandler> errorHandler);
	~WeaponsLoader();

private:

	std::shared_ptr<ErrorHandler> _errorHandler;
	std::string _errorMsg;

	std::vector<Weapon_struct> _weaponsData;


	enum TAGVALUE{
		NAME,
		IMG,
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

	//current loaded weapon
	Weapon_struct _currentData;
	int _weaponCount = 0;

	//Magic Numbers
	int __UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ = 1000;

	int __BASE_PRIMARY_ONEHANDED_MULTIPLIER__ = 50;
	int __BASE_SECONDARY_ONEHANDED_MULTIPLIER__ = 25;

	int __BASE_PRIMARY_TWOHANDED_MULTIPLIER__ = 100;
	int __BASE_SECONDARY_TWOHANDED_MULTIPLIER__ = 50;

private:
	void parseLine(std::string stringLine);
	void parseTag(std::vector<std::string> &output);
	int checkTag(std::string tag);

	void prepareStruct();

	void saveStruct();

	bool checkStructCorrectness();
	bool correctStruct(int tag);

	void showStruct();

};



#endif //!ITEMS_WEAPONS_WEAPONSLOADER