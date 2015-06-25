#ifndef ITEMS_ITEMSHOLDER
#define ITEMS_ITEMSHOLDER


#include <vector>
#include <iostream>

#include "../StructsEnums.h"


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


private:
	ItemsHolder();
	ItemsHolder(ItemsHolder const&);
	void operator=(ItemsHolder const&);



private:
	static ItemsHolder *_itemsHolder;
	std::vector<Weapon_struct> _weaponsData;
	std::vector<Armor_struct> _armorsData;




};

#endif //!ITEMS_ITEMSHOLDER
