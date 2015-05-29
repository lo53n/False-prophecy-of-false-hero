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

	void clearMap();

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


	//and now to building texture tile by tile//
	void drawMap(sf::RenderTexture& mapRenderTexture);
	void drawWall(sf::RenderTexture& mapRenderTexture, int y, int x);
	void drawFloor(sf::RenderTexture& mapRenderTexture, int y, int x);
	void drawEntry(sf::RenderTexture& mapRenderTexture, int y, int x);

	void drawEmpty(sf::RenderTexture& mapRenderTexture, int y, int x);

	void setMapLayer(sf::RenderTexture& mapRenderTexture);

	//////////////////
	//Map traversing//
	//////////////////

	void findAllExitPoints();

	//Set for destination map
	void pairMapAndExitPoint(std::shared_ptr<Map> previousMap); 
	//Set for actual map
	void pairMapAndExitPoint(std::shared_ptr<Map> destinationMap, sf::Vector2i exitPoint);


	std::shared_ptr<Map> moveToMap(unsigned int previousMapID);


	//Debug?//
	void printConsoleMap();




private:
	std::vector<std::vector<char>> _mapTemplate; //Representation of 2D map, it ended with _mapTemplate[y_dimension][x_dimension]

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