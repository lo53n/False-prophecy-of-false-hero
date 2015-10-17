#include "Game.h"

Game::Game()
	: _window(sf::VideoMode(800, 640), "SFML Application")
	, _gameView(sf::FloatRect(0.0f, 0.0f, 800.0f, 640.0f))
	, _interfaceView(sf::FloatRect(0.f, 0.f, 800.f, 640.f))
	, _player(std::make_shared<Player>())
{
		
	///////////////////////
	//Load game resources//
	///////////////////////
	MapLoader mapLoader;
	mapLoader.loadFromFile(); //Load maps from file

	ItemsLoader itemsloader;
	itemsloader.loadResources(); //Load items from file

	EnemiesLoader enemiesLoader;
	enemiesLoader.loadFromFile(); //Load enemies from file

//	_itemsHolder->loadResources();

	//_player->setPlayerPositionOnGrid(sf::Vector2i(5, 5));


	//////////////////////////////////////////////
	//Set player on inventory window and DevMode//
	//////////////////////////////////////////////

	_inventoryWindow.setPlayer(_player);
	_statusWindow.setPlayer(_player);
	_devMode.setPlayer(_player);

	////////////////////////
	//Set size of dev menu//
	////////////////////////

	sf::Vector2f size = (sf::Vector2f) _window.getSize();
	sf::Vector2f position = sf::Vector2f(0, _gameWindowInterface.getInterfaceHeight());

	size = sf::Vector2f(size.x, size.y - _gameWindowInterface.getInterfaceHeight());

	_devMode.setPositionAndSize(position, size);

	/////////////
	//Set views//
	/////////////
	_gameView.setCenter(_player->getPlayerPositionOnMap());

	_window.setView(_gameView);

	_gameWindowInterface.setGameWindowInterfaceSizeByResize(sf::Vector2f((float)_window.getSize().x, (float)_window.getSize().y));

	_inventoryWindow.resizeByGameWindow(sf::Vector2f((float)_window.getSize().x / 2, (float)_window.getSize().y / 2));
	_statusWindow.resizeByGameWindow(sf::Vector2f((float)_window.getSize().x / 2, (float)_window.getSize().y / 2));

}

/////////////
//Main Loop//
/////////////

void Game::run(){
	
	_currentMapNumber = 0;
	
	for (int i = 0; i < 29; i++){
		std::shared_ptr<Item> asd(std::make_shared<Weapon>(_itemsHolder->_weaponsData[0]));
		_player->putItemInBackpack(asd);
	}
/*	for (int i = 0; i < 19; i++){
		std::shared_ptr<Item> asd(std::make_shared<Armour>(_itemsHolder->_armoursData[0]));
		_player->putItemInBackpack(asd);
	}*/

	std::shared_ptr<Armour> asd(std::make_shared<Armour>(_itemsHolder->_armoursData[0]));
	_player->putItemInBackpack(asd);
	std::shared_ptr<Armour> asd1(std::make_shared<Armour>(_itemsHolder->_armoursData[1]));
	_player->putItemInBackpack(asd1);


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
	sf::Vector2i coords;
	sf::Vector2f visible;
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

		//RESIZE//
		case sf::Event::Resized:
			visible = sf::Vector2f((int)event.size.width, (int)event.size.height);
			if (visible.x < 640.f && visible.y < 480){
				visible = sf::Vector2f(640, 480);
				_window.setSize((sf::Vector2u)visible);
			}
			_gameView.setSize(visible);
			_interfaceView.setSize(visible);
			_interfaceView.setCenter(visible.x/2, visible.y/2);
			_gameWindowInterface.setGameWindowInterfaceSizeByResize(visible);
			_inventoryWindow.resizeByGameWindow(sf::Vector2f(visible.x / 2, visible.y / 2));
			_statusWindow.resizeByGameWindow(sf::Vector2f(visible.x / 2, visible.y / 2));
			_window.setView(_gameView);

			_devMode.resizeMenu(sf::Vector2f(visible.x, visible.y - _gameWindowInterface.getInterfaceHeight()));
			break;
		/*case::sf::Event::MouseButtonPressed:
			coords = sf::Mouse::getPosition(_window);
			std::cout << coords.x << " " << coords.y << std::endl;
			break;*/
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
	_window.draw(*_player);
	for (auto item : _itemList)
		_window.draw(*item);

	//////////////////
	//draw interface//
	//////////////////
	_window.setView(_interfaceView);
	_window.draw(_gameWindowInterface);
	if (_isInventoryWindowOpen) _window.draw(_inventoryWindow);
	if (_isStatusWindowOpen) _window.draw(_statusWindow);
	if (_isDevModeActive) _window.draw(_devMode);
	_window.display();
}

