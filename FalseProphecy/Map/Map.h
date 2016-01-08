#ifndef MAP_MAP
#define MAP_MAP

#include <iostream>
#include <cstdlib>
#include <memory>
#include <unordered_map>
#include <random>
#include <queue>

#include <SFML\Graphics.hpp>

#include "../Enemy/Enemy.h"
#include "../Items/Item.h"
#include "../Items/Weapons/Weapon.h"
#include "../Items/Armours/Armour.h"
#include "../Items/Consumables/Consumable.h"

#include "../ResourceManagment/ResourcesHolder.h"

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


	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{


		ar  & _mapIdentifier;
		ar  & _respawn_counter;
		takeEnemiesFromMap();
		ar  & _mapTemplate;
		putEnemiesOnMap();
		ar  & _maxDimensionX;
		ar  & _maxDimensionY; /*
		ar  & _enemies;
		ar  & _deadenemies;
		ar  & _exitPoints;
		ar  & _notPairedExitPoints;
		ar  & _mapExits;
		ar  & _itemsOnMap;*/
		
	}

public:


	Map();

	Map(int id, int resCount, std::vector<std::vector<char>>& mapTemplate, int maxX, int maxY/*,
		std::vector<std::shared_ptr<Enemy>> &enemies, std::vector<std::shared_ptr<Enemy>> &deadenemies,
		std::vector<sf::Vector2i> &exitPoints, std::vector<sf::Vector2i> &notPairedExits,
		std::unordered_map<sf::Vector2i, std::shared_ptr<Map>> &mapExits,
		std::unordered_multimap<sf::Vector2i, std::shared_ptr<Item>> &itemsOnMap*/);

	Map(std::vector<std::vector<char>> mapTemplate, unsigned int mapID, sf::RenderTexture& renderTexture, sf::RenderTexture& renderTextureDisplayed, Hero_Ratings ratings);
	~Map();


	void restoreMap(sf::RenderTexture& renderTexture, sf::RenderTexture& renderTextureDisplayed);


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

	//as the name suggests
	void drawWall(sf::RenderTexture& mapRenderTexture, int y, int x);
	void drawFloor(sf::RenderTexture& mapRenderTexture, int y, int x);
	void drawEntry(sf::RenderTexture& mapRenderTexture, int y, int x);
	void drawEmpty(sf::RenderTexture& mapRenderTexture, int y, int x);

	void drawDecoration(int number, int type);

	//set map texture
	void setMapLayer(sf::RenderTexture& mapRenderTexture);

	//redraw everything
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

	void increaseEnemyTicks(int &amount);
	void moveEnemy(std::shared_ptr<Enemy> &enemy, sf::Vector2i newPos);

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

	void generateItemAtPosition(sf::Vector2i position, int enemyRating);
	void pushItemToMapStorage(sf::Vector2i position, std::shared_ptr<Item> item);
	bool checkForItemsAtTile(sf::Vector2i position);

	std::shared_ptr<Item> returnItemAtTile(sf::Vector2i position);



	//Debug?//
	void printConsoleMap();




private:
	////////////////////////
	//Generating and stuff//
	////////////////////////
	ResourcesHolder *_resHolder = &ResourcesHolder::getResourcesHolder();
	Hero_Ratings _ratings;

	std::default_random_engine _generator;

	///////////////
	//Map overlay//
	///////////////
	std::vector<std::vector<char>> _mapTemplate; //Representation of 2D map, it ended with _mapTemplate[y_dimension][x_dimension]

	sf::RenderTexture* _renderTexture;
	sf::RenderTexture* _renderTextureDisplayed;
	sf::Sprite _mapSprite;
	sf::Sprite _mapSpriteToDisplay;

	sf::Sprite _wallTile;
	sf::Texture _wallTexture;

	sf::Sprite _floorTile;
	sf::Texture _floorTexture;

	sf::Sprite _doorTile;
	sf::Texture _doorTexture;

	unsigned int _mapIdentifier; //Map identifying number

	std::vector<sf::Vector2f> _wallDecorationSmall;
	std::vector<sf::Vector2f> _wallDecorationLarge;

	std::vector<sf::Vector2f> _floorDecorationSmall;
	std::vector<sf::Vector2f> _floorDecorationMedium;
	std::vector<sf::Vector2f> _floorDecorationLarge;

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

	////////
	//ENUM//
	////////

	enum MAP_DECORATIONS{
		SMALL_WALL,
		LARGE_WALL,
		SMALL_FLOOR,
		MEDIUM_FLOOR,
		LARGE_FLOOR
	};


private:
	void checkMaxSizes();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


#endif //!MAP_MAP