#include "MapBuilderPattern.h"

MapBuilder::MapBuilder() 
	: _landbuilder(NULL)
{

}
MapBuilder::~MapBuilder()
{

}

///////////
//Getters//
///////////
LandBuilder* MapBuilder::getLandBuilder()
{
	return _landbuilder; 
};

Map& MapBuilder::getMap()
{ 
	return _landbuilder->getMap(); 
}
///////////
//Setters//
///////////
void MapBuilder::setLandBuilder(LandBuilder* lb)
{
	_landbuilder = lb;
}

void MapBuilder::buildMap(std::vector<std::vector<char>> *mapTemplate)
{

	for (int k = 0, len2 = mapTemplate->size(); k < len2; k++){
		for (int j = 0, len1 = (*mapTemplate)[k].size(); j < len1; j++){
			std::cout << (*mapTemplate)[k][j];
		}
		std::cout << std::endl;
	}
}