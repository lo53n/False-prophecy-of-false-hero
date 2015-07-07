#include "Game.h"

Game::Game()
	: _window(sf::VideoMode(800, 640), "SFML Application")
	, _gameView(sf::FloatRect(0.0f, 0.0f, 800.0f, 640.0f))
{

	///////////////////////
	//Load game resources//
	///////////////////////
	MapLoader mapLoader;
	mapLoader.loadFromFile(); //Load maps from file

	ItemsLoader itemsloader;
	itemsloader.loadResources(); //Load items from file

//	_itemsHolder->loadResources();

	//_player.setPlayerPositionOnGrid(sf::Vector2i(5, 5));

	_gameView.setCenter(_player.getPlayerPositionOnMap());

	_window.setView(_gameView);
}

/////////////
//Main Loop//
/////////////

void Game::run(){
	
	_currentMapNumber = 0;
	
	std::shared_ptr<Item> asd(std::make_shared<Weapon>(_itemsHolder->_weaponsData[0]));
	_itemList.push_back(asd);


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

	/////////////
	//draw game//
	/////////////

	_window.setView(_gameView);
	//for (int i = 0, len = _maps.size(); i < len; i++) _window.draw(*_maps[i]);
	_window.draw(*_currentMap);
	_window.draw(_player);
	for (auto item : _itemList)
		_window.draw(*item);

	//////////////////
	//draw interface//
	//////////////////
	_window.setView(_window.getDefaultView());
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
	if (key == sf::Keyboard::Numpad0 && isPressed){
		if (noClip) noClip = false;
		else noClip = true;
	}

	////////////////////
	//Some fast debugs//
	////////////////////
	if (key == sf::Keyboard::Period && isPressed) _itemList[0]->setImagesPosition(sf::Vector2f(32.f, 32.f));


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
		switch (currentTile){
		case 'E': return handleMapTraverse();

		default: return false;
		}
	}
	//We check now tiles
	if (_currentMap->getMap()[checkForPosition.y][checkForPosition.x] != 'x')
		return true;

	//if we get here, that mean there was any obstacle
	return false;
}


//////////////////
//Map traversing//
//////////////////

bool Game::handleMapTraverse()
{

	//This one is for map traversing//
	sf::Vector2i currentPosition((int)_player.getPlayerPositionOnGrid().y, (int)_player.getPlayerPositionOnGrid().x);
	unsigned int previousMap = _currentMap->getMapId();

	//Check for existing maps. If not, create new or pair with new.
	if (_currentMap->getMapExitPoints()[currentPosition] == NULL){
		if (_mapsWithAvaiableExits.size() < 15 || rand() % 100 > 50)
			generateNewMap(currentPosition);
		else{
			int randomMap = rand() % _mapsWithAvaiableExits.size();

			_newMap = _mapsWithAvaiableExits[randomMap];

			std::shared_ptr<Map> transferCurrentMap = _currentMap;
			std::shared_ptr<Map> transferNextMap = _newMap;

			_currentMap->pairMapAndExitPoint(transferNextMap, currentPosition);
			transferNextMap->pairMapAndExitPoint(transferCurrentMap);

			/*if (_currentMap->getNumberOfFreeExits() == 0){
				int mapID = _currentMap->getMapId();
				for (int i = 0, len = _mapsWithAvaiableExits.size(); i < len; i++)
					if (_mapsWithAvaiableExits[i]->getMapId() == mapID){
						_mapsWithAvaiableExits.erase(_mapsWithAvaiableExits.begin() + i);
						std::cout << "Erased." << std::endl;
					}
			}

			if (_newMap->getNumberOfFreeExits() == 0){
				int newMapID = _newMap->getMapId();
				for (int i = 0, len = _mapsWithAvaiableExits.size(); i < len; i++)
					if (_mapsWithAvaiableExits[i]->getMapId() == newMapID){
						_mapsWithAvaiableExits.erase(_mapsWithAvaiableExits.begin() + i);
						std::cout << "Erased." << std::endl;
					}
			}*/
			checkForExistingFreeExits(_currentMap);
			checkForExistingFreeExits(_newMap);

			//std::cout << "BOOM! TIED WITH OTHER MAP WITH ID's: old " << _currentMap->getMapId() << ", new " << _newMap->getMapId() << std::endl;
			_currentMap = _newMap;
			_currentMap->drawMap(_mapTexture);
		}
	}
	else{
		unsigned int targetMap;
		for (auto keyValue : _currentMap->getMapExitPoints())
		{
			if (keyValue.first == currentPosition){
				targetMap = keyValue.second->getMapId();
				break;
			}
		}
		_currentMap = _currentMap->moveToMap(targetMap);
		_currentMap->drawMap(_mapTexture);
	}


	_player.setPlayerPositionOnGrid(sf::Vector2i(_currentMap->getNewPosition(previousMap).y, _currentMap->getNewPosition(previousMap).x));
	return false;
}

