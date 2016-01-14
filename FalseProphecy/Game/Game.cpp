#include "Game.h"

Game::Game()
	: _window(sf::VideoMode(800, 640), "Prophecy")
	, _gameView(sf::FloatRect(0.0f, 0.0f, 800.0f, 640.0f))
	, _interfaceView(sf::FloatRect(0.f, 0.f, 800.f, 640.f))
	, _player(std::make_shared<Player>())
{

	//////////////////
	//Create objects//
	//////////////////
	_gameWindowInterface = std::make_shared<GameWindowInterface>();


	/////////////////////
	//Set error handler//
	/////////////////////
	_errorHandler = std::make_shared<ErrorHandler>();
	

	//////////////////////
	//Set events handler//
	//////////////////////
	_eventsHandler = std::make_shared<EventsHandler>();

	//////////////////
	//Set save state//
	//////////////////
	_saveState = std::make_shared<SaveState>(*this);
	//std::cout << this << std::endl;

	///////////////////////
	//Load game resources//
	///////////////////////

	ResourcesLoader resload(_errorHandler);
	resload.loadGameData();

	_resHolder->loadData();


	//////////////////////////////////////////////
	//Set player on inventory window and DevMode//
	//////////////////////////////////////////////

	_inventoryWindow.setPlayer(_player);
	_statusWindow.setPlayer(_player);
	_generator.seed(time(0));


	_player->setGameWindowInterface(_gameWindowInterface);

	/////////////
	//Set views//
	/////////////
	_gameView.setCenter(_player->getPlayerPositionOnMap());

	_window.setView(_gameView);

	_gameWindowInterface->setGameWindowInterfaceSizeByResize(sf::Vector2f((float)_window.getSize().x, (float)_window.getSize().y));

	_inventoryWindow.resizeByGameWindow(sf::Vector2f((float)_window.getSize().x / 2, (float)_window.getSize().y / 2));
	_statusWindow.resizeByGameWindow(sf::Vector2f((float)_window.getSize().x / 2, (float)_window.getSize().y / 2));
	_menu.resizeByGameWindow(sf::Vector2f((float)_window.getSize().x / 2, (float)_window.getSize().y / 2));
	_help.resizeByGameWindow(sf::Vector2f((float)_window.getSize().x / 2, (float)_window.getSize().y / 2));

	_errorHandler->resizeByGameWindow(sf::Vector2f((float)_window.getSize().x / 2, (float)_window.getSize().y / 2));
	_eventsHandler->resizeByGameWindow(sf::Vector2f((float)_window.getSize().x / 2, (float)_window.getSize().y / 2));




	//////////////
	//Test stuff//
	//////////////


}

/////////////
//Main Loop//
/////////////

void Game::run(){

	_currentMapNumber = 0;
	generateNewMap();


	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.0f/60.0f); //set to 60fps

	while (_window.isOpen()){

		_isErrorMessageActive = _errorHandler->getErrorStatus();

		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame){
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			if (_isPlaying){
				update();
			}
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
	sf::Vector2f visible, currSize;
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
			visible = sf::Vector2f((float)event.size.width, (float)event.size.height);
			if (visible.x < 640.f){
				visible = sf::Vector2f(640, visible.y);
				_window.setSize((sf::Vector2u)visible);
			}
			if (visible.y < 480.f){
				visible = sf::Vector2f(visible.x, 480);
				_window.setSize((sf::Vector2u)visible);
			}


			_gameView.setSize(visible);
			_interfaceView.setSize(visible);
			_interfaceView.setCenter(visible.x/2, visible.y/2);
			_gameWindowInterface->setGameWindowInterfaceSizeByResize(visible);
			_inventoryWindow.resizeByGameWindow(sf::Vector2f(visible.x / 2, visible.y / 2));
			_statusWindow.resizeByGameWindow(sf::Vector2f(visible.x / 2, visible.y / 2));
			_menu.resizeByGameWindow(sf::Vector2f(visible.x / 2, visible.y / 2));
			_help.resizeByGameWindow(sf::Vector2f(visible.x / 2, visible.y / 2));

			_errorHandler->resizeByGameWindow(sf::Vector2f(visible.x / 2, visible.y / 2));
			_eventsHandler->resizeByGameWindow(sf::Vector2f(visible.x / 2, visible.y / 2));

			_window.setView(_gameView);
			break;

		}
	}
}

void Game::update()
{
	enemyTurn();



	animateStuff();
}

