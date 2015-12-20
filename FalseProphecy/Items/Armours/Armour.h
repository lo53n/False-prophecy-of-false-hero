#ifndef ITEM_ARMOURS_ARMOUR
#define ITEM_ARMOURS_ARMOUR



#include "../Item.h"
#include "../../StatsCalculations.h"

class Armour : public Item{


public:

	void getItemStats();
	Armour_struct getStatsStruct();

	Armour();
	Armour(Armour_struct stats);
	Armour(Armour_struct stats, int hero_rating);
	~Armour();

private:

	Armour_struct _stats;



	//////////////////
	//Magic Numbers!//
	//////////////////


	std::string __DEFAULT_HELMET_IMAGE__ = "data\\img\\armour\\defaulthelmet.png";
	std::string __DEFAULT_CHEST_IMAGE__ = "data\\img\\armour\\defaultchest.png";
	std::string __DEFAULT_LEGS_IMAGE__ = "data\\img\\armour\\defaultlegs.png";
	std::string __DEFAULT_SHIELD_IMAGE__ = "data\\img\\armour\\defaultshield.png";
private:


};


#endif //!ITEM_ARMOURS_ARMOUR