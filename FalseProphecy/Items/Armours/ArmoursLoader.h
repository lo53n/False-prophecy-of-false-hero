#ifndef ITEM_ARMOUR_ARMOURSLOADER
#define ITEM_ARMOUR_ARMOURSLOADER

#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>


#include <stdexcept>


#include "../../StructsEnums.h"
#include "../ItemsHolder.h"



class ArmoursLoader{

public:
	void loadFromFile();

	ArmoursLoader();
	~ArmoursLoader();

private:
	std::vector<Armour_struct> _armoursData;

	enum TAGVALUE{
		NAME,
		IMG,
		TYPE,
		CLASS,
		DEFENCE,
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

	//Current loaded armour

	Armour_struct _currentData;
	int _armourCount = 0;

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




#endif //!ITEM_ARMOR_ARMOURSLOADER