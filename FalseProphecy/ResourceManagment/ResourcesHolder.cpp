#include "ResourcesHolder.h"

ResourcesHolder::ResourcesHolder()
{

}

ResourcesHolder& ResourcesHolder::getResourcesHolder()
{
	static ResourcesHolder instance;
	return instance;
}


int ResourcesHolder::getEnemiesCount()
{
	return _enemiesData.size();
}

int ResourcesHolder::getMapsCount()
{
	return _mapsData.size();
}


//get all items
std::vector<std::vector<std::vector<char>>> ResourcesHolder::getAllMaps()
{
	return _mapsData;
}
std::vector<Enemy_Stats> ResourcesHolder::getAllEnemies()
{
	return _enemiesData;
}
std::vector<Weapon_struct> ResourcesHolder::getAllWeapons()
{
	return _weaponsData;
}
std::vector<Armour_struct> ResourcesHolder::getAllArmours()
{
	return _armoursData;
}


//get single item
std::vector<std::vector<char>> ResourcesHolder::getMapFromHolder(int mapIndex)
{
	return _mapsData[mapIndex];
}

//set whole containers
void ResourcesHolder::setData(std::vector<Enemy_Stats> externalData)
{
	_enemiesData = externalData;
}
void ResourcesHolder::setData(std::vector<Weapon_struct> externalData)
{
	_weaponsData = externalData;
}
void ResourcesHolder::setData(std::vector<Armour_struct> externalData)
{
	_armoursData = externalData;
}
void ResourcesHolder::setData(std::vector<std::vector<std::vector<char>>> externalData)
{
	_mapsData = externalData;
}