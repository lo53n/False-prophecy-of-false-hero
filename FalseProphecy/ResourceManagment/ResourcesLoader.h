#ifndef RESOURCEMANAGEMENT_RESOURCESLOADER
#define RESOURCEMANAGEMENT_RESOURCESLOADER

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <vector>

#include "ResourcesHolder.h"

#include "../Map/MapLoader.h"
#include "../Enemy/EnemiesLoader.h"
#include "../Items/Weapons/WeaponsLoader.h"
#include "../Items/Armours/ArmoursLoader.h"


class ResourcesLoader{

public:
	ResourcesLoader(std::shared_ptr<ErrorHandler> errorHandler);
	~ResourcesLoader();

	void loadGameData();

private:
	ResourcesHolder *_resHolder = &ResourcesHolder::getResourcesHolder();

	std::shared_ptr<ErrorHandler> _errorHandler;



private:





};


#endif //!RESOURCEMANAGEMENT_RESOURCESLOADER