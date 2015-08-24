#include "ItemsHolder.h"

ItemsHolder::ItemsHolder()
{
}

ItemsHolder& ItemsHolder::getItemsHolder()
{
	static ItemsHolder instance;
	return instance;
}

int ItemsHolder::getWeaponsCount()
{
	return _weaponsData.size();
}

void ItemsHolder::setData(std::vector<Weapon_struct> externalData)
{
	_weaponsData = externalData;
}

void ItemsHolder::setData(std::vector<Armour_struct> externalData)
{
	_armoursData = externalData;
}