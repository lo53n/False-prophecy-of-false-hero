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
	std::vector<std::vector<std::vector<char>>> getSpecialMaps();

	std::vector<Enemy_Stats> getAllEnemies();
	std::vector<Enemy_Stats> getSpecialEnemies();

	std::vector<Weapon_struct> getAllWeapons();
	std::vector<Weapon_struct> getSpecialWeapons();

	std::vector<Armour_struct> getAllArmours();
	std::vector<Armour_struct> getSpecialArmours();

	std::vector<Consumable_struct> getAllConsumables();
	std::vector<Consumable_struct> getSpecialConsumables();

	//get one specific item
	std::vector<std::vector<char>> getMapFromHolder(int mapIndex);

	//set whole containers
	void setData(std::vector<Enemy_Stats> externalData, bool special = false);
	void setData(std::vector<Weapon_struct> externalData, bool special = false);
	void setData(std::vector<Armour_struct> externalData, bool special = false);
	void setData(std::vector<Consumable_struct> externalData, bool special = false);
	void setData(std::vector<std::vector<std::vector<char>>> externalData, bool special = false);


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
	std::vector<Enemy_Stats> _specialEnemiesData;

	std::vector<Weapon_struct> _weaponsData;
	std::vector<Weapon_struct> _specialWeaponsData;

	std::vector<Armour_struct> _armoursData;
	std::vector<Armour_struct> _specialArmoursData;

	std::vector<Consumable_struct> _consumablesData;
	std::vector<Consumable_struct> _specialConsumablesData;

	std::vector<std::vector<std::vector<char>>> _mapsData;
	std::vector<std::vector<std::vector<char>>> _specialMapsData;


	std::vector<std::shared_ptr<sf::Texture>> _tilesTextures;
	std::vector<std::shared_ptr<sf::Texture>> _wallsTextures;
	std::vector<std::shared_ptr<sf::Texture>> _doorsTextures;



private:
	ResourcesHolder();
	ResourcesHolder(ResourcesHolder const&);
	void operator=(ResourcesHolder const&);


};




#endif //!RESOURCEMANAGEMENT_RESOURCESHOLDER