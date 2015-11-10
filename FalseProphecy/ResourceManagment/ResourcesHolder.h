#ifndef RESOURCEMANAGEMENT_RESOURCESHOLDER
#define RESOURCEMANAGEMENT_RESOURCESHOLDER

#include <vector>
#include <iostream>

#include "../StructsEnums.h"


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

	//get one specific item
	std::vector<std::vector<char>> getMapFromHolder(int mapIndex);

	//set whole containers
	void setData(std::vector<Enemy_Stats> externalData);
	void setData(std::vector<Weapon_struct> externalData);
	void setData(std::vector<Armour_struct> externalData);
	void setData(std::vector<std::vector<std::vector<char>>> externalData);


private:
	static ResourcesHolder *_resHolder;

	//containers
	std::vector<Enemy_Stats> _enemiesData;
	std::vector<Weapon_struct> _weaponsData;
	std::vector<Armour_struct> _armoursData;
	std::vector<std::vector<std::vector<char>>> _mapsData;


private:
	ResourcesHolder();
	ResourcesHolder(ResourcesHolder const&);
	void operator=(ResourcesHolder const&);


};




#endif //!RESOURCEMANAGEMENT_RESOURCESHOLDER