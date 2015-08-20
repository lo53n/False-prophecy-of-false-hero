#include "Enemy.h"

Enemy::Enemy(sf::Vector2i positionOnGrid, char newTile)
	: _positionOnGrid(positionOnGrid),
	_tile_underneath(newTile)
{
	_positionOnMap = (sf::Vector2f)(_positionOnGrid * (int)__ENEMY_HEIGHT__);
	_enemyShape.setSize(sf::Vector2f(__ENEMY_WIDTH__, __ENEMY_HEIGHT__));
	_enemyShape.setPosition(_positionOnMap);
	_enemyShape.setFillColor(sf::Color(15, 200, 100, 255));
}

Enemy::~Enemy()
{

}


///////////
//Getters//
///////////

sf::Vector2f& Enemy::getEnemyPositionOnMap()
{
	return _positionOnMap;
}

sf::Vector2i& Enemy::getEnemyPositionOnGrid()
{
	return _positionOnGrid;
}

char Enemy::getTileUnderneathEnemy()
{
	return _tile_underneath;
}

///////////
//Setters//
///////////

void Enemy::setEnemyPositionOnMap(sf::Vector2f newPositionOnMap)
{
	_positionOnMap = newPositionOnMap;
	_positionOnGrid = (sf::Vector2i)(_positionOnMap / __ENEMY_HEIGHT__);
	_enemyShape.setPosition(_positionOnMap);
}

void Enemy::setEnemyPositionOnGrid(sf::Vector2i newPositionOnGrid)
{
	_positionOnGrid = newPositionOnGrid;
	_positionOnMap = (sf::Vector2f)(_positionOnGrid * (int)__ENEMY_HEIGHT__);
	_enemyShape.setPosition(_positionOnMap);
}

void Enemy::SetTileUnderneathEnemy(char newTile)
{
	_tile_underneath = newTile;
}

///////////
//Drawing//
///////////

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isAlive){
		target.draw(_enemyShape);
	}
}

//////////////
//Swap tiles//
//////////////

char Enemy::swapTileUnderneathToNextOne(char newTile)
{
	char temp = _tile_underneath;
	_tile_underneath = newTile;
	return temp;
}

//////////////////////
//Manage enemy death//
//////////////////////
bool Enemy::checkIfAlive()
{
	return isAlive;
}

void Enemy::killEnemy()
{
	std::cout << "Enemy is killed" << std::endl;
	isAlive = false;
}

void Enemy::resurrectAndReinforce()
{
	resurrectEnemy();
	reinforceEnemy();
}

void Enemy::resurrectEnemy()
{
	isAlive = true;
}

void Enemy::reinforceEnemy()
{

}