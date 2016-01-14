#ifndef GAME_GAME
#define GAME_GAME

#include <SFML/Graphics.hpp>


#include "../ResourceManagment/ResourcesLoader.h"


#include "../Map/Map.h"

#include "../Player/Player.h"

#include "../Items/Weapons/Weapon.h"
#include "../Items/Armours/Armour.h"
#include "../Items/Consumables/Consumable.h"

#include "../Interface/GameWindowInterface.h"
#include "../Interface/InventoryWindow.h"
#include "../Interface/StatusWindow.h"
#include "../Interface/HelpWindow.h"
#include "../Menu/Menu.h"
#include "../Events/EventsHandler.h"


#include "../Save/SaveState.h"


class Game {
public:
	Game();
	void run();



	///////////////////
	//Events Handling//
	///////////////////
	std::shared_ptr<EventsHandler> _eventsHandler;


	//fix it later
	ResourcesHolder *_resHolder = &ResourcesHolder::getResourcesHolder();
	std::shared_ptr<Player> _player;

	int _currentMapNumber = 0;
	std::shared_ptr<Map> _currentMap;
	std::vector<std::shared_ptr<Map>> _maps;


private:

	std::default_random_engine _generator;


	///////////////
	//Game Window//
	///////////////
	sf::RenderWindow _window;
	sf::View _gameView;
	sf::View _interfaceView;

	/////////////////////////////
	//Some bool to check events//
	/////////////////////////////
	bool _isPlaying = false;
	bool _isHeroDead = false;
	bool _isMenu = true;
	bool _isHelp = false;
	bool _isStatusWindowOpen = false;
	bool _isInventoryWindowOpen = false;
	bool _isDevModeActive = false;
	bool _isEnemyTurn = false;
	bool _isItemsManipulated = false;

	bool _isTimeToAnimate = false;

	bool _isErrorMessageActive = false;


	//////////////////
	//Error Handling//
	//////////////////
	std::shared_ptr<ErrorHandler> _errorHandler;


	/////////////////
	//Save and load//
	/////////////////
	std::shared_ptr<SaveState> _saveState;



	///////////////////////
	//Interfaces and menu//
	///////////////////////

	std::shared_ptr<GameWindowInterface> _gameWindowInterface;
	InventoryWindow _inventoryWindow;
	StatusWindow _statusWindow;
	Menu _menu;
	HelpWindow _help;

	///////////////////////
	//Items related stuff//
	///////////////////////

	std::vector<std::shared_ptr<Item>> _itemList;

	//////////////////////
	//Maps related stuff//
	//////////////////////
	//std::vector<std::shared_ptr<Map>> _maps;
	std::vector<std::shared_ptr<Map>> _mapsWithAvaiableExits;
	
	sf::RenderTexture _mapTexture;
	sf::RenderTexture _mapTextureDisplayed;

	std::shared_ptr<Map> _newMap;
	//std::shared_ptr<Map> _currentMap;
	int _currentMapTemplate;


	/////////////////////////
	//Stuff holders/loaders//
	/////////////////////////

	//ResourcesHolder *_resHolder = &ResourcesHolder::getResourcesHolder();

	/*MapsHolder *_mapsHolder = &MapsHolder::getMapsHolder();
	ItemsHolder *_itemsHolder = &ItemsHolder::getItemsHolder();
	EnemiesHolder *_enemiesHolder = &EnemiesHolder::getEnemiesHolder();*/



	////////////////////////
	//Player related stuff//
	////////////////////////
//	std::shared_ptr<Player> _player;


	int _ticks = 0;
	int _turns_taken = 0;

	///////////////
	//Some cheats//
	///////////////
	bool noClip = false;


	/////////////////
	//Magic numbers//
	/////////////////
	const float __CAMERA_MOVE_LENGTH__ = 32.0f;

	int __TICKS_PER_TURN__ = 100;
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


	void animateStuff();

	///////////////////////
	//Handle player input//
	///////////////////////
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);



	//check, if player can move into specific place
	bool checkMovement(int direction);


	////////////////
	//Events stuff//
	////////////////
	void updateEvents();


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
	void enemyTurn();
	void moveEnemy();

	int checkEnemyMovement(sf::Vector2i enemy_pos, std::shared_ptr<Enemy> &enemy, std::vector<std::vector<char>> &mapTemplate);

	bool isPlayerNearby(sf::Vector2i position);


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

	void generateDrop(sf::Vector2i position, std::shared_ptr<Enemy> enemy);
	void checkForObjectsAtPlayerPosition();


	///////////////////
	//Save management//
	///////////////////
	void newGame();
	void restoreData();
};


#endif //!GAME_GAME