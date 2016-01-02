#ifndef ITEM_WEAPONS_WEAPON
#define ITEM_WEAPONS_WEAPON



#include "../Item.h"
#include "../../StatsCalculations.h"

class Weapon : public Item{


public:

	void restoreData();
	void getItemStats();
	Weapon_struct getStatsStruct();

	Weapon();
	Weapon(Weapon_struct stats);
	Weapon(int item_typ, Weapon_struct stats);
	Weapon(Weapon_struct stats, int hero_rating);
	~Weapon();


	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar  & boost::serialization::base_object<Item>(*this);
		ar  & _stats;
	}

private:

	Weapon_struct _stats;



	//////////////////
	//Magic Numbers!//
	//////////////////


	std::string __DEFAULT_AXE_IMAGE__ = "data\\img\\weapon\\defaultaxe.png";
	std::string __DEFAULT_SWORD_IMAGE__ = "data\\img\\weapon\\defaultsword.png";
	std::string __DEFAULT_SPEAR_IMAGE__ = "data\\img\\weapon\\defaultspear.png";
	std::string __DEFAULT_MACE_IMAGE__ = "data\\img\\weapon\\defaultmace.png";
private:


};


#endif //!ITEM_WEAPONS_WEAPON