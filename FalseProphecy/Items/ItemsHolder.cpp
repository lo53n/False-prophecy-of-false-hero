#include "ItemsHolder.h"

ItemsHolder::ItemsHolder()
{
}

ItemsHolder& ItemsHolder::getItemsHolder()
{
	static ItemsHolder instance;
	return instance;
}

void ItemsHolder::adjustContainer(int container)
{
	switch (container){
	case CONTAINER::WEAPONS: _weaponsData.shrink_to_fit();
		break;
	case CONTAINER::ARMOURS: _armoursData.shrink_to_fit();
		break;

	}
}

void ItemsHolder::addToWeaponContainter(Weapon_struct data)
{
	std::vector<Weapon_struct>::size_type sz = _weaponsData.capacity();
	_weaponsData.push_back(data);
	if (sz != _weaponsData.capacity()) {
		sz = _weaponsData.capacity();
		std::cout << "capacity changed: " << sz << '\n';
	}
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