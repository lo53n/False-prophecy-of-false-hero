#include "MapsHolder.h"

MapsHolder::MapsHolder()
{

}

/*static*/ MapsHolder& MapsHolder::getMapsHolder()
{
	static MapsHolder instance;
	return instance;
}





void MapsHolder::addToContainter(std::vector<std::vector<char>> map)
{
	_maps.push_back(map);
}

void MapsHolder::showMaps()
{
	for (int k = 0, len2 = _maps.size(); k < len2; k++){
		for (int j = 0, len1 = _maps[k].size(); j < len1; j++){
			for (int i = 0, len = _maps[k][j].size(); i < len; i++)
				std::cout << _maps[k][j][i];
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}


///////////
//Getters//
///////////

int MapsHolder::getMapCount()
{
	return _maps.size();
}

std::vector<std::vector<char>> MapsHolder::getMapFromHolder(int mapIndex)
{
	return _maps[mapIndex];
}
std::vector<std::vector<std::vector<char>>> MapsHolder::getAllMaps()
{
	return _maps;
}