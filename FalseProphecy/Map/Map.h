#ifndef MAP_MAP
#define MAP_MAP

#include <iostream>
#include <cstdlib>
#include <memory>
#include <unordered_map>

#include <SFML\Graphics.hpp>

#include "MapsHolder.h"

namespace std
{
	template <class T>
	struct hash<sf::Vector2<T>>
	{
		std::size_t operator()(const sf::Vector2<T>& v) const
		{
			using std::hash;

			// Compute individual hash values for first
			// and second. Combine them using the Boost-func

			std::size_t tmp0 = hash<T>()(v.x);
			std::size_t tmp1 = hash<T>()(v.y);

			tmp0 ^= tmp1 + 0x9e3779b9 + (tmp0 << 6) + (tmp0 >> 2);
			return tmp0;
		}
	};
}

class Map : public sf::Drawable{

public:
	Map();
	Map(std::vector<std::vector<char>> mapTemplate, unsigned int mapID);
	~Map();



	///////////
	//Getters//
	///////////

	//Get map ID
	//@return unsigned it _mapID
	unsigned int getMapId();

	//Get map vectors as map[y_dimension][x_dimenstion]
	//@return std::vector<std::vector<char>>& map
	std::vector<std::vector<char>>& getMap();

	//Get map exit points vector
	//@return std::vector<sf::Vector2i>& _mapExitPoints
	std::unordered_map<sf::Vector2i, std::shared_ptr<Map>>& getMapExitPoints();

	//Get exit point, at which you appear after moving to next map
	//@return sf::Vector2i newPosition
	sf::Vector2i getNewPosition(unsigned int previousMapID);

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

	void findAllExitPoints();

	//Set for destination map
	void pairMapAndExitPoint(std::shared_ptr<Map> previousMap); 
	//Set for actual map
	void pairMapAndExitPoint(std::shared_ptr<Map> destinationMap, sf::Vector2i exitPoint);

	void setMapExitPoint(int exitDirection, std::shared_ptr<Map> previousMap);
	//std::shared_ptr<Map> moveToMap(int exitTile);
	std::shared_ptr<Map> moveToMap(unsigned int previousMapID);

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


	///////////////////
	//Map exit points//
	///////////////////

	std::vector<sf::Vector2i> _exitPoints; //all existing exit points
	std::vector<sf::Vector2i> _notPairedExitPoints; //not paired exit points, will be checked for making new pairs with pointers
	std::unordered_map<sf::Vector2i, std::shared_ptr<Map>> _mapExits;



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