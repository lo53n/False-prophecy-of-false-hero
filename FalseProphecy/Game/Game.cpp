#include "Game.h"

Game::Game()
	: _window(sf::VideoMode(800, 640), "SFML Application")
	, _gameView(sf::FloatRect(0.0f, 0.0f, 800.0f, 640.0f))
{
	_player.setPlayerPositionOnMap(sf::Vector2f(64.f, 64.f));

	_gameView.setCenter(_player.getPlayerPositionOnMap());
	_window.setView(_gameView);
}

/////////////
//Main Loop//
/////////////

void Game::run(){

	MapLoader mapLoader;
	mapLoader.loadFromFile();

	_currentMapNumber = 0;
	

	_newMap = new Map(_mapsHolder->getMapFromHolder(_currentMapNumber));

	_newMap->drawMap();
	_maps.push_back(_newMap);
	_currentMap = _maps[0];

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.0f/60.0f);

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
	//Generate next map, not optimalized
	if (key == sf::Keyboard::Return && isPressed){
		std::cout << _currentMapNumber << " Another!" << std::endl;
		_currentMapNumber++;
		if (_currentMapNumber >= _mapsHolder->getMapCount()) _currentMapNumber = 0;
		_newMap = new Map(_mapsHolder->getMapFromHolder(_currentMapNumber));
		_newMap->drawMap();
		_maps.push_back(_newMap);
		_currentMap = _maps[_maps.size() - 1];
	}
	///////////////////////////////
	//Process normal player input//
	///////////////////////////////

	//Map Movement//
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
		_window.setView(_gameView);
	}
	//Player Movement//
	if (key >= sf::Keyboard::Left && key <= sf::Keyboard::Down && isPressed){
		bool canMove = false;
		sf::Vector2i checkForPosition;
		switch (key){

		case sf::Keyboard::Up:
			checkForPosition = _player.getPlayerPositionOnGrid() - sf::Vector2i(0, 1);
			if (_currentMap->getMap()[checkForPosition.y][checkForPosition.x] != 'x')
				canMove = true;
			else std::cout << "shit! " << checkForPosition.x << " " << checkForPosition.y << std::endl;
			if (canMove)
				_player.movePlayer(Player::UP);
			break;

		case sf::Keyboard::Right:
			checkForPosition = _player.getPlayerPositionOnGrid() - sf::Vector2i(-1, 0);
			if (_currentMap->getMap()[checkForPosition.y][checkForPosition.x] != 'x')
				canMove = true;
			else std::cout << "shit! " << checkForPosition.x << " " << checkForPosition.y << std::endl;
			if (canMove) 
				_player.movePlayer(Player::RIGHT);
			break;

		case sf::Keyboard::Down:
			checkForPosition = _player.getPlayerPositionOnGrid() - sf::Vector2i(0, -1);
			if (_currentMap->getMap()[checkForPosition.y][checkForPosition.x] != 'x')
				canMove = true;
			else std::cout << "shit! " << checkForPosition.x << " " << checkForPosition.y << std::endl;
			if (canMove) 
				_player.movePlayer(Player::DOWN);
			break;

		case sf::Keyboard::Left:
			checkForPosition = _player.getPlayerPositionOnGrid() - sf::Vector2i(1, 0);
			if (_currentMap->getMap()[checkForPosition.y][checkForPosition.x] != 'x')
				canMove = true;
			else std::cout << "shit! " << checkForPosition.x << " " << checkForPosition.y << std::endl;
			if (canMove)
				_player.movePlayer(Player::LEFT);
		}

		/*if (key == sf::Keyboard::Up)
			_player.movePlayer(Player::UP);
		else if (key == sf::Keyboard::Right)
			_player.movePlayer(Player::RIGHT);
		else if (key == sf::Keyboard::Down)
			_player.movePlayer(Player::DOWN);
		else if (key == sf::Keyboard::Left)
			_player.movePlayer(Player::LEFT);*/
		_gameView.setCenter(_player.getPlayerPositionOnMap());
		_window.setView(_gameView);
		std::cout << _currentMap->getMap()[_player.getPlayerPositionOnGrid().y][_player.getPlayerPositionOnGrid().x] << std::endl;
	}


	//TODO: Debug Menu
}