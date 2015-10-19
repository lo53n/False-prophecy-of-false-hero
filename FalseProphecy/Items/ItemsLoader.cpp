#include "ItemsLoader.h"



ItemsLoader::ItemsLoader(std::shared_ptr<ErrorHandler> handler)
	:
	_errorHandler(handler)
{

}

void ItemsLoader::loadResources()
{
	loadWeapons();
	loadArmours();

}

void ItemsLoader::loadWeapons()
{
	WeaponsLoader weaponloader(_errorHandler);
	weaponloader.loadFromFile();
}

void ItemsLoader::loadArmours()
{
	ArmoursLoader armoursloader(_errorHandler);
	armoursloader.loadFromFile();
}