void Game::draw()
{
	_window.clear();


	/////////////
	//draw game//
	/////////////
	_window.setView(_gameView);
	
	if (!_isMenu){
		_window.draw(*_currentMap);
		for (auto item : _itemList)
			_window.draw(*item);

		_window.draw(*_player);
	}
	//////////////////
	//draw interface//
	//////////////////
	_window.setView(_interfaceView);
	if (_isMenu){
		_window.draw(_menu);
		if (_errorHandler->getErrorStatus()) _window.draw(*_errorHandler);
	}
	else{
		_window.draw(*_gameWindowInterface);
		if (_isInventoryWindowOpen) _window.draw(_inventoryWindow);
		if (_isStatusWindowOpen) _window.draw(_statusWindow);
		if (_errorHandler->getErrorStatus()) _window.draw(*_errorHandler);
		if (_eventsHandler->getEventStatus()) _window.draw(*_eventsHandler); 
		if (_isHelp) _window.draw(_help);
	}
	_window.display();
}


void Game::animateStuff()
{
	int  frames = 8;
	float change = 32 / frames;

	if (_player->checkIfThereIsNeedToAnimate()){
		_player->moveSprite(change);

		_gameView.setCenter(_player->getPlayerSpritePosition()); //center view on player
		_window.setView(_gameView); //refresh the view
	}

	for (auto enemy : _currentMap->getEnemies()){
		if (enemy->checkIfThereIsNeedToAnimate()){
			enemy->moveSprite(change);
		}
	}
	_currentMap->updateMap();
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

	//////////////////////
	//Toggle help window//
	//////////////////////
	if (key == sf::Keyboard::F1 && isPressed){
		if (!_isHelp) _isHelp = true;
		else _isHelp = false;
	}

	//////////////////
	//Error handling//
	//////////////////
	if (_isErrorMessageActive){
		_errorHandler->handleInput(key, isPressed);
		return;
	}


	//////////////////
	//Events handler//
	//////////////////
	if (_eventsHandler->getEventStatus()){
		_eventsHandler->handleInput(key, isPressed);
		return;
	}

	/////////////////////
	//Player  is  dead///
	//Back to menu ASAP//
	/////////////////////
	if (_isHeroDead && isPressed){
		_isHeroDead = false;
		_isPlaying = false;
		_isMenu = true;
		return;
	}

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

	//Exit all menus or enter game menu.//
	if (key == sf::Keyboard::Escape && isPressed){
		if (!_isInventoryWindowOpen && !_isStatusWindowOpen && !_isDevModeActive ){
			if (!_isMenu)	{
				_isMenu = true;
			}
			else if(!_isPlaying) _window.close();
		}
		else if (_isInventoryWindowOpen || _isStatusWindowOpen || _isDevModeActive || _isMenu){
			_isInventoryWindowOpen = false;
			_isStatusWindowOpen = false;
			_isDevModeActive = false;
			_isMenu = false;
		}
		
	}

	/////////////////
	//Menu handling//
	/////////////////
	if (_isMenu){
		if (key == sf::Keyboard::Return && isPressed){
			int selection = _menu.getHighlit();
			switch (selection){
			case 0:
				if (!_isPlaying){
					try{
						restoreData();
					}
					catch (boost::archive::archive_exception &e){
						newGame();
					}
				}
				_isMenu = false;
				_isPlaying = true;
				return;
				break;

			case 1: newGame();
				_isMenu = false;
				_isPlaying = true;
				return;
				break;

			case 2:
				_player->setCurrentMap(_currentMap->getMapId());
				_saveState->saveGame();
				_window.close();
				return;
				break;
			}
		}
		else{
			_menu.handleInput(key, isPressed);
			return;
		}
	}

	////////////////////////
	//DevMode manipulation//
	////////////////////////
	

	
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
			bool canMove = false; //for collision
			sf::Vector2i checkForPosition;
			if (!noClip) //No Clip cheat off!//
				switch (key){
				//Move one step up//
				case sf::Keyboard::Up:
					if (checkMovement(Player::UP)){
						_player->movePlayer(Player::UP);
						takeTurn();
					}
					break;

					//Move one step right//
				case sf::Keyboard::Right:
					if (checkMovement(Player::RIGHT)){
						_player->movePlayer(Player::RIGHT);
						takeTurn();
					}
					break;

					//Move one step down//
				case sf::Keyboard::Down:
					if (checkMovement(Player::DOWN)){
						_player->movePlayer(Player::DOWN);
						takeTurn();
					}
					break;

					//Move one step left//
				case sf::Keyboard::Left:
					if (checkMovement(Player::LEFT)){
						_player->movePlayer(Player::LEFT);
						takeTurn();
					}
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

				//centering view in animating

		}
		//pick up items
		if (key == sf::Keyboard::D && isPressed && (_player->getPlayerBackpack().size() < (unsigned)__BACKPACK_CAPACITY__)){
			checkForObjectsAtPlayerPosition();
		}

		//rest
		if (key == sf::Keyboard::R && isPressed){
			if (rand() % 100 > 50) _player->regenHealth(true);
			_player->regenStamina(true);
			takeTurn();
		}
	}
	else{
		//////////////////////////
		//Interface manipulation//
		//////////////////////////
		if (_isInventoryWindowOpen && !_isStatusWindowOpen && isPressed){
			if (key == sf::Keyboard::D && isPressed){
				takeTurn();
				heroDropsItem();
				_currentMap->updateMap();
			}
			_inventoryWindow.handleInput(key, isPressed, _isItemsManipulated);
			if (_isItemsManipulated){
				takeTurn();
				_isItemsManipulated = false;
			}
		}
	}
	//TODO: Debug Menu
}


