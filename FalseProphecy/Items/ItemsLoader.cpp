#include "ItemsLoader.h"

void ItemsLoader::loadResources()
{
	loadWeapons();

}

void ItemsLoader::loadWeapons()
{
	WeaponsLoader weaponloader;
	weaponloader.loadFromFile();
}