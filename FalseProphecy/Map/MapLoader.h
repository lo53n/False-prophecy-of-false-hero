#ifndef MAP_MAPLOADER
#define MAP_MAPLOADER

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>



class MapLoader{

public:
	MapLoader();
	~MapLoader();
	void loadFromFile();

	std::vector<std::vector<std::vector<char>>> loadSpecialMaps();

	std::vector<std::vector<std::vector<char>>>& getMapsData();

private:
	std::vector<std::vector<char>> _map;

	std::vector<std::vector<std::vector<char>>> _mapsData;


private:
	void parseMapLine(std::string line);
	void prepareMapVector();

};


#endif //!MAP_MAPLOADER