#ifndef ITEM_CONSUMABLES_CONSUMABLES
#define ITEM_CONSUMABLES_CONSUMABLES



#include "../Item.h"
#include "../../StatsCalculations.h"

class Consumable : public Item{


public:

	void restoreData();

	void getItemStats();
	Consumable_struct getStatsStruct();

	Consumable();
	Consumable(int item_typ, Consumable_struct stats);
	Consumable(Consumable_struct stats);
	~Consumable();

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar  & boost::serialization::base_object<Item>(*this);
		ar  & _stats;
	}
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