////////////////
//Events stuff//
////////////////
void Game::updateEvents()
{
	_eventsHandler->updateEventTracker(_player->getPlayerStats(), _player->getPlayerPositionOnGrid());
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
		for (auto enemy : _currentMap->getEnemies()){
			if (enemy->getEnemyPositionOnGrid() == checkForPosition){
				if (!enemy->checkIfAlive()){
					continue;
				}
				heroAttacksEnemy(checkForPosition);
				takeTurn();
				//set as aggroed
				enemy->setAlarmStatus(true);

				//if dead, then calculate outcome
				if (!enemy->checkIfAlive()){
					generateDrop(checkForPosition, enemy);

					_player->increaseExperience(enemy->getEnemyStats().experience);

					if (_currentMap->getMapId() == 1){
						_eventsHandler->triggerEvent(EVENT_TYPE::FIRST_ENEMY_KILLED);
					}
					if (_currentMap->getMapId() == 40){
						_eventsHandler->triggerEvent(EVENT_TYPE::FIRST_BOSS_KILLED);
					}
					if (_currentMap->getMapId() == 100){
						_eventsHandler->triggerEvent(EVENT_TYPE::PRIESTESS_KILLED);
					}
				}
				_gameWindowInterface->refreshBars(_player->getPlayerStats());
			}
		}
		return false;
	}
	//events
	if (_currentMap->getMap()[checkForPosition.y][checkForPosition.x] == 'E'){
		if (_currentMap->getMapId() == 40 && !(_eventsHandler->getEventsStructure().first_boss_killed))	return false;
		if (_currentMap->getMapId() == 100 && !(_eventsHandler->getEventsStructure().priestess_killed))	return false;

	}
		
	//Is it wall?
	if (_currentMap->getMap()[checkForPosition.y][checkForPosition.x] != 'x')
		return true;

	if (_currentMap->getMap()[checkForPosition.y][checkForPosition.x] == 'x' &&
		_currentMap->getMap()[_player->getPlayerPositionOnGrid().y][_player->getPlayerPositionOnGrid().x] == 'E'){
		return handleMapTraverse();
	}


	//if we get here, that mean there was any obstacle
	return false;
}


//////////////////
//Map traversing//
//////////////////

bool Game::handleMapTraverse()
{
	//Let's save the game.
	_player->setCurrentMap(_currentMap->getMapId());
	_saveState->saveGame();
	//First, increace maps respawn counter
	increaseMapsRespawnCounter(false);

	//This one is for map traversing//
	unsigned int previousMap = _currentMap->getMapId();

	//then, events

	if (_currentMapNumber == 1){
		_eventsHandler->triggerEvent(EVENT_TYPE::FIRST_ENEMY_MEET);
	}
	else if (_currentMapNumber == 20){
		_eventsHandler->triggerEvent(EVENT_TYPE::HALFWAY_TO_BOSS);
	}
	else if (_currentMapNumber == 40){
		_eventsHandler->triggerEvent(EVENT_TYPE::FIRST_BOSS);
	}
	else if (_currentMapNumber == 100){
		if (_player->getPlayerStats().willpower < 100 && _player->getPlayerStats().level < 50){
			_eventsHandler->triggerEvent(EVENT_TYPE::PRIESTESS_FOUND_TOO_WEAK);
			_player->takeDamage(999999999);
		}
		else{
			_eventsHandler->triggerEvent(EVENT_TYPE::PRIESTESS_FOUND);
		}
	}


	if (previousMap == 0 && _currentMapNumber == 1){
		generateNewMap();
		_player->setPlayerPositionOnGrid(sf::Vector2i(_currentMap->getNewPosition(previousMap).y, _currentMap->getNewPosition(previousMap).x));
		_gameView.setCenter(_player->getPlayerSpritePosition()); //center view on player
		_window.setView(_gameView); //refresh the view
		return false;
	}

	sf::Vector2i currentPosition((int)_player->getPlayerPositionOnGrid().y, (int)_player->getPlayerPositionOnGrid().x);

	//Check for existing maps. If not, create new or pair with new.
	if (_currentMap->getMapExitPoints()[currentPosition] == NULL && previousMap != 0){
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
			_currentMap->drawMap();
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
		_currentMap->drawMap();
	}


	_player->setPlayerPositionOnGrid(sf::Vector2i(_currentMap->getNewPosition(previousMap).y, _currentMap->getNewPosition(previousMap).x));
	_gameView.setCenter(_player->getPlayerSpritePosition()); //center view on player
	_window.setView(_gameView); //refresh the view
	return false;
}

