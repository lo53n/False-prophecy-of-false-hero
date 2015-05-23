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
	sf::CircleShape _shape;
	sf::View _gameView;


	//////////////////////
	//Maps related stuff//
	//////////////////////
	std::vector<Map*> _maps;

	MapsHolder *_mapsHolder = &MapsHolder::getMapsHolder();
	Map *_newMap;
	Map *_currentMap;

	int _currentMapNumber;

	////////////////////////
	//Player related stuff//
	////////////////////////
	Player _player;


	/////////////////
	//Magic numbers//
	/////////////////
	const float __CAMERA_MOVE_LENGTH__ = 32.f;

private:
	void processEvents();
	void update();
	void draw();

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


};




#endif //!GAME_GAME