#include "Player.h"

Player::Player()
{
	sf::RectangleShape player;
	player.setSize(sf::Vector2f(__PLAYER_HEIGHT__, __PLAYER_WIDTH__));
	player.setPosition(0.f, 0.f);
	player.setFillColor(sf::Color::Red);

	_playerTexture.create(__PLAYER_WIDTH__, __PLAYER_HEIGHT__);
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
sf::Vector2f& Player::getPlayerPosition()
{
	return _position;
}
sf::Vector2f& Player::getPlayerPositionOnGrid()
{
	return _positionOnGrid;
}
///////////////////
//Player movement//
///////////////////
void Player::movePlayer(int direction)
{
	sf::Vector2f movement;

	switch (direction){
	case 0:
		movement = sf::Vector2f(0, -1);
		break;
	case 1:
		movement = sf::Vector2f(1, 0);
		break;
	case 2:
		movement = sf::Vector2f(0, 1);
		break;
	case 3:
		movement = sf::Vector2f(-1, 0);
		break;

	}
	_positionOnGrid += movement;
	_position += movement * __PLAYER_HEIGHT__;
	_playerSprite.setPosition(_position);
}