///OBSOLETE!?
void Game::moveToMap(int mapNumber, bool needPair)
{
	if (!needPair){
		std::shared_ptr<Map> ptr(_currentMap->moveToMap(mapNumber));
		_currentMap = ptr;
		_currentMap->drawMap();
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
//'Dis can be used for events!
void Game::generateNewMap()
{
	unsigned int mapID = _currentMapNumber;
	//_currentMapTemplate = rand() % _resHolder->getMapsCount();

	sf::Vector2i position;
	if (!_eventsHandler->getEventsStructure().start_of_game){
		_currentMapTemplate = 0;
		position = sf::Vector2i(4, 7);
		_player->setPlayerPositionOnGrid(sf::Vector2i(position.y, position.x));
	}

	if (mapID == 1){
		_currentMapTemplate = 1;
	}


	_newMap = std::make_shared<Map>(_resHolder->getSpecialMaps().at(_currentMapTemplate), mapID, _mapTexture, _mapTextureDisplayed, _player->getPlayerRating());

	_maps.push_back(_newMap);
	_mapsWithAvaiableExits.push_back(_newMap);


	if (mapID == 1){

		//Now, time pair exits
		std::shared_ptr<Map> transferCurrentMap = _currentMap;
		std::shared_ptr<Map> transferNextMap = _newMap;

		sf::Vector2i currentPos((int)_player->getPlayerPositionOnGrid().y, (int)_player->getPlayerPositionOnGrid().x);

		_currentMap->pairMapAndExitPoint(transferNextMap, currentPos);
		transferNextMap->pairMapAndExitPoint(transferCurrentMap);

		//Recount exits which wasn't paired yet
		checkForExistingFreeExits(_currentMap);
		checkForExistingFreeExits(_newMap);


		Enemy_Stats enemy_template = _resHolder->getSpecialEnemies()[0];
		std::shared_ptr<Enemy> enemy(std::make_shared<Enemy>(0, enemy_template, sf::Vector2i(5, 4), '.', _player->getPlayerRating().overral_rating));
		_newMap->getEnemies().push_back(enemy);
		_newMap->changeMapTile(__ENEMY_ON_MAP__, 5, 4);


	}

	_currentMap = _maps[_maps.size() - 1];

	_gameView.setCenter(_player->getPlayerPositionOnMap()); //center view on player
	_window.setView(_gameView); //refresh the view

	//increment maps id
	_currentMapNumber++;
	_currentMap->drawMap();
	_player->setCurrentMap(_currentMap->getMapId());

}

void Game::generateNewMap(sf::Vector2i currentPos)
{

	//Get new map identifier based on total maps generated
	unsigned int mapID = _currentMapNumber;
	_currentMapNumber++;
	_currentMapTemplate = rand() % _resHolder->getMapsCount();


	//_currentMapNumber = 0;
	if (_currentMapTemplate >= _resHolder->getMapsCount()) _currentMapTemplate = 0;

	//Create new map and then draw it
	if (mapID == 40){
		_newMap = std::make_shared<Map>(_resHolder->getSpecialMaps().at(2), mapID, _mapTexture, _mapTextureDisplayed, _player->getPlayerRating());
	}
	else if (mapID == 100){
		_newMap = std::make_shared<Map>(_resHolder->getSpecialMaps().at(3), mapID, _mapTexture, _mapTextureDisplayed, _player->getPlayerRating());
	}
	else _newMap = createMapSharedPointer(mapID);

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
	_currentMap = _maps[_maps.size() - 1];


	//Generate enemies!
	//Here for special maps:
	if (mapID == 40){
		Enemy_Stats enemy_template = _resHolder->getSpecialEnemies()[1];
		std::shared_ptr<Enemy> enemy(std::make_shared<Enemy>(0, enemy_template, sf::Vector2i(3, 2), '.', _player->getPlayerRating().overral_rating));
		_currentMap->getEnemies().push_back(enemy);
		_currentMap->changeMapTile(__ENEMY_ON_MAP__, 3, 2);
	}
	else if (mapID == 100){
		Enemy_Stats enemy_template = _resHolder->getSpecialEnemies()[2];
		std::shared_ptr<Enemy> enemy(std::make_shared<Enemy>(0, enemy_template, sf::Vector2i(3, 2), '.', _player->getPlayerRating().overral_rating));
		_currentMap->getEnemies().push_back(enemy);
		_currentMap->changeMapTile(__ENEMY_ON_MAP__, 3, 2);
	}
	//Regular ones
	else {
		int tiley = 0;
		int enemy_id = 0;
		std::uniform_int_distribution<int> randomize(0, _resHolder->getAllEnemies().size() - 1);
		for (auto row : _currentMap->getMap()){
			int tilex = 0;
			for (auto tile : row){
				if (tile == '.'){
					int chance = rand() % 100;
					if (chance > 90){
						Enemy_Stats enemy_template = _resHolder->getAllEnemies()[randomize(_generator)];
						std::shared_ptr<Enemy> enemy(std::make_shared<Enemy>(enemy_id, enemy_template, sf::Vector2i(tilex, tiley), tile, _player->getPlayerRating().overral_rating));
						_currentMap->getEnemies().push_back(enemy);
						_currentMap->changeMapTile(__ENEMY_ON_MAP__, tilex, tiley);
						enemy_id++;
					}
				}
				tilex++;
			}
			tiley++;
		}
	}
	_currentMap->drawMap();
	_player->setCurrentMap(_currentMap->getMapId());

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

	Hero_Ratings new_rating = _player->getPlayerRating();
	std::shared_ptr<Map> ptr(std::make_shared<Map>(_resHolder->getMapFromHolder(_currentMapTemplate), mapID, _mapTexture, _mapTextureDisplayed, new_rating));
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
	_ticks += 100;

	while (_ticks >= __TICKS_PER_TURN__){
		_turns_taken++;
		_ticks -= __TICKS_PER_TURN__;
	}

	while (_turns_taken >= __TURNS_TO_INCREMENT_MAP_RESPAWN_TIMER__){
		if (_turns_taken >= __TURNS_TO_INCREMENT_MAP_RESPAWN_TIMER__){
			increaseMapsRespawnCounter(true);
			_turns_taken -= __TURNS_TO_INCREMENT_MAP_RESPAWN_TIMER__;
		}
	}
	_isEnemyTurn = true;
	_player->takeTurn();
	
	updateEvents();

	_gameWindowInterface->refreshBars(_player->getPlayerStats());
}

void Game::heroDropsItem()
{
		std::shared_ptr<Item> item = _player->dropSelectedItem(_inventoryWindow.getHighlitItem(), _inventoryWindow.isHighlitInBag());
		if (item == nullptr) return;
		_currentMap->pushItemToMapStorage(_player->getPlayerPositionOnGrid(), item);
		_inventoryWindow.putItemsOnTiles();
}
///////////////
//Enemy stuff//
///////////////

void Game::enemyTurn()
{
	if (_isEnemyTurn){
		sf::Vector2i playerPos = _player->getPlayerPositionOnGrid();
		//std::uniform_int_distribution<int> randomize(0, 5);
		sf::Vector2i change;
		for (auto enemy : _currentMap->getEnemies()){
			//if dead, why even bother?
			if (!enemy->checkIfAlive()) continue;

			sf::Vector2i enemyPos = enemy->getEnemyPositionOnGrid();

			//if player is nearby, attack him
			if (isPlayerNearby(enemyPos)){
				int dmg = enemy->getEnemyStats().attack;
				_player->takeDamage(dmg);
				continue;
			}

			if (!enemy->isAlarmed() && enemy->getEnemyType() != ENEMY_TYPE::UNDEAD_ENEMY){
				sf::Vector2i normalized = playerPos - enemyPos;
				int range = sqrt(pow(normalized.x, 2) + pow(normalized.y, 2));
				enemy->isPlayerInAggroRange(range);
			}

			//bool canMove = false;
			//if undead enemy, then set to unalarmed after attack. They are neutral
			if (enemy->getEnemyType() == ENEMY_TYPE::UNDEAD_ENEMY){
				enemy->setAlarmStatus(false);
			}

			std::vector<std::vector<char>> mapTemplate = _currentMap->getMap();
			int direction = checkEnemyMovement(enemyPos, enemy, mapTemplate);

			switch (direction){
			case Enemy::UP:
				change = sf::Vector2i(0, -1);
				break;

			case Enemy::DOWN:
				change = sf::Vector2i(0, 1);
				break;

			case Enemy::RIGHT:
				change = sf::Vector2i(1, 0);
				break;

			case Enemy::LEFT:
				change = sf::Vector2i(-1, 0);
				break;

			default:
				change = sf::Vector2i(0, 0);
				//std::cout << "waitin'" << std::endl;
				break;

			}

			enemyPos += change;

			_currentMap->moveEnemy(enemy, enemyPos);

		}
		_isEnemyTurn = false;
		_currentMap->updateMap();
		if (_player->isPlayerDead() && _currentMap->getMapId() == 100){
			_isHeroDead = true;
			_eventsHandler->triggerEvent(EVENT_TYPE::PRIESTESS_FOUND_HERO_LOST);
		}
		else if (_player->isPlayerDead()){
			_isHeroDead = true;
			_eventsHandler->triggerEvent(EVENT_TYPE::HERO_DIES);
		}
	}
}

int Game::checkEnemyMovement(sf::Vector2i enemy_pos, std::shared_ptr<Enemy> &enemy, std::vector<std::vector<char>> &mapTemplate)
{
	sf::Vector2i player_pos = _player->getPlayerPositionOnGrid();
	sf::Vector2i temp_enemy_pos = enemy_pos;
	int direction = 0;
	if (!enemy->isAlarmed()){
		std::uniform_int_distribution<int> randomize(0, 5);
		//return randomize(_generator);
		int direction = 0;
		while (1){
			direction = randomize(_generator);
			temp_enemy_pos = enemy_pos;
			switch (direction){
			case Enemy::UP:
				temp_enemy_pos += sf::Vector2i(0, -1);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x' 
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__ 
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
					return direction;
				}
				break;
			case Enemy::DOWN:
				temp_enemy_pos += sf::Vector2i(0, +1);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x' 
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
					return direction;
				}
				break;
			case Enemy::LEFT:
				temp_enemy_pos += sf::Vector2i(-1, 0);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
					return direction;
				}
				break;
			case Enemy::RIGHT:
				temp_enemy_pos += sf::Vector2i(+1, 0);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
					return direction;
				}
				break;
			default: return direction;
			}
			
		}
	}
	
	if (enemy->isAlarmed()){
		//enemy is on the right side of player
		if (enemy_pos.x > player_pos.x){
			//check if there is anything on the way
			temp_enemy_pos = enemy_pos + sf::Vector2i(-1, 0);
			if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'x'
				|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == __ENEMY_ON_MAP__
				|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'E'){
				//move to the up or down
				//but first move up
				temp_enemy_pos = enemy_pos + sf::Vector2i(0, -1);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'
					&& enemy->getPreviousDirection() != Enemy::UP
					&& enemy->getActualDirection() != Enemy::DOWN){
					return Enemy::UP;
				}
				//or move down
				temp_enemy_pos = enemy_pos + sf::Vector2i(0, +1); 
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
					return Enemy::DOWN;
				}
				//or don't move.
				else {
					return 77;
				}

			}
			//if nothin on the way, move left
			else{
				return Enemy::LEFT;
			}

		}
		//enemy is on the left side of player
		if (enemy_pos.x < player_pos.x){
			//check if there is anything on the way
			temp_enemy_pos = enemy_pos + sf::Vector2i(+1, 0);
			if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'x' 
				|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == __ENEMY_ON_MAP__
				|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'E'){
				//move to the up or down
				//but first move up
				temp_enemy_pos = enemy_pos + sf::Vector2i(0, -1);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'
					&& enemy->getPreviousDirection() != Enemy::UP
					&& enemy->getActualDirection() != Enemy::DOWN){
					return Enemy::UP;
				}
				//or move down
				temp_enemy_pos = enemy_pos + sf::Vector2i(0, +1);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
					return Enemy::DOWN;
				}
				//or don't move.
				else {
					return 77;
				}
				
			}
			//if nothin on the way, move right
			else{
				return Enemy::RIGHT;
			}

		}
		//enemy is on the down side of player
		if (enemy_pos.y > player_pos.y){
			//check if there is anything on the way
			temp_enemy_pos = enemy_pos + sf::Vector2i(0, -1);
			if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'x'
				|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == __ENEMY_ON_MAP__
				|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'E'){
				//move to the left or right
				//but first move left
				temp_enemy_pos = enemy_pos + sf::Vector2i(-1, 0);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'
					&& enemy->getPreviousDirection() != Enemy::LEFT
					&& enemy->getActualDirection() != Enemy::RIGHT){
					return Enemy::LEFT;
				}
				//or then right
				temp_enemy_pos = enemy_pos + sf::Vector2i(+1, 0);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
					return Enemy::RIGHT;
				}
				//or don't move
				else{
					return 77;
				}

			}
			//if nothing on the way, move up
			else{
				return Enemy::UP;
			}

		}
		//enemy is on the up side of player
		if (enemy_pos.y < player_pos.y){
			//check if there is anything on the way
			temp_enemy_pos = enemy_pos + sf::Vector2i(0, +1);
			if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'x'
				|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == __ENEMY_ON_MAP__
				|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'E'){
				//move to the left or right
				//but first move left
				temp_enemy_pos = enemy_pos + sf::Vector2i(-1, 0);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'
					&& enemy->getPreviousDirection() != Enemy::LEFT
					&& enemy->getActualDirection() != Enemy::RIGHT){
					return Enemy::LEFT;
				}
				//or then right
				temp_enemy_pos = enemy_pos + sf::Vector2i(+1, 0);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
					&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
					return Enemy::RIGHT;
				}
				//or don't move
				else{
					return 77;
				}

			}
			//if nothing on the way, move down
			else{
				return Enemy::DOWN;
			}

		}

		//enemy is on the same XAxis as player
		if (enemy_pos.x == player_pos.x){
			//enemy is on the down side of player
			if (enemy_pos.y > player_pos.y){
				//check if there is anything on the way
				temp_enemy_pos = enemy_pos + sf::Vector2i(0, -1);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'x'
					|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == __ENEMY_ON_MAP__
					|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'E'){
					//move to the left or right
					//but first move left
					temp_enemy_pos = enemy_pos + sf::Vector2i(-1, 0);
					if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
						return Enemy::LEFT;
					}
					//or then right
					temp_enemy_pos = enemy_pos + sf::Vector2i(+1, 0);
					if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
						return Enemy::RIGHT;
					}
					//or don't move
					else{
						return 77;
					}

				}
				//if nothing on the way, move up
				else{
					return Enemy::UP;
				}

			}
			//enemy is on the up side of player
			if (enemy_pos.y < player_pos.y){
				//check if there is anything on the way
				temp_enemy_pos = enemy_pos + sf::Vector2i(0, +1);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'x'
					|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == __ENEMY_ON_MAP__
					|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'E'){
					//move to the left or right
					//but first move left
					temp_enemy_pos = enemy_pos + sf::Vector2i(-1, 0);
					if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
						return Enemy::LEFT;
					}
					//or then right
					temp_enemy_pos = enemy_pos + sf::Vector2i(+1, 0);
					if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
						return Enemy::RIGHT;
					}
					//or don't move
					else{
						return 77;
					}

				}
				//if nothing on the way, move down
				else{
					return Enemy::DOWN;
				}

			}

		}

		//enemy is on the same YAxis as player
		if (enemy_pos.y == player_pos.y){
			//enemy is on the right side of player
			if (enemy_pos.x > player_pos.x){
				//check if there is anything on the way
				temp_enemy_pos = enemy_pos + sf::Vector2i(-1, 0);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'x'
					|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == __ENEMY_ON_MAP__
					|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'E'){
					//move to the up or down
					//but first move up
					temp_enemy_pos = enemy_pos + sf::Vector2i(0, -1);
					if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
						return Enemy::UP;
					}
					//or move down
					temp_enemy_pos = enemy_pos + sf::Vector2i(0, +1);
					if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
						return Enemy::DOWN;
					}
					//or don't move.
					else {
						return 77;
					}

				}
				//if nothin on the way, move left
				else{
					return Enemy::LEFT;
				}

			}
			//enemy is on the left side of player
			if (enemy_pos.x < player_pos.x){
				//check if there is anything on the way
				temp_enemy_pos = enemy_pos + sf::Vector2i(+1, 0);
				if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'x'
					|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == __ENEMY_ON_MAP__
					|| mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] == 'E'){
					//move to the up or down
					//but first move up
					temp_enemy_pos = enemy_pos + sf::Vector2i(0, -1);
					if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
						return Enemy::UP;
					}
					//or move down
					temp_enemy_pos = enemy_pos + sf::Vector2i(0, +1);
					if (mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'x'
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != __ENEMY_ON_MAP__
						&& mapTemplate[temp_enemy_pos.y][temp_enemy_pos.x] != 'E'){
						return Enemy::DOWN;
					}
					//or don't move.
					else {
						return 77;
					}

				}
				//if nothin on the way, move right
				else{
					return Enemy::RIGHT;
				}

			}
		}
		//return whatever, since it will sit in one place
		return 77;
	}



	//likewise.
	return 77;
}

