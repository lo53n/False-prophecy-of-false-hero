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

void ResourcesHolder::loadData()
{
	loadTilesTexture();
	loadWallsTexture();
	loadDoorsTexture();
}

void ResourcesHolder::loadTilesTexture()
{

	std::string path = "data\\img\\textures\\tiles.png";
	sf::Texture texture;

	texture.loadFromFile(path);

	int tilesNumber = texture.getSize().x / 32, tilesRow = texture.getSize().y / 32;
	for (int j = 0; j < tilesRow; j++){
		for (int i = 0; i < tilesNumber; i++){
			std::shared_ptr<sf::Texture> text(new sf::Texture());
			
			text->loadFromFile(path, sf::IntRect(i * 32, j * 32, 32, 32));
			_tilesTextures.push_back(text);
		}
	}

}

void ResourcesHolder::loadWallsTexture()
{

	std::string path = "data\\img\\textures\\walls.png";
	sf::Texture texture;

	texture.loadFromFile(path);

	int tilesNumber = texture.getSize().x / 32, tilesRow = texture.getSize().y / 32;
	for (int j = 0; j < tilesRow; j++){
		for (int i = 0; i < tilesNumber; i++){
			std::shared_ptr<sf::Texture> text(new sf::Texture());

			text->loadFromFile(path, sf::IntRect(i * 32, j * 32, 32, 32));
			_wallsTextures.push_back(text);
		}
	}

}

void ResourcesHolder::loadDoorsTexture()
{

	std::string path = "data\\img\\textures\\doors.png";
	sf::Texture texture;

	texture.loadFromFile(path);

	int tilesNumber = texture.getSize().x / 32, tilesRow = texture.getSize().y / 32;
	for (int j = 0; j < tilesRow; j++){
		for (int i = 0; i < tilesNumber; i++){
			std::shared_ptr<sf::Texture> text(new sf::Texture());

			text->loadFromFile(path, sf::IntRect(i * 32, j * 32, 32, 32));
			_doorsTextures.push_back(text);
		}
	}

}

sf::Texture& ResourcesHolder::getTileTexture()
{
	int id = _tilesTextures.size();
	auto found = _tilesTextures.at(rand()%id);
	return *found;
}
sf::Texture& ResourcesHolder::getWallTexture()
{
	int id = _wallsTextures.size();
	auto found = _wallsTextures.at(rand() % id);
	return *found;
}
sf::Texture& ResourcesHolder::getDoorTexture()
{
	int id = _doorsTextures.size();
	auto found = _doorsTextures.at(rand() % id);
	return *found;
}