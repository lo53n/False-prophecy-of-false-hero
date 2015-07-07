#include "ItemsLoader.h"

void ItemsLoader::loadResources()
{
	loadWeapons();
	loadArmours();

}

void ItemsLoader::loadWeapons()
{
	WeaponsLoader weaponloader;
	weaponloader.loadFromFile();
}

void ItemsLoader::loadArmours()
{
	ArmoursLoader armoursloader;
	armoursloader.loadFromFile();
}