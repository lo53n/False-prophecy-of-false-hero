#ifndef GAME_GAME
#define GAME_GAME

#include <SFML/Graphics.hpp>


#include "../ResourceManagment/ResourcesLoader.h"


//#include "../Enemy/EnemiesLoader.h"
//#include "../Items/ItemsLoader.h"
//#include "../Map/MapLoader.h"

#include "../Map/Map.h"

#include "../Player/Player.h"

#include "../Items/Weapons/Weapon.h"
#include "../Items/Armours/Armour.h"

#include "../Interface/GameWindowInterface.h"
#include "../Interface/InventoryWindow.h"
#include "../Interface/StatusWindow.h"

#include "../DevMode/DevMode.h"


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
	sf::View _interfaceView;

	/////////////////////////////
	//Some bool to check events//
	/////////////////////////////
	bool _isPlaying = true;
	bool _isStatusWindowOpen = false;
	bool _isInventoryWindowOpen = false;
	bool _isDevModeActive = false;

	bool _isErrorMessageActive = false;


	//////////////////
	//Error Handling//
	//////////////////
	std::shared_ptr<ErrorHandler> _errorHandler;



	///////////////////////
	//Interfaces and menu//
	///////////////////////

	std::shared_ptr<GameWindowInterface> _gameWindowInterface;
	InventoryWindow _inventoryWindow;
	StatusWindow _statusWindow;
	DevMode _devMode;

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

	std::shared_ptr<Map> _newMap;
	std::shared_ptr<Map> _currentMap;


	int _currentMapNumber;

	/////////////////////////
	//Stuff holders/loaders//
	/////////////////////////

	ResourcesHolder *_resHolder = &ResourcesHolder::getResourcesHolder();

	/*MapsHolder *_mapsHolder = &MapsHolder::getMapsHolder();
	ItemsHolder *_itemsHolder = &ItemsHolder::getItemsHolder();
	EnemiesHolder *_enemiesHolder = &EnemiesHolder::getEnemiesHolder();*/



	////////////////////////
	//Player related stuff//
	////////////////////////
	std::shared_ptr<Player> _player;

	int _turns_taken = 0;

	///////////////
	//Some cheats//
	///////////////
	bool noClip = false;


	/////////////////
	//Magic numbers//
	/////////////////
	const float __CAMERA_MOVE_LENGTH__ = 32.0f;

	int __TURNS_TO_INCREMENT_MAP_RESPAWN_TIMER__ = 50;

	//Change those also in Map.h//
	char __ENEMY_ON_MAP__ = '8';
	char __ENEMY_CORPSE_ON_MAP__ = '#';


	//If changed, change in Player.h//
	const int __BACKPACK_CAPACITY__ = 50;

private:
	//////////////////
	//Game main loop//
	//////////////////
	void processEvents();
	void update();
	void draw();


	///////////////////////
	//Handle player input//
	///////////////////////
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);



	//check, if player can move into specific place
	bool checkMovement(int direction);


	/////////////
	//Map stuff//
	/////////////
	//Shared pointers stuff, it's really hard to think of something better...//

	//In reality creates new map object and shared pointer to it.//
	std::shared_ptr<Map> createMapSharedPointer(unsigned int mapID); 


	void generateNewMap();
	void generateNewMap(sf::Vector2i currentPos);

	void checkForExistingFreeExits(std::shared_ptr<Map> mapToCheck);

	void increaseMapsRespawnCounter(bool isOnMap);

	//////////////////
	//Map traversing//
	//////////////////

	bool handleMapTraverse();
	void moveToMap(int mapNumber, bool needPair);


	///////////////
	//Enemy stuff//
	///////////////



	////////////////
	//Player stuff//
	////////////////

	void takeTurn();

	//////////////////////////
	//Player and Enemy stuff//
	//////////////////////////

	void heroAttacksEnemy(sf::Vector2i position);
	void heroDropsItem();

	///////////////////////
	//Item and drop stuff//
	///////////////////////

	void generateDrop(sf::Vector2i position);
	void checkForObjectsAtPlayerPosition();

};


#endif //!GAME_GAME