bool Game::isPlayerNearby(sf::Vector2i position)
{
	sf::Vector2i player_pos = _player->getPlayerPositionOnGrid();

	if (player_pos == position + sf::Vector2i(1, 0) ||
		player_pos == position + sf::Vector2i(0, 1) ||
		player_pos == position + sf::Vector2i(-1, 0) ||
		player_pos == position + sf::Vector2i(0, -1)){
		return true;
	}
	else{
		return false;
	}
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

	_currentMap->updateMap();
}

///////////////////////
//Item and drop stuff//
///////////////////////

//Need better drop generator here.
void Game::generateDrop(sf::Vector2i position, std::shared_ptr<Enemy> enemy)
{


	int generated_items = (rand() % (enemy->getEnemyClass()/3 + 3)) + enemy->getEnemyClass()/2;

	for (int i = 0; i < generated_items; i++){
		int enemyRating = 0;
		int modifier = rand() % 3 - 1;
		modifier = rand() % 20 * modifier;
		enemyRating = enemy->getEnemyRating() + (int)((float)enemy->getEnemyRating() * ((float)modifier / 100));
		_currentMap->generateItemAtPosition(position, enemyRating);
	}

}

void Game::checkForObjectsAtPlayerPosition()
{
	if (_currentMap->checkForItemsAtTile(_player->getPlayerPositionOnGrid())){
		_player->getPlayerBackpack().push_back(_currentMap->returnItemAtTile(_player->getPlayerPositionOnGrid()));
		_currentMap->updateMap();

		takeTurn();
	}
}


