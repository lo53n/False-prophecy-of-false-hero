#ifndef ITEM_CONSUMABLES_CONSUMABLES
#define ITEM_CONSUMABLES_CONSUMABLES



#include "../Item.h"
#include "../../StatsCalculations.h"

class Consumable : public Item{


public:

	void getItemStats();
	Consumable_struct getStatsStruct();

	Consumable();
	Consumable(Consumable_struct stats);
	~Consumable();

private:

	Consumable_struct _stats;



	//////////////////
	//Magic Numbers!//
	//////////////////


	std::string __DEFAULT_PILL_IMAGE__ = "data\\img\\consumable\\defaultpill.png";
	std::string __DEFAULT_POTION_IMAGE__ = "data\\img\\consumable\\defaultpotion.png";
	std::string __DEFAULT_FOOD_IMAGE__ = "data\\img\\consumable\\defaultfood.png";
private:


};


#endif //!ITEM_CONSUMABLES_CONSUMABLES