void Game::moveToMap(int mapNumber, bool needPair)
{
	if (!needPair){
		std::shared_ptr<Map> ptr(_currentMap->moveToMap(mapNumber));
		_currentMap = ptr;
		_currentMap->drawMap(_mapTexture);
	}
	else{

	}
}


/////////////
//Map Stuff//
/////////////

//Generate next map//
//TODO:
//could use some checking if map exist when coming back. Also, some optimalization?//

//Debugging/testing map generator. Enter to generate new.
void Game::generateNewMap()
{
	unsigned int mapID = _maps.size();
	_currentMapNumber = rand() % _mapsHolder->getMapCount();

	if (_maps.size() > 0) _currentMap->clearMap();
	//if (_currentMapNumber >= _mapsHolder->getMapCount()) _currentMapNumber = 0;
	//_newMap = new Map(_mapsHolder->getMapFromHolder(_currentMapNumber));

	_newMap = createMapSharedPointer(mapID);
	_newMap->drawMap(_mapTexture);

	_maps.push_back(_newMap);
	_mapsWithAvaiableExits.push_back(_newMap);

	_currentMap = _maps[_maps.size() - 1];

	sf::Vector2i position = _currentMap->getExitPoints()[rand() % _currentMap->getExitPoints().size()];
	_player.setPlayerPositionOnGrid(sf::Vector2i(position.y, position.x));

	_gameView.setCenter(_player.getPlayerPositionOnMap()); //center view on player
	_window.setView(_gameView); //refresh the view

	//std::cout << _currentMapNumber << " Another! " << _maps.size() << " Map No_" << _currentMap->getMapId() << std::endl;
}

void Game::generateNewMap(sf::Vector2i currentPos)
{

	unsigned int mapID = _maps.size();
	_currentMapNumber = rand() % _mapsHolder->getMapCount();

	//_currentMapNumber = 0;
	if (_currentMapNumber >= _mapsHolder->getMapCount()) _currentMapNumber = 0;

	if (_maps.size() > 0) _currentMap->clearMap();

	_newMap = createMapSharedPointer(mapID);
	_newMap->drawMap(_mapTexture);

	_maps.push_back(_newMap);
	_mapsWithAvaiableExits.push_back(_newMap);

	std::shared_ptr<Map> transferCurrentMap = _currentMap;
	std::shared_ptr<Map> transferNextMap = _newMap;

	_currentMap->pairMapAndExitPoint(transferNextMap, currentPos);
	transferNextMap->pairMapAndExitPoint(transferCurrentMap);

	checkForExistingFreeExits(_currentMap);
	checkForExistingFreeExits(_newMap);

	//std::cout << "Old map exits left: " << _currentMap->getNumberOfFreeExits();
	_currentMap = _maps[_maps.size() - 1];
	//std::cout << " New map exits left: " << _currentMap->getNumberOfFreeExits() << std::endl;

	//std::cout << _currentMapNumber << " Another! " << _maps.size() << " >> Map No_" << _currentMap->getMapId() << " <<" << std::endl;

}


void Game::checkForExistingFreeExits(std::shared_ptr<Map> mapToCheck)
{
	if (mapToCheck->getNumberOfFreeExits() == 0){
		int mapID = _currentMap->getMapId();
		for (int i = 0, len = _mapsWithAvaiableExits.size(); i < len; i++)
			if (_mapsWithAvaiableExits[i]->getMapId() == mapID){
				_mapsWithAvaiableExits.erase(_mapsWithAvaiableExits.begin() + i);
				len = _mapsWithAvaiableExits.size();
				std::cout << "Erased." << std::endl;
			}
	}
}

std::shared_ptr<Map> Game::createMapSharedPointer(unsigned int mapID)
{
	std::shared_ptr<Map> ptr(std::make_shared<Map>(_mapsHolder->getMapFromHolder(_currentMapNumber), mapID));
	return ptr;
}