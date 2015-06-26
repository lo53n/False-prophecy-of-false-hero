#ifndef ITEMS_ITEMSHOLDER
#define ITEMS_ITEMSHOLDER


#include <vector>
#include <iostream>

#include "../StructsEnums.h"
#include "Weapons/WeaponsLoader.h"


class ItemsHolder{

public:
	static ItemsHolder& getItemsHolder();
	void addToWeaponContainter(Weapon_struct data);

	int getWeaponsCount();
	int getTotalItemsCount();

	void adjustContainer(int container);

	enum CONTAINER{
		WEAPONS,
		ARMORS,
		CONSUMABLES
	};


	std::vector<Weapon_struct> _weaponsData;

private:
	ItemsHolder();
	ItemsHolder(ItemsHolder const&);
	void operator=(ItemsHolder const&);



private:
	static ItemsHolder *_itemsHolder;
	std::vector<Armor_struct> _armorsData;




};

#endif //!ITEMS_ITEMSHOLDER
