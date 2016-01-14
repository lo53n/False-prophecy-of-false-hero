#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(int id, char tile, Enemy_Stats stats, Enemy_Stats base_stats, sf::Vector2i posOnGrid, sf::Vector2f posOnMap)
	:
	_stats(stats),
	_enemy_id(id),
	_tile_underneath(tile),
	_baseStats(base_stats),
	_positionOnGrid(posOnGrid),
	_positionOnMap(posOnMap)
{

}

Enemy::Enemy(int enemy_id, Enemy_Stats enemy_template, sf::Vector2i positionOnGrid, char newTile, int heroRating)
	:
	_enemy_id(enemy_id),
	_stats(enemy_template),
	_baseStats(enemy_template),
	_positionOnGrid(positionOnGrid),
	_tile_underneath(newTile)
{
	setAggroRange();
	_positionOnMap = (sf::Vector2f)(_positionOnGrid * (int)__ENEMY_HEIGHT__);

	if (!_enemyTexture.loadFromFile(_stats.img_path, sf::IntRect(0,0,32,32))){
		switch (_stats.type){
		case ENEMY_TYPE::BEAST_ENEMY:
			_enemyTexture.loadFromFile(__ENEMY_DEFAULT_BEAST__, sf::IntRect(0, 0, 32, 32));
			break;
		case ENEMY_TYPE::UNDEAD_ENEMY:
			_enemyTexture.loadFromFile(__ENEMY_DEFAULT_UNDEAD__, sf::IntRect(0, 0, 32, 32));
			break;
		case ENEMY_TYPE::DEMON_ENEMY:
			_enemyTexture.loadFromFile(__ENEMY_DEFAULT_DEMON__, sf::IntRect(0, 0, 32, 32));
			break;
		case ENEMY_TYPE::HUMANOID_ENEMY:
			_enemyTexture.loadFromFile(__ENEMY_DEFAULT_HUMANOID__, sf::IntRect(0, 0, 32, 32));
			break;
		case ENEMY_TYPE::HUMAN_ENEMY:
			_enemyTexture.loadFromFile(__ENEMY_DEFAULT_HUMAN__, sf::IntRect(0, 0, 32, 32));
			break;
		case ENEMY_TYPE::GOLEM_ENEMY:
			_enemyTexture.loadFromFile(__ENEMY_DEFAULT_GOLEM__, sf::IntRect(0, 0, 32, 32));
			break;
		}
	}
	_enemyCorpseTexture.loadFromFile("data\\img\\enemy\\grave.png");


	_enemyShape.setSize(sf::Vector2f(__ENEMY_WIDTH__, __ENEMY_HEIGHT__));
	_enemyShape.setPosition(_positionOnMap);
	//_enemyShape.setFillColor(sf::Color(15, 200, 100, 255));
	_enemyShape.setTexture(&_enemyTexture);

	_enemyCorpseShape.setSize(sf::Vector2f(__ENEMY_WIDTH__, __ENEMY_HEIGHT__));
	_enemyCorpseShape.setPosition(_positionOnMap);
	_enemyCorpseShape.setTexture(&_enemyCorpseTexture);

	_hpBar.setSize(sf::Vector2f(30.f, 3.f));
	_hpBar.setPosition(sf::Vector2f(_enemyShape.getPosition().x + 1.f, _enemyShape.getPosition().y + 25.f));
	_hpBar.setFillColor(sf::Color(0, 255, 0, 255));

	_underHpBar.setSize(_hpBar.getSize());
	_underHpBar.setPosition(_hpBar.getPosition());
	_underHpBar.setFillColor(sf::Color());
	_underHpBar.setOutlineThickness(1.f);
	_underHpBar.setOutlineColor(sf::Color::Black);


	if (!_stats.special){
		Calculations::calculateNewStats(_stats, heroRating);
	}
	else{
		Calculations::calculateBaseRating(_stats);
		_stats.base_rating += 500;
		_stats.current_rating = _stats.base_rating;
	}

	_stats.hitpoints = _stats.max_hitpoints;


	//Set coloring based on monster class
	switch (_stats.enemy_class)
	{
	case ENEMY_CLASS::RARE_ENEMY:
		_enemyShape.setFillColor(sf::Color(15, 150, 50, 255));
		break;
	case ENEMY_CLASS::MAGIC_ENEMY:
		_enemyShape.setFillColor(sf::Color(15, 15, 200, 255));
		break;
	case ENEMY_CLASS::ELITE_ENEMY:
		_enemyShape.setFillColor(sf::Color(100, 200, 100, 255));
		break;
	case ENEMY_CLASS::MINIBOSS_ENEMY:
		_enemyShape.setFillColor(sf::Color(15, 15, 100, 255));
		break;
	case ENEMY_CLASS::BOSS_ENEMY:
		_enemyShape.setFillColor(sf::Color(40, 40, 40, 255));
		break;

	}


}