////////////////////
//Processing stuff//
////////////////////

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
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

	/////////////////////////////////
	//Switch interfaces and windows//
	/////////////////////////////////
	//INVENTORY WINDOW//
	if (key == sf::Keyboard::I && isPressed) {
		if (_isInventoryWindowOpen) _isInventoryWindowOpen = false;
		else {
			_isInventoryWindowOpen = true;
			_inventoryWindow.putItemsOnTiles();
		}

		_isStatusWindowOpen = false; 
		_isDevModeActive = false;
	}
	//STATUS WINDOW//
	if (key == sf::Keyboard::C && isPressed) {
		if (_isStatusWindowOpen) _isStatusWindowOpen = false;
		else{
			_isStatusWindowOpen = true;
			_statusWindow.refreshStatus();
		}

		_isInventoryWindowOpen = false; 
		_isDevModeActive = false;
	}
	//DEVMODE//
	if (key == sf::Keyboard::F1 && isPressed){
		if (_isDevModeActive) _isDevModeActive = false;
		else _isDevModeActive = true;

		_isInventoryWindowOpen = false;
		_isStatusWindowOpen = false;
	}

	////////////////////////
	//DevMode manipulation//
	////////////////////////
	
	if (_isDevModeActive){
		DevMode::Result result = _devMode.handlePlayerInput(key, isPressed);

		return;
	}
	
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
			_gameView.setCenter(_player->getPlayerPositionOnMap()); //center

		_window.setView(_gameView); //refresh view
	}
	//////////////////
	//Player & Menus//
	//////////////////
	if (!_isInventoryWindowOpen && !_isStatusWindowOpen){
		///////////////////
		//Player Movement//
		///////////////////
		if (key >= sf::Keyboard::Left && key <= sf::Keyboard::Down && isPressed){
			takeTurn();
			bool canMove = false; //for collision
			sf::Vector2i checkForPosition;
			if (!noClip) //No Clip cheat off!//
				switch (key){
				//Move one step up//
				case sf::Keyboard::Up:
					if (checkMovement(Player::UP))
						_player->movePlayer(Player::UP);
					break;

					//Move one step right//
				case sf::Keyboard::Right:
					if (checkMovement(Player::RIGHT))
						_player->movePlayer(Player::RIGHT);
					break;

					//Move one step down//
				case sf::Keyboard::Down:
					if (checkMovement(Player::DOWN))
						_player->movePlayer(Player::DOWN);
					break;

					//Move one step left//
				case sf::Keyboard::Left:
					if (checkMovement(Player::LEFT))
						_player->movePlayer(Player::LEFT);
			}

			if (noClip)//No Clip cheat on!//
				if (key == sf::Keyboard::Up)
					_player->movePlayer(Player::UP);
				else if (key == sf::Keyboard::Right)
					_player->movePlayer(Player::RIGHT);
				else if (key == sf::Keyboard::Down)
					_player->movePlayer(Player::DOWN);
				else if (key == sf::Keyboard::Left)
					_player->movePlayer(Player::LEFT);

				_gameView.setCenter(_player->getPlayerPositionOnMap()); //center view on player
				_window.setView(_gameView); //refresh the view

		}
		//Show next map//
		if (key == sf::Keyboard::Return && isPressed){
			generateNewMap();
		}
		if (key == sf::Keyboard::D && isPressed && (_player->getPlayerBackpack().size() < __BACKPACK_CAPACITY__)){
			checkForObjectsAtPlayerPosition();
		}
	}
	else{
		//////////////////////////
		//Interface manipulation//
		//////////////////////////
		if (_isInventoryWindowOpen && !_isStatusWindowOpen && isPressed){
			if (key == sf::Keyboard::D && isPressed){
					heroDropsItem();
			}
			_inventoryWindow.handleInput(key, isPressed);
			
		}
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
			checkForPosition = _player->getPlayerPositionOnGrid() - sf::Vector2i(0, 1);
			break;
		case 1: //RIGHT
			checkForPosition = _player->getPlayerPositionOnGrid() - sf::Vector2i(-1, 0);
			break;
		case 2: //DOWN
			checkForPosition = _player->getPlayerPositionOnGrid() - sf::Vector2i(0, -1);
			break;
		case 3: //LEFT
			checkForPosition = _player->getPlayerPositionOnGrid() - sf::Vector2i(1, 0);
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

			throw _currentMap->getMap()[_player->getPlayerPositionOnGrid().y][_player->getPlayerPositionOnGrid().x];
	}
	catch(char currentTile){
		switch (currentTile){
		case 'E': return handleMapTraverse();
		default: return false;
		}
	}
	//We check now tiles
	//Is it enemy?
	if (_currentMap->getMap()[checkForPosition.y][checkForPosition.x] == __ENEMY_ON_MAP__){
		for (auto enemy : _currentMap->_enemies){
			if (enemy->getEnemyPositionOnGrid() == checkForPosition){
				//std::cout << "boom, enemy!" << std::endl;
				//_currentMap->changeMapTile(__ENEMY_CORPSE_ON_MAP__, checkForPosition.x, checkForPosition.y);
				heroAttacksEnemy(checkForPosition);
				//_currentMap->printConsoleMap();

				//if dead, then calculate loot
				if (!enemy->checkIfAlive()){
					generateDrop(checkForPosition);
					std::cout << "ded" << std::endl;
				}
			}
		}
		return false;
	}


	//Is it wall?
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

	//First, increace maps respawn counter
	increaseMapsRespawnCounter(false);

	//This one is for map traversing//
	sf::Vector2i currentPosition((int)_player->getPlayerPositionOnGrid().y, (int)_player->getPlayerPositionOnGrid().x);
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


	_player->setPlayerPositionOnGrid(sf::Vector2i(_currentMap->getNewPosition(previousMap).y, _currentMap->getNewPosition(previousMap).x));
	return false;
}