///////////////////
//Save management//
///////////////////
void Game::restoreData()
{
	//first load game data for unusual exceptions
	ResourcesLoader resload(_errorHandler);
	resload.loadGameData();
	_resHolder->loadData();


	//now load game
	_saveState->loadGame();
	//restore player data
	_player->restoreData();
	//reset pointers to player
	_inventoryWindow.setPlayer(_player);
	_statusWindow.setPlayer(_player);
	_player->setGameWindowInterface(_gameWindowInterface);

	//reset maps, but keep event progress!
	//_maps.clear();
	//_mapsWithAvaiableExits.clear();
	//generateNewMap();

	_currentMap = _maps[_player->getCurrentMap()];
	for (auto map : _maps){
		map->restoreMap(_mapTexture, _mapTextureDisplayed);

		//Generate enemies!
		//Here for special maps:
		if (map->getMapId() == 40){
			Enemy_Stats enemy_template = _resHolder->getSpecialEnemies()[1];
			std::shared_ptr<Enemy> enemy(std::make_shared<Enemy>(0, enemy_template, sf::Vector2i(4, 4), '.', _player->getPlayerRating().overral_rating));
			map->getEnemies().push_back(enemy);
			map->changeMapTile(__ENEMY_ON_MAP__, 4, 4);
		}
		//Regular ones
		else {
			int tiley = 0;
			int enemy_id = 0;
			std::uniform_int_distribution<int> randomize(0, _resHolder->getAllEnemies().size() - 1);
			for (auto row : map->getMap()){
				int tilex = 0;
				for (auto tile : row){
					if (tile == '.'){
						int chance = rand() % 100;
						if (chance > 85){
							Enemy_Stats enemy_template = _resHolder->getAllEnemies()[randomize(_generator)];
							std::shared_ptr<Enemy> enemy(std::make_shared<Enemy>(enemy_id, enemy_template, sf::Vector2i(tilex, tiley), tile, _player->getPlayerRating().overral_rating));
							map->getEnemies().push_back(enemy);
							map->changeMapTile(__ENEMY_ON_MAP__, tilex, tiley);
							enemy_id++;
							break;
							break;
						}
					}
					tilex++;
				}
				tiley++;
			}
		}
	}
	
	//center at player
	_gameView.setCenter(_player->getPlayerPositionOnMap()); 
}

