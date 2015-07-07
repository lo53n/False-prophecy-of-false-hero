#ifndef GAME_GAME
#define GAME_GAME

#include <SFML/Graphics.hpp>

#include <cstdlib>

#include "../Map/MapLoader.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Items/ItemsLoader.h"
#include "../Items/Weapons/Weapon.h"

class Game {
public:
	Game();
	void run();


private:
	///////////////
	//Game Window//
	///////////////
	sf::RenderWindow _window;
	sf::View _gameView;


	///////////////////////
	//Items related stuff//
	///////////////////////

	std::vector<std::shared_ptr<Item>> _itemList;

	//////////////////////
	//Maps related stuff//
	//////////////////////
	std::vector<std::shared_ptr<Map>> _maps;
	std::vector<std::shared_ptr<Map>> _mapsWithAvaiableExits;
	
	sf::RenderTexture _mapTexture;

	/////////////////////////
	//Stuff holders/loaders//
	/////////////////////////
	MapsHolder *_mapsHolder = &MapsHolder::getMapsHolder();
	ItemsHolder *_itemsHolder = &ItemsHolder::getItemsHolder();

	std::shared_ptr<Map> _newMap;
	std::shared_ptr<Map> _currentMap;


	int _currentMapNumber;

	void generateNewMap();
	void generateNewMap(sf::Vector2i currentPos);

	void checkForExistingFreeExits(std::shared_ptr<Map> mapToCheck);

	//////////////////
	//Map traversing//
	//////////////////

	bool handleMapTraverse();
	void moveToMap(int mapNumber, bool needPair);


	////////////////////////
	//Player related stuff//
	////////////////////////
	Player _player;

	///////////////
	//Some cheats//
	///////////////
	bool noClip = false;


	/////////////////
	//Magic numbers//
	/////////////////
	const float __CAMERA_MOVE_LENGTH__ = 32.0f;

private:
	void processEvents();
	void update();
	void draw();


	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


	//check, if player can move into specific place
	bool checkMovement(int direction);


	/////////////
	//Map stuff//
	/////////////
	//Shared pointers stuff, it's really hard to think of something better...//

	//In reality creates new map object and shared pointer to it.//
	std::shared_ptr<Map> createMapSharedPointer(unsigned int mapID); 




};


#endif //!GAME_GAME