///OBSOLETE!?
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
	_player->setPlayerPositionOnGrid(sf::Vector2i(position.y, position.x));

	_gameView.setCenter(_player->getPlayerPositionOnMap()); //center view on player
	_window.setView(_gameView); //refresh the view

	//std::cout << _currentMapNumber << " Another! " << _maps.size() << " Map No_" << _currentMap->getMapId() << std::endl;
}

void Game::generateNewMap(sf::Vector2i currentPos)
{

	//Get new map identifier based on total maps generated
	unsigned int mapID = _maps.size();
	_currentMapNumber = rand() % _mapsHolder->getMapCount();


	//_currentMapNumber = 0;
	if (_currentMapNumber >= _mapsHolder->getMapCount()) _currentMapNumber = 0;

	if (_maps.size() > 0) _currentMap->clearMap();


	//Create new map and then draw it
	_newMap = createMapSharedPointer(mapID);
	_newMap->drawMap(_mapTexture);

	//Save map
	_maps.push_back(_newMap);
	_mapsWithAvaiableExits.push_back(_newMap);

	//Now, time pair exits
	std::shared_ptr<Map> transferCurrentMap = _currentMap;
	std::shared_ptr<Map> transferNextMap = _newMap;

	_currentMap->pairMapAndExitPoint(transferNextMap, currentPos);
	transferNextMap->pairMapAndExitPoint(transferCurrentMap);

	//Recount exits which wasn't paired yet
	checkForExistingFreeExits(_currentMap);
	checkForExistingFreeExits(_newMap);

	//Set latest map as current
	//std::cout << "Old map exits left: " << _currentMap->getNumberOfFreeExits();
	_currentMap = _maps[_maps.size() - 1];
	//std::cout << " New map exits left: " << _currentMap->getNumberOfFreeExits() << std::endl;

	//std::cout << _currentMapNumber << " Another! " << _maps.size() << " >> Map No_" << _currentMap->getMapId() << " <<" << std::endl;

	//Generate enemies!
	int tiley = 0;
	int enemy_id = 0;
	for (auto row : _currentMap->getMap()){
		int tilex = 0;
		for (auto tile : row){
			if (tile == '.'){
				int chance = rand() % 100;
				if (chance > 90){
					Enemy_Stats enemy_template = _enemiesHolder->_enemiesData[rand()%_enemiesHolder->_enemiesData.size()];
					std::shared_ptr<Enemy> enemy(std::make_shared<Enemy>(enemy_id, enemy_template, sf::Vector2i(tilex, tiley), tile));
					_currentMap->_enemies.push_back(enemy);
					_currentMap->changeMapTile(__ENEMY_ON_MAP__, tilex, tiley);
					enemy_id++;
				}
			}
			tilex++;
		}
		tiley++;
	}
	//_currentMap->printConsoleMap();

}


