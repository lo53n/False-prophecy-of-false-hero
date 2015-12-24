#ifndef ITEM_CONSUMABLES_CONSUMABLESLOADER
#define ITEM_CONSUMABLES_CONSUMABLESLOADER

#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>


#include <stdexcept>
#include <memory>


#include "../../StatsCalculations.h"
#include "../../Errors/ErrorHandler.h"



class ConsumablesLoader{

public:
	void loadFromFile();

	ConsumablesLoader(std::shared_ptr<ErrorHandler> errorHandler);
	~ConsumablesLoader();
	std::vector<Consumable_struct>& getConsumablesData();
private:

	std::shared_ptr<ErrorHandler> _errorHandler;
	std::string _errorMsg;

	std::vector<Consumable_struct> _consumablesData;

	enum TAGVALUE{
		NAME,
		IMG,
		TYPE,
		EFFECT_TYPE,
		EFFECT_STRENGHT
	};

	//Current loaded armour

	Consumable_struct _currentData;
	int _consumableCount = 0;

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




#endif //!ITEM_CONSUMABLES_CONSUMABLESLOADER