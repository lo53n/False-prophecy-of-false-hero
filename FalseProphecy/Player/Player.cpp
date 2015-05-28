#include "Player.h"

Player::Player()
{
	sf::RectangleShape player;
	player.setSize(sf::Vector2f(__PLAYER_HEIGHT__, __PLAYER_WIDTH__));
	player.setPosition(0.0f, 0.0f);
	player.setFillColor(sf::Color::Red);

	_playerTexture.create((unsigned int)__PLAYER_WIDTH__, (unsigned int)__PLAYER_HEIGHT__);
	_playerTexture.clear();
	_playerTexture.draw(player);
	_playerTexture.display();

	_playerSprite.setTexture(_playerTexture.getTexture());

	std::cout <<"ENUM: "<< Player::DOWN << std::endl;
}
Player::~Player()
{

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(_playerSprite);

}

///////////
//Getters//
///////////

sf::Vector2f& Player::getPlayerPositionOnMap()
{
	return _positionOnMap;
}
sf::Vector2i& Player::getPlayerPositionOnGrid()
{
	return _positionOnGrid;
}

///////////
//Setters//
///////////

void Player::setPlayerPositionOnMap(sf::Vector2f newPositionOnMap)
{
	_positionOnMap = newPositionOnMap;
	_positionOnGrid = (sf::Vector2i)(_positionOnMap / __PLAYER_HEIGHT__);
	_playerSprite.setPosition(_positionOnMap);
}

void Player::setPlayerPositionOnGrid(sf::Vector2i newPositionOnGrid)
{
	_positionOnGrid = newPositionOnGrid;
	_positionOnMap = (sf::Vector2f)(_positionOnGrid * (int)__PLAYER_HEIGHT__);
	_playerSprite.setPosition(_positionOnMap);
}
///////////////////
//Player movement//
///////////////////

void Player::movePlayer(int direction)
{
	sf::Vector2i movement;

	switch (direction){
	case 0:
		movement = sf::Vector2i(0, -1);
		break;
	case 1:
		movement = sf::Vector2i(1, 0);
		break;
	case 2:
		movement = sf::Vector2i(0, 1);
		break;
	case 3:
		movement = sf::Vector2i(-1, 0);
		break;

	}
	_positionOnGrid += movement;
	_positionOnMap += (sf::Vector2f)(movement * (int)__PLAYER_HEIGHT__);
	_playerSprite.setPosition(_positionOnMap);
	//std::cout << "My position on grid: " << _positionOnGrid.x << " " << _positionOnGrid.y << std::endl;
	//std::cout << "My position on map: " << _positionOnMap.x << " " << _positionOnMap.y << std::endl;
}