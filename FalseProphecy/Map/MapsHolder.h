#ifndef MAP_MAPSHOLDER
#define MAP_MAPSHOLDER

#include <vector>
#include <iostream>


class MapsHolder{


private:
	static MapsHolder *_mapsHolder;
	std::vector<std::vector<std::vector<char>>> _maps;


private:
	MapsHolder();
	MapsHolder(MapsHolder const&);
	void operator=(MapsHolder const&);



public:
	static MapsHolder& getMapsHolder();
	void addToContainter(std::vector<std::vector<char>> map);
	void showMaps();
	std::vector<std::vector<char>> getMapFromHolder(int mapIndex);

	///////////
	//Getters//
	///////////
	int getMapCount();
	std::vector<std::vector<std::vector<char>>> getAllMaps();


};
#endif //!MAP_MAPSHOLDER