void Game::newGame()
{

	//std::shared_ptr<Item> weapon0(std::make_shared<Weapon>(_resHolder->getAllWeapons()[0]));
	//_player->putItemInBackpack(weapon0);

	//_player->_item = weapon0;
	//
	//std::shared_ptr<Item> weapon1(std::make_shared<Weapon>(_resHolder->getAllWeapons()[1]));

	//std::shared_ptr<Consumable> cons0(std::make_shared<Consumable>(_resHolder->getAllConsumables()[0]));
	//_player->putItemInBackpack(cons0);
	//std::shared_ptr<Consumable> cons1(std::make_shared<Consumable>(_resHolder->getAllConsumables()[1]));
	//_player->putItemInBackpack(cons1);
	//std::shared_ptr<Consumable> cons2(std::make_shared<Consumable>(_resHolder->getAllConsumables()[2]));
	//_player->putItemInBackpack(cons2);
	//std::shared_ptr<Consumable> cons3(std::make_shared<Consumable>(_resHolder->getAllConsumables()[3]));
	//_player->putItemInBackpack(cons3);

	//set initial values
	_player->initializeStartValues();
	_eventsHandler->resetEvents();
	_maps.clear();
	_currentMapNumber = 0;
	//refresh interface to match initals
	_gameWindowInterface->refreshBars(_player->getPlayerStats());
	//generate new map
	generateNewMap();
	//trigger first event
	_eventsHandler->triggerEvent(EVENT_TYPE::START_OF_GAME);
	//_eventsHandler->triggerEvent(EVENT_TYPE::FIRST_BOSS_KILLED);

}