Enemy::~Enemy()
{

}

void Enemy::restoreData()
{
	setAggroRange();

	if (!_enemyTexture.loadFromFile(_stats.img_path, sf::IntRect(0, 0, 32, 32))){
		switch (_stats.type){
		case ENEMY_TYPE::BEAST_ENEMY:
			_enemyTexture.loadFromFile(__ENEMY_DEFAULT_BEAST__, sf::IntRect(0, 0, 32, 32));
			break;
		case ENEMY_TYPE::UNDEAD_ENEMY:
			_enemyTexture.loadFromFile(__ENEMY_DEFAULT_UNDEAD__, sf::IntRect(0, 0, 32, 32));
			break;
		case ENEMY_TYPE::DEMON_ENEMY:
			_enemyTexture.loadFromFile(__ENEMY_DEFAULT_DEMON__, sf::IntRect(0, 0, 32, 32));
			break;
		case ENEMY_TYPE::HUMANOID_ENEMY:
			_enemyTexture.loadFromFile(__ENEMY_DEFAULT_HUMANOID__, sf::IntRect(0, 0, 32, 32));
			break;
		case ENEMY_TYPE::HUMAN_ENEMY:
			_enemyTexture.loadFromFile(__ENEMY_DEFAULT_HUMAN__, sf::IntRect(0, 0, 32, 32));
			break;
		case ENEMY_TYPE::GOLEM_ENEMY:
			_enemyTexture.loadFromFile(__ENEMY_DEFAULT_GOLEM__, sf::IntRect(0, 0, 32, 32));
			break;
		}
	}


	_enemyCorpseTexture.loadFromFile("data\\img\\enemy\\grave.png");


	_enemyShape.setSize(sf::Vector2f(__ENEMY_WIDTH__, __ENEMY_HEIGHT__));
	_enemyShape.setPosition(_positionOnMap);
	//_enemyShape.setFillColor(sf::Color(15, 200, 100, 255));
	_enemyShape.setTexture(&_enemyTexture);

	_enemyCorpseShape.setSize(sf::Vector2f(__ENEMY_WIDTH__, __ENEMY_HEIGHT__));
	_enemyCorpseShape.setPosition(_positionOnMap);
	_enemyCorpseShape.setTexture(&_enemyCorpseTexture);

	_hpBar.setSize(sf::Vector2f(30.f, 3.f));
	_hpBar.setPosition(sf::Vector2f(_enemyShape.getPosition().x + 1.f, _enemyShape.getPosition().y + 25.f));
	_hpBar.setFillColor(sf::Color(0, 255, 0, 255));

	_underHpBar.setSize(_hpBar.getSize());
	_underHpBar.setPosition(_hpBar.getPosition());
	_underHpBar.setFillColor(sf::Color());
	_underHpBar.setOutlineThickness(1.f);
	_underHpBar.setOutlineColor(sf::Color::Black);


	//Set coloring based on monster class
	switch (_stats.enemy_class)
	{
	case ENEMY_CLASS::RARE_ENEMY:
		_enemyShape.setFillColor(sf::Color(15, 150, 50, 255));
		break;
	case ENEMY_CLASS::MAGIC_ENEMY:
		_enemyShape.setFillColor(sf::Color(15, 15, 200, 255));
		break;
	case ENEMY_CLASS::ELITE_ENEMY:
		_enemyShape.setFillColor(sf::Color(100, 200, 100, 255));
		break;
	case ENEMY_CLASS::MINIBOSS_ENEMY:
		_enemyShape.setFillColor(sf::Color(15, 15, 100, 255));
		break;
	case ENEMY_CLASS::BOSS_ENEMY:
		_enemyShape.setFillColor(sf::Color(40, 40, 40, 255));
		break;

	}
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

int Enemy::getEnemyType()
{
	return _stats.type;
}

int Enemy::getEnemyRating()
{
	return _stats.current_rating;
}

int Enemy::getEnemyClass()
{
	return _stats.enemy_class;
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

void Enemy::setTileUnderneathEnemy(char newTile)
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

/////////////////
//Agressiveness//
/////////////////

void Enemy::setAlarmStatus(bool status)
{
	_isAlarmed = status;

}
bool Enemy::isAlarmed()
{
	return _isAlarmed;
}

void Enemy::isPlayerInAggroRange(int range)
{
	if (range <= _aggroRange){
		setAlarmStatus(true);
	}
}

void Enemy::setAggroRange()
{
	switch (_stats.type){

	case ENEMY_TYPE::BEAST_ENEMY:
		_aggroRange = 10;
		break;
	case ENEMY_TYPE::DEMON_ENEMY:
		_aggroRange = 8;
		break;
	case ENEMY_TYPE::GOLEM_ENEMY:
		_aggroRange = 2;
		break;
	case ENEMY_TYPE::HUMANOID_ENEMY:
		_aggroRange = 6;
		break;
	case ENEMY_TYPE::HUMAN_ENEMY:
		_aggroRange = 4;
		break;
	case ENEMY_TYPE::UNDEAD_ENEMY:
		_aggroRange = 0;
		break;



	}
}

//////////////
//Directions//
//////////////

void Enemy::setDirection(int direction)
{
	_direction_2 = _direction_1;
	_direction_1 = _direction;
	_direction = direction;
}
int Enemy::getActualDirection()
{
	return _direction;
}
int Enemy::getPreviousDirection()
{
	return _direction_1;
}
int Enemy::getBackPreviousDirection()
{
	return _direction_2;
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
	std::cout << "DMG TAKEN: " << damage << std::endl;

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
	_enemyCorpseShape.setPosition((sf::Vector2f)getEnemyPositionOnGrid()*32.f);
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

////////////
//Movement//
////////////

void Enemy::moveEnemy(sf::Vector2i newPos)
{
	//decreaseTicks();

	if (_positionOnMap != _enemyShape.getPosition()){
		_enemyShape.setPosition(_positionOnMap);
		_hpBar.setPosition(sf::Vector2f(_enemyShape.getPosition().x + 1.f, _enemyShape.getPosition().y + 25.f));
		_underHpBar.setPosition(_hpBar.getPosition());
	}

	//temporary???
	if (newPos.x > _positionOnGrid.x){
		setDirection(MOVEMENT::RIGHT);
	}
	else if (newPos.y > _positionOnGrid.y){
		setDirection(MOVEMENT::DOWN);
	}
	else if (newPos.x < _positionOnGrid.x){
		setDirection(MOVEMENT::LEFT);
	}
	else if (newPos.y < _positionOnGrid.y){
		setDirection(MOVEMENT::UP);
	}
	else {
		setDirection(6);
	}

	//std::cout << "Move Enemy ID " << getEnemyId() << std::endl;
	//std::cout << "x,y " << _positionOnGrid.x << " " << _positionOnGrid.y << std::endl;

	//std::cout << "new pos " << newPos.x << " " << newPos.y << std::endl;
	_positionOnGrid = newPos;

	//std::cout << "x,y " << _positionOnGrid.x << " " << _positionOnGrid.y << std::endl;
	_positionOnMap = (sf::Vector2f)_positionOnGrid * 32.f;


	_isNeedToMoveSprite = true;
}

bool Enemy::checkIfThereIsNeedToAnimate()
{
	return _isNeedToMoveSprite;
}

void Enemy::moveSprite(float change)
{

	sf::Vector2f changeToSprite;
	switch (_direction){
	case 0:
		changeToSprite = sf::Vector2f(0, -change);
		break;
	case 1:
		changeToSprite = sf::Vector2f(change, 0);
		break;
	case 2:
		changeToSprite = sf::Vector2f(0, change);
		break;
	case 3:
		changeToSprite = sf::Vector2f(-change, 0);
		break;
	default:
		break;
	}



	_enemyShape.setPosition(_enemyShape.getPosition() + changeToSprite);
	_hpBar.setPosition(sf::Vector2f(_enemyShape.getPosition().x + 1.f, _enemyShape.getPosition().y + 25.f));
	_underHpBar.setPosition(_hpBar.getPosition());


	//std::cout << "Shape pos: " << _enemyShape.getPosition().x << ":" << _enemyShape.getPosition().y << " TargetPos: " << _positionOnMap.x << ":" << _positionOnMap.y << std::endl;
	if (_positionOnMap == _enemyShape.getPosition()){
		_isNeedToMoveSprite = false;
	}


}
/////////
//Other//
/////////
void Enemy::increaseTicks(int &amount)
{
}

void Enemy::decreaseTicks()
{
}

bool Enemy::checkIfCanTakeAction()
{
	return _canTakeAction;
}