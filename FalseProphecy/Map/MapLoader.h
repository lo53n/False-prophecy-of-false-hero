#ifndef MAP_MAPLOADER
#define MAP_MAPLOADER

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <vector>

#include "MapsHolder.h"


class MapLoader{

public:
	MapLoader();
	~MapLoader();
	void loadFromFile();


private:
	std::vector<std::vector<char>> _map;
	MapsHolder *_mapsHolder = &MapsHolder::getMapsHolder();

private:
	void parseMapLine(std::string line);
	void prepareMapVector();

};


#endif //!MAP_MAPLOADER