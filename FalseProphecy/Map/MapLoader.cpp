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
	xxxExxxxxxx
	x.x.x..xx.x
	xx.xx.x...x
	x...x..x..x
	xx....x.x.x
	 xx.......x
	  xExxxxxxx
	*/
	stringline = "xxxExxxxxxx";
	parseMapLine(stringline);
	stringline = "x.x.x..xx.x";
	parseMapLine(stringline);
	stringline = "xx.xx.x...x";
	parseMapLine(stringline);
	stringline = "x...x..x..x";
	parseMapLine(stringline);
	stringline = "xx....x.x.x";
	parseMapLine(stringline);
	stringline = " xx.......x";
	parseMapLine(stringline);
	stringline = "  xExxxxxxx";
	parseMapLine(stringline);

	special_maps.push_back(_map);

	prepareMapVector();
	/*
	xxxxx
	E...xx
	xxx..xxx
	  xx...xx
	   xx...x
	    xxxEx
	*/
	stringline = "xxxxx";
	parseMapLine(stringline);
	stringline = "E...xx";
	parseMapLine(stringline);
	stringline = "xxx..xx";
	parseMapLine(stringline);
	stringline = "  xx..xxx";
	parseMapLine(stringline);
	stringline = "   xx...x";
	parseMapLine(stringline);
	stringline = "    xxxEx";
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

	prepareMapVector();
	/*
	xxxExxx
	x.....x
	x.....x
	x.....x
	xxxxxxx
	*/
	stringline = "xxxExxx";
	parseMapLine(stringline);
	stringline = "x.....x";
	parseMapLine(stringline);
	stringline = "x.....x";
	parseMapLine(stringline);
	stringline = "x.....x";
	parseMapLine(stringline);
	stringline = "xxxxxxx";
	parseMapLine(stringline);

	special_maps.push_back(_map);
	return special_maps;
}