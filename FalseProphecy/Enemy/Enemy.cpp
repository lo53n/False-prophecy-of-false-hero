#include "Enemy.h"

Enemy::Enemy(int enemy_id, Enemy_Stats enemy_template, sf::Vector2i positionOnGrid, char newTile, int heroRating)
	: _enemy_id(enemy_id),
	_stats(enemy_template),
	_baseStats(enemy_template),
	_positionOnGrid(positionOnGrid),
	_tile_underneath(newTile)
{
	_positionOnMap = (sf::Vector2f)(_positionOnGrid * (int)__ENEMY_HEIGHT__);
	_enemyShape.setSize(sf::Vector2f(__ENEMY_WIDTH__, __ENEMY_HEIGHT__));
	_enemyShape.setPosition(_positionOnMap);
	_enemyShape.setFillColor(sf::Color(15, 200, 100, 255));

	_enemyCorpseShape.setSize(sf::Vector2f(__ENEMY_WIDTH__, __ENEMY_HEIGHT__));
	_enemyCorpseShape.setPosition(_positionOnMap);
	_enemyCorpseShape.setFillColor(sf::Color(150, 200, 100, 255));

	_hpBar.setSize(sf::Vector2f(30.f, 3.f));
	_hpBar.setPosition(sf::Vector2f(_enemyShape.getPosition().x + 1.f, _enemyShape.getPosition().y + 25.f));
	_hpBar.setFillColor(sf::Color(0, 255, 0, 255));

	_underHpBar.setSize(_hpBar.getSize());
	_underHpBar.setPosition(_hpBar.getPosition());
	_underHpBar.setFillColor(sf::Color());

	//_stats.max_hitpoints = 10;
	//_stats.hitpoints = 10;
	//_stats.defence = 1;
	//_stats.hitpoints = _stats.max_hitpoints;

	Calculations::calculateNewStats(_stats, heroRating);
	_stats.hitpoints = _stats.max_hitpoints;

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

int Enemy::getEnemyId()
{
	return _enemy_id;
}

Enemy_Stats Enemy::getEnemyStats()
{
	return _stats;
}

int Enemy::getEnemyRating()
{
	return _stats.current_rating;
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
		target.draw(_underHpBar);
		target.draw(_hpBar);
	}
	else{
		target.draw(_enemyCorpseShape);
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
//Attack and defence//
//////////////////////

void Enemy::takeHit(int damage)
{

	//int dmgTaken = damage - _stats.defence;
	int dmgTaken = damage;

	if (dmgTaken < 0) dmgTaken = 0;
	_stats.hitpoints-= dmgTaken;
	float percentage = (float)_stats.hitpoints / (float)_stats.max_hitpoints;


	int green, red;

	green = (int)(255 * percentage);
	red = (int)(255 * (1 - percentage));

	_hpBar.setFillColor(sf::Color(red, green, 0, 255));
	_hpBar.setScale(percentage, 1.f);

	if (_stats.hitpoints <= 0){
		killEnemy();
	}
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
	//std::cout << "Enemy is killed" << std::endl;
	isAlive = false;
	_enemyCorpseShape.setPosition(_enemyShape.getPosition());
}

void Enemy::resurrectAndReinforce(int heroRating)
{
	reinforceEnemy(heroRating);
	resurrectEnemy();
}

void Enemy::resurrectEnemy()
{
	isAlive = true;
	_stats.hitpoints = _stats.max_hitpoints;
	_hpBar.setScale(1.f, 1.f);
	_hpBar.setFillColor(sf::Color(0, 255, 0, 255));
}

void Enemy::reinforceEnemy(int heroRating)
{
	_stats = _baseStats;
	Calculations::calculateNewStats(_stats, heroRating);
}