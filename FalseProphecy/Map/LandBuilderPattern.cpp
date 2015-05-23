#include "LandBuilderPattern.h"

LandBuilder::LandBuilder()
{

}

LandBuilder::~LandBuilder()
{

}

Map& LandBuilder::getMap() 
{
	return *_map; 
}

void LandBuilder::setMap(Map* map)
{
	_map = map;
}


