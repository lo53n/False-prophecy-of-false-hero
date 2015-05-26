#include "Game.h"

Game::Game()
	: _window(sf::VideoMode(800, 640), "SFML Application")
	, _gameView(sf::FloatRect(0.0f, 0.0f, 800.0f, 640.0f))
{
	_player.setPlayerPositionOnGrid(sf::Vector2i(5, 5));

	_gameView.setCenter(_player.getPlayerPositionOnMap());
	_window.setView(_gameView);
}

/////////////
//Main Loop//
/////////////

void Game::run(){

	MapLoader mapLoader;
	mapLoader.loadFromFile(); //Load maps from file


	_currentMapNumber = 0;
	

	//_newMap = new Map(_mapsHolder->getMapFromHolder(_currentMapNumber));

	//_newMap->drawMap();
	//_maps.push_back(_newMap);
	//_currentMap = _maps[0];

	generateNewMap();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.0f/60.0f); //set to 60fps

	while (_window.isOpen()){
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame){
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update();
		}
		draw();
	}

}

//////////////////////
//MainLoop functions//
//////////////////////

void Game::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		switch (event.type){

		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			_window.close();
			break;
		case sf::Event::Resized:
			sf::Vector2f visible((float)event.size.width, (float)event.size.height);
			_gameView.setSize(visible);
			_window.setView(_gameView);
			break;
		}
	}
}

void Game::update()
{

}

void Game::draw()
{
	_window.clear();
	//for (int i = 0, len = _maps.size(); i < len; i++) _window.draw(*_maps[i]);
	_window.draw(*_currentMap);
	_window.draw(_player);
	_window.display();
}

////////////////////
//Processing stuff//
////////////////////

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	//Show next map//
	if (key == sf::Keyboard::Return && isPressed){
		generateNewMap();
	}
	///////////////////////////////
	//Process normal player input//
	///////////////////////////////
	//
	//TODO: move those cheats into some kind of debug mode maybe?
	//
	////////////////
	//Some cheats!//
	////////////////
	//No clip - if true, collisions does not apply//
	if (key == sf::Keyboard::Numpad0 && isPressed)
		if (noClip) noClip = false;
		else noClip = true;

	////////////////
	//Map Movement//
	////////////////
	if (key >= sf::Keyboard::Numpad1 && key <= sf::Keyboard::Numpad9 && isPressed){
		if (key == sf::Keyboard::Numpad1)
			_gameView.move(-__CAMERA_MOVE_LENGTH__, __CAMERA_MOVE_LENGTH__); //left-down
		else if (key == sf::Keyboard::Numpad2)
			_gameView.move(0, __CAMERA_MOVE_LENGTH__);  //down
		else if (key == sf::Keyboard::Numpad3)
			_gameView.move(__CAMERA_MOVE_LENGTH__, __CAMERA_MOVE_LENGTH__); //right-down
		else if (key == sf::Keyboard::Numpad4)
			_gameView.move(-__CAMERA_MOVE_LENGTH__, 0); //left
		else if (key == sf::Keyboard::Numpad6)
			_gameView.move(__CAMERA_MOVE_LENGTH__, 0);  //right
		else if (key == sf::Keyboard::Numpad7)
			_gameView.move(-__CAMERA_MOVE_LENGTH__, -__CAMERA_MOVE_LENGTH__); //left-up
		else if (key == sf::Keyboard::Numpad8)
			_gameView.move(0, -__CAMERA_MOVE_LENGTH__); //up
		else if (key == sf::Keyboard::Numpad9)
			_gameView.move(__CAMERA_MOVE_LENGTH__, -__CAMERA_MOVE_LENGTH__); //right-up
		else if (key == sf::Keyboard::Numpad5)
			_gameView.setCenter(_player.getPlayerPositionOnMap()); //center

		_window.setView(_gameView); //refresh view
	}
	///////////////////
	//Player Movement//
	///////////////////
	if (key >= sf::Keyboard::Left && key <= sf::Keyboard::Down && isPressed){
		bool canMove = false; //for collision
		sf::Vector2i checkForPosition;
		if (!noClip) //No Clip cheat!//
		switch (key){
			//Move one step up//
		case sf::Keyboard::Up:
			if (checkMovement(Player::UP))
				_player.movePlayer(Player::UP);
			break;

			//Move one step right//
		case sf::Keyboard::Right:
			if (checkMovement(Player::RIGHT))
				_player.movePlayer(Player::RIGHT);
			break;

			//Move one step down//
		case sf::Keyboard::Down:
			if (checkMovement(Player::DOWN))
				_player.movePlayer(Player::DOWN);
			break;

			//Move one step left//
		case sf::Keyboard::Left:
			if (checkMovement(Player::LEFT))
				_player.movePlayer(Player::LEFT);
		}

		if (noClip)//No Clip cheat!//
			if (key == sf::Keyboard::Up)
				_player.movePlayer(Player::UP);
			else if (key == sf::Keyboard::Right)
				_player.movePlayer(Player::RIGHT);
			else if (key == sf::Keyboard::Down)
				_player.movePlayer(Player::DOWN);
			else if (key == sf::Keyboard::Left)
				_player.movePlayer(Player::LEFT);

		_gameView.setCenter(_player.getPlayerPositionOnMap()); //center view on player
		_window.setView(_gameView); //refresh the view
	}


	//TODO: Debug Menu
}



