#include "MapLoader.h"


MapLoader::MapLoader()
{

}

MapLoader::~MapLoader()
{

}

void MapLoader::loadFromFile()
{

	std::fstream mapFile;

	mapFile.open("data/map.txt");
	if (!mapFile.good()) return;

	std::string stringLine;

	prepareMapVector();
	while (!mapFile.eof()){
		std::getline(mapFile, stringLine);
		if (stringLine != "[---]"){
			parseMapLine(stringLine);
		}
		else{
			_mapsHolder->addToContainter(_map);
			prepareMapVector();
		}
	}
	_mapsHolder->addToContainter(_map);
	//mapsHolder->showMaps();
}


void MapLoader::parseMapLine(std::string line)
{

	std::vector<char> mapLine;

	for (int i = 0, len = line.length(); i < len; i++){
		mapLine.push_back(line[i]);
	}
	_map.push_back(mapLine);
}

void MapLoader::prepareMapVector()
{
	_map.clear();
}