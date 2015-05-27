#ifndef GAME_GAME
#define GAME_GAME

#include <SFML/Graphics.hpp>

#include <cstdlib>

#include "../Map/MapLoader.h"
#include "../Map/Map.h"
#include "../Player/Player.h"


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


	//////////////////////
	//Maps related stuff//
	//////////////////////
	//std::vector<Map*> _maps;
	std::vector<std::shared_ptr<Map>> _maps;

	MapsHolder *_mapsHolder = &MapsHolder::getMapsHolder();
	//Map *_newMap;
	//Map *_currentMap;

	std::shared_ptr<Map> _newMap;
	std::shared_ptr<Map> _currentMap;


	int _currentMapNumber;

	void generateNewMap();
	void generateNewMap(int exitTile);

	//////////////////
	//Map traversing//
	//////////////////

	void moveToMap(int exitTile);


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
	std::shared_ptr<Map> createMapSharedPointer(unsigned int mapID); //In reality creates new map object and shared pointer to it.//
};




#endif //!GAME_GAME