bool Game::checkMovement(int direction)
{
	bool canMove = false;
	sf::Vector2i checkForPosition;
	try{
		switch (direction){
			//We must give opposite vectors to achieve our goal of checking desired tile
		case 0: //UP
			checkForPosition = _player.getPlayerPositionOnGrid() - sf::Vector2i(0, 1);
			break;
		case 1: //RIGHT
			checkForPosition = _player.getPlayerPositionOnGrid() - sf::Vector2i(-1, 0);
			break;
		case 2: //DOWN
			checkForPosition = _player.getPlayerPositionOnGrid() - sf::Vector2i(0, -1);
			break;
		case 3: //LEFT
			checkForPosition = _player.getPlayerPositionOnGrid() - sf::Vector2i(1, 0);
			break;
		}
		//Check if you don't go out-of-bound. If this is the case, it can be the exit
		if (
			checkForPosition.x < 0 
			|| checkForPosition.y < 0
			|| (unsigned)(checkForPosition.y) >= _currentMap->getMap().size()
			|| (unsigned)(checkForPosition.x) >= _currentMap->getMap()[checkForPosition.y].size()
			|| _currentMap->getMap()[checkForPosition.y][checkForPosition.x] == ' '
			)

			throw _currentMap->getMap()[_player.getPlayerPositionOnGrid().y][_player.getPlayerPositionOnGrid().x];
	}
	catch(char currentTile){
		if (currentTile == 'E'){
			//std::cout << "Wyjœcie" << std::endl;
			generateNewMap();
			_player.setPlayerPositionOnGrid(sf::Vector2i(3, 2));
		}
		return false;
	}
	//We check now tiles
	if (_currentMap->getMap()[checkForPosition.y][checkForPosition.x] != 'x')
		return true;

	//if we get here, that mean there was any obstacle
	return false;
}


/////////////
//Map Stuff//
/////////////

//Generate next map//
//TODO:
//could use some checking if map exist when coming back. Also, some optimalization?//
void Game::generateNewMap()
{
	unsigned int mapID = _maps.size();
	if(_maps.size() > 0) _currentMap->clearMap();
	_currentMapNumber = rand()%_mapsHolder->getMapCount();
	//if (_currentMapNumber >= _mapsHolder->getMapCount()) _currentMapNumber = 0;
	//_newMap = new Map(_mapsHolder->getMapFromHolder(_currentMapNumber));
	_newMap = createMapSharedPointer(mapID);
	_newMap->drawMap();
	_maps.push_back(_newMap);
	_currentMap = _maps[_maps.size() - 1];
	std::cout << _currentMapNumber << " Another! " << _maps.size() << " Map No_" << _currentMap->getMapId() << std::endl;
}

std::shared_ptr<Map> Game::createMapSharedPointer(unsigned int mapID)
{
	std::shared_ptr<Map> ptr(std::make_shared<Map>(_mapsHolder->getMapFromHolder(_currentMapNumber), mapID));
	return ptr;
}