#ifndef RESOURCEMANAGEMENT_RESOURCESHOLDER
#define RESOURCEMANAGEMENT_RESOURCESHOLDER

#include <vector>
#include <iostream>
#include <memory>


#include <SFML\Graphics.hpp>


#include "../StructsEnums.h"
#include "../LoadFromResource.h"


class ResourcesHolder{
public:
	static ResourcesHolder& getResourcesHolder();

	//put into containers
	void addToContainer(Enemy_Stats data);
	void addToContainer(std::vector<std::vector<char>> map);


	//get containers count
	int getEnemiesCount();
	int getMapsCount();

	//get containers
	std::vector<std::vector<std::vector<char>>> getAllMaps();
	std::vector<Enemy_Stats> getAllEnemies();
	std::vector<Weapon_struct> getAllWeapons();
	std::vector<Armour_struct> getAllArmours();
	std::vector<Consumable_struct> getAllConsumables();

	//get one specific item
	std::vector<std::vector<char>> getMapFromHolder(int mapIndex);

	//set whole containers
	void setData(std::vector<Enemy_Stats> externalData);
	void setData(std::vector<Weapon_struct> externalData);
	void setData(std::vector<Armour_struct> externalData);
	void setData(std::vector<Consumable_struct> externalData);
	void setData(std::vector<std::vector<std::vector<char>>> externalData);


	//load data
	void loadData();


	void loadTilesTexture();
	void loadWallsTexture();
	void loadDoorsTexture();
	/*void loadWeaponsTexture();
	void loadArmoursTexture();
	void loadEnemiesAliveTexture();
	void loadEnemiesDeadTexture();
	void loadTilesTexture();*/

	//get texture
	
	sf::Texture& getTileTexture();
	sf::Texture& getWallTexture();
	sf::Texture& getDoorTexture();

public:

private:
	static ResourcesHolder *_resHolder;

	//containers
	std::vector<Enemy_Stats> _enemiesData;
	std::vector<Weapon_struct> _weaponsData;
	std::vector<Armour_struct> _armoursData;
	std::vector<Consumable_struct> _consumablesData;
	std::vector<std::vector<std::vector<char>>> _mapsData;


	std::vector<std::shared_ptr<sf::Texture>> _tilesTextures;
	std::vector<std::shared_ptr<sf::Texture>> _wallsTextures;
	std::vector<std::shared_ptr<sf::Texture>> _doorsTextures;



private:
	ResourcesHolder();
	ResourcesHolder(ResourcesHolder const&);
	void operator=(ResourcesHolder const&);


};




#endif //!RESOURCEMANAGEMENT_RESOURCESHOLDER