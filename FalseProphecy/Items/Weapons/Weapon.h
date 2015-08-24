#ifndef ITEM_WEAPONS_WEAPON
#define ITEM_WEAPONS_WEAPON



#include "../Item.h"
#include "../../StructsEnums.h"

class Weapon : public Item{


public:

	void getItemStats();
	Weapon_struct getStatsStruct();

	Weapon();
	Weapon(Weapon_struct stats);
	~Weapon();

private:

	Weapon_struct _stats;



	//////////////////
	//Magic Numbers!//
	//////////////////


	std::string __DEFAULT_AXE_IMAGE__ = "data\\img\\weapon\\axedefault.png";
	std::string __DEFAULT_SWORD_IMAGE__ = "data\\img\\weapon\\sworddefault.png";
	std::string __DEFAULT_SPEAR_IMAGE__ = "data\\img\\weapon\\speardefault.png";
	std::string __DEFAULT_MACE_IMAGE__ = "data\\img\\weapon\\macedefault.png";
private:


};


#endif //!ITEM_WEAPONS_WEAPON