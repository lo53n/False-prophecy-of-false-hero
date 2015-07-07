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

	void setData(std::vector<Weapon_struct>);
	void setData(std::vector<Armour_struct>);

	void adjustContainer(int container);

	enum CONTAINER{
		WEAPONS,
		ARMOURS,
		CONSUMABLES
	};


	std::vector<Weapon_struct> _weaponsData;
	std::vector<Armour_struct> _armoursData;

private:
	ItemsHolder();
	ItemsHolder(ItemsHolder const&);
	void operator=(ItemsHolder const&);



private:
	static ItemsHolder *_itemsHolder;




};

#endif //!ITEMS_ITEMSHOLDER
