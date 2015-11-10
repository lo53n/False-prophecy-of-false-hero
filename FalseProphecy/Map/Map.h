#ifndef MAP_MAP
#define MAP_MAP

#include <iostream>
#include <cstdlib>
#include <memory>
#include <unordered_map>

#include <SFML\Graphics.hpp>

#include "MapsHolder.h"
#include "../Enemy/Enemy.h"
#include "../Items/Item.h"

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

class Enemy;

class Map : public sf::Drawable{

public:

	sf::RenderTexture* _renderTexture;

	Map();
	Map(std::vector<std::vector<char>> mapTemplate, unsigned int mapID, sf::RenderTexture& renderTexture);
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
	
	//Get exit points vector
	//@return std::vector<sf::Vector2i>& _mapExitPoints
	std::vector<sf::Vector2i> getExitPoints();

	//Get map of exit points
	//@return std::unordered_map<sf::Vector2i, std::shared_ptr<Map>>& _mapExits
	std::unordered_map<sf::Vector2i, std::shared_ptr<Map>>& getMapExitPoints();

	//Get exit point, at which you appear after moving to next map
	//@return sf::Vector2i newPosition
	sf::Vector2i getNewPosition(unsigned int previousMapID);

	//Get number of free exits.
	//@return: unsigned int
	unsigned int getNumberOfFreeExits();


	///////////
	//Setters//
	///////////

	//Set map template
	void setMap(std::vector<std::vector<char>> mapTemplate);


	/////////////////////
	//Map drawing stuff//
	/////////////////////


	//and now to building texture tile by tile//
	void drawMap();
	void drawWall(sf::RenderTexture& mapRenderTexture, int y, int x);
	void drawFloor(sf::RenderTexture& mapRenderTexture, int y, int x);
	void drawEntry(sf::RenderTexture& mapRenderTexture, int y, int x);

	void drawEmpty(sf::RenderTexture& mapRenderTexture, int y, int x);

	void setMapLayer(sf::RenderTexture& mapRenderTexture);

	void updateMap();

	//////////////////
	//Map traversing//
	//////////////////

	void findAllExitPoints();

	//Set for destination map
	void pairMapAndExitPoint(std::shared_ptr<Map> previousMap); 
	//Set for actual map
	void pairMapAndExitPoint(std::shared_ptr<Map> destinationMap, sf::Vector2i exitPoint);


	std::shared_ptr<Map> moveToMap(unsigned int previousMapID);



	///////////////
	//Map enemies//
	///////////////

	std::vector<std::shared_ptr<Enemy>>& getEnemies();

	void increaseRespawnCounter();
	void resurrectAndReinforceEnemies();

	std::shared_ptr<Enemy> getEnemyAtPosition(int posx, int posy);

	void killOffEnemy(int enemy_id);

	//////////////////////////
	//Moving around entities//
	//////////////////////////

	void changeMapTile(char newTile, int x, int y);




	///////////////////////////////
	//Setting enemies on load map//
	///////////////////////////////

	void putEnemiesOnMap();
	void takeEnemiesFromMap();



	//////////////////
	//Items and drop//
	//////////////////

	void pushItemToMapStorage(sf::Vector2i position, std::shared_ptr<Item> item);
	bool checkForItemsAtTile(sf::Vector2i position);

	std::shared_ptr<Item> returnItemAtTile(sf::Vector2i position);



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


	///////////////
	//Map enemies//
	///////////////
	std::vector<std::shared_ptr<Enemy>> _enemies;
	std::vector<std::shared_ptr<Enemy>> _deadenemies;

	int _respawn_counter = 0;

	//////////////////
	//Items and drop//
	//////////////////

	std::unordered_multimap<sf::Vector2i, std::shared_ptr<Item>> _itemsOnMap;


	/////////////////
	//Magic Numbers//
	/////////////////
	const float __TILE_SIZE_X__ = 32.0f; //Height of tile
	const float __TILE_SIZE_Y__ = 32.0f; //Width of tile

	int __MAPS_TILL_RESPAWN__ = 30;

	//Change those also in Game.h//
	char __ENEMY_ON_MAP__ = '8';
	char __ENEMY_CORPSE_ON_MAP__ = '#';


private:
	void checkMaxSizes();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};



#endif //!MAP_MAP