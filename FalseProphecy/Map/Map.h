#ifndef MAP_MAP
#define MAP_MAP

#include <iostream>
#include <cstdlib>

#include <SFML\Graphics.hpp>

#include "MapsHolder.h"

class Map : public sf::Drawable{

public:
	Map();
	Map(std::vector<std::vector<char>> mapTemplate);
	~Map();

	void setMap(std::vector<std::vector<char>> mapTemplate);
	void setMapLayer();

	std::vector<std::vector<char>>& getMap();

	void drawMap();
	void drawWall(int y, int x);
	void drawFloor(int y, int x);
	void drawEntry(int y, int x);

	void drawEmpty(int y, int x);


	//Debug?//
	void printConsoleMap();



private:
	std::vector<std::vector<char>> _mapTemplate; //Representation of 2D map, it ended with _mapTemplate[y_dimension][x_dimension]

	sf::RenderTexture _mapTexture;
	sf::Sprite _mapSprite;

	//////////////////
	//Map Dimensions//
	//////////////////
	int _maxDimensionX;
	int _maxDimensionY;


	/////////////////
	//Magic Numbers//
	/////////////////
	const float __TILE_SIZE_X__ = 32.0f; //Height of tile
	const float __TILE_SIZE_Y__ = 32.0f; //Width of tile

private:
	void checkMaxSizes();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif //!MAP_MAP