void Game::checkForExistingFreeExits(std::shared_ptr<Map> mapToCheck)
{
	if (mapToCheck->getNumberOfFreeExits() == 0){
		int mapID = _currentMap->getMapId();
		for (int i = 0, len = _mapsWithAvaiableExits.size(); i < len; i++)
			if (_mapsWithAvaiableExits[i]->getMapId() == mapID){
				_mapsWithAvaiableExits.erase(_mapsWithAvaiableExits.begin() + i);
				len = _mapsWithAvaiableExits.size();
			}
	}
}

std::shared_ptr<Map> Game::createMapSharedPointer(unsigned int mapID)
{
	std::shared_ptr<Map> ptr(std::make_shared<Map>(_mapsHolder->getMapFromHolder(_currentMapNumber), mapID));
	return ptr;
}

void Game::increaseMapsRespawnCounter(bool isInMap)
{
	if (isInMap){
		for (auto map : _maps){
			if (map == _currentMap) continue;
			map->increaseRespawnCounter();
		}
	}
	else{
		for (auto map : _maps){
			map->increaseRespawnCounter();
		}

	}
}

/////////////////////
//Player only stuff//
/////////////////////

void Game::takeTurn()
{
	_turns_taken++;
	if (_turns_taken == __TURNS_TO_INCREMENT_MAP_RESPAWN_TIMER__){
		increaseMapsRespawnCounter(true);
		_turns_taken = 0;
	}
}

void Game::heroDropsItem()
{
		std::shared_ptr<Item> item = _player->dropSelectedItem(_inventoryWindow.getHighlitItem(), _inventoryWindow.isHighlitInBag());
		if (item == nullptr) return;
		_currentMap->pushItemToMapStorage(_player->getPlayerPositionOnGrid(), item);
		_inventoryWindow.putItemsOnTiles();
}

//////////////////////////
//Player and Enemy stuff//
//////////////////////////

void Game::heroAttacksEnemy(sf::Vector2i position)
{
	std::shared_ptr<Enemy> enemy = _currentMap->getEnemyAtPosition(position.x, position.y);
	int dmg = _player->calculateDamage();
	enemy->takeHit(dmg);
	if (!enemy->checkIfAlive()){
		_currentMap->killOffEnemy(enemy->getEnemyId());
	}
}

///////////////////////
//Item and drop stuff//
///////////////////////

//Need better drop generator here.
void Game::generateDrop(sf::Vector2i position)
{
	std::shared_ptr<Item> item(std::make_shared<Weapon>(_itemsHolder->_weaponsData[0]));
	_currentMap->pushItemToMapStorage(position, item);
	std::shared_ptr<Item> item1(std::make_shared<Weapon>(_itemsHolder->_weaponsData[0]));
	_currentMap->pushItemToMapStorage(position, item1);
	std::cout << "generated" << std::endl;
}

void Game::checkForObjectsAtPlayerPosition()
{
	if (_currentMap->checkForItemsAtTile(_player->getPlayerPositionOnGrid())){
		_player->getPlayerBackpack().push_back(_currentMap->returnItemAtTile(_player->getPlayerPositionOnGrid()));
	}
}
