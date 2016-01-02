#include "MapLoader.h"


MapLoader::MapLoader()
{

}

MapLoader::~MapLoader()
{

}

std::vector<std::vector<std::vector<char>>>& MapLoader::getMapsData()
{
	return _mapsData;
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
			_mapsData.push_back(_map);
			prepareMapVector();
		}
	}
	_mapsData.push_back(_map);
	
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


std::vector<std::vector<std::vector<char>>> MapLoader::loadSpecialMaps()
{
	std::vector<std::vector<std::vector<char>>> special_maps;
	std::string stringline;

	prepareMapVector();
	/*
	xxxxxxxxxxx
	x...x..xx.x
	xx..x.x...x
	x...x..x..x
	xx....x.x.x
	xxx.......x
	xxxExxxxxxx
	*/
	stringline = "xxxxxxxxxxx";
	parseMapLine(stringline);
	stringline = "x...x..xx.x";
	parseMapLine(stringline);
	stringline = "xx..x.x...x";
	parseMapLine(stringline);
	stringline = "x...x..x..x";
	parseMapLine(stringline);
	stringline = "xx....x.x.x";
	parseMapLine(stringline);
	stringline = "xxx.......x";
	parseMapLine(stringline);
	stringline = "xxxExxxxxxx";
	parseMapLine(stringline);

	special_maps.push_back(_map);

	prepareMapVector();
	/*
	xxxxxxxxxxx
	E...xxxxxxx
	xxx..xxxxxx
	xxxx...xxxx
	xxxxxx...xx
	xxxxxxxxExx
	*/
	stringline = "xxxxxxxxxxx";
	parseMapLine(stringline);
	stringline = "E...xxxxxxx";
	parseMapLine(stringline);
	stringline = "xxx..xxxxxx";
	parseMapLine(stringline);
	stringline = "xxxx...xxxx";
	parseMapLine(stringline);
	stringline = "xxxxxx...xx";
	parseMapLine(stringline);
	stringline = "xxxxxxxxExx";
	parseMapLine(stringline);

	special_maps.push_back(_map);

	prepareMapVector();
	/*
	xxxExxx
	x.....x
	x.....x
	x.....x
	xxxExxx
	*/
	stringline = "xxxExxx";
	parseMapLine(stringline);
	stringline = "x.....x";
	parseMapLine(stringline);
	stringline = "x.....x";
	parseMapLine(stringline);
	stringline = "x.....x";
	parseMapLine(stringline);
	stringline = "xxxExxx";
	parseMapLine(stringline);

	special_maps.push_back(_map);

	return special_maps;
}