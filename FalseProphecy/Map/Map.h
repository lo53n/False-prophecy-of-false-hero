#ifndef MAP_MAP
#define MAP_MAP

#include <iostream>
#include <cstdlib>
#include <memory>

#include <SFML\Graphics.hpp>

#include "MapsHolder.h"

class Map : public sf::Drawable{

public:
	Map();
	Map(std::vector<std::vector<char>> mapTemplate, unsigned int mapID);
	~Map();



	///////////
	//Getters//
	///////////

	unsigned int getMapId();
	std::vector<std::vector<char>>& getMap();

	///////////
	//Setters//
	///////////

	void setMap(std::vector<std::vector<char>> mapTemplate);


	/////////////////////
	//Map drawing stuff//
	/////////////////////

	//clear whole map to release a lot of memory//
	void clearMap();

	//and now to building texture tile by tile//
	void drawMap();
	void drawWall(int y, int x);
	void drawFloor(int y, int x);
	void drawEntry(int y, int x);

	void drawEmpty(int y, int x);

	void setMapLayer();

	//////////////////
	//Map traversing//
	//////////////////
	//clock-wise, where NORHT is 0//
	enum MAPEXIT{ NORTH, EAST, SOUTH, WEST };

	void setMapExitPoint(int exitDirection, std::shared_ptr<Map> previousMap);
	std::shared_ptr<Map> moveToMap(int exitTile);

	//true means there is no pairing//
	bool checkMapExitPoint(int exit);

	//Debug?//
	void printConsoleMap();




private:
	std::vector<std::vector<char>> _mapTemplate; //Representation of 2D map, it ended with _mapTemplate[y_dimension][x_dimension]

	sf::RenderTexture _mapTexture;
	sf::Sprite _mapSprite;

	unsigned int _mapIdentifier; //Map identifying number

	//////////////////
	//Map Dimensions//
	//////////////////
	int _maxDimensionX;
	int _maxDimensionY;

	//////////////////
	//Map traversing//
	//////////////////
	//clock-wise//
	std::shared_ptr<Map> _northExit;
	std::shared_ptr<Map> _eastExit;
	std::shared_ptr<Map> _southExit;
	std::shared_ptr<Map> _westExit;


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