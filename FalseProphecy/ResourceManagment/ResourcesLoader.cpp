#include "ResourcesLoader.h"

ResourcesLoader::ResourcesLoader(std::shared_ptr<ErrorHandler> errorHandler)
	:
	_errorHandler(errorHandler)
{

}

ResourcesLoader::~ResourcesLoader()
{

}


void ResourcesLoader::loadGameData()
{
	MapLoader mapLoader;
	mapLoader.loadFromFile();
	_resHolder->setData(mapLoader.getMapsData());
	_resHolder->setData(mapLoader.loadSpecialMaps(), true);

	EnemiesLoader enemiesLoader(_errorHandler);
	enemiesLoader.loadFromFile();
	_resHolder->setData(enemiesLoader.getEnemiesData());
	_resHolder->setData(enemiesLoader.getSpecialEnemiesData(), true);

	WeaponsLoader weaponsLoader(_errorHandler);
	weaponsLoader.loadFromFile();
	_resHolder->setData(weaponsLoader.getWeaponsData());

	ArmoursLoader armoursLoader(_errorHandler);
	armoursLoader.loadFromFile();
	_resHolder->setData(armoursLoader.getArmoursData());

	ConsumablesLoader consumablesLoader(_errorHandler);
	consumablesLoader.loadFromFile();
	_resHolder->setData(consumablesLoader.getConsumablesData());
}