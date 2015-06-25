#include "ItemsHolder.h"

ItemsHolder::ItemsHolder()
{

}

ItemsHolder& ItemsHolder::getItemsHolder()
{
	static ItemsHolder instance;
	return instance;
}

void ItemsHolder::addToWeaponContainter(Weapon_struct data)
{
	_weaponsData.push_back(data);
}

int ItemsHolder::getWeaponsCount()
{
	return _weaponsData.size();
}