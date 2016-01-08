#include "Map.h"

Map::Map()
{
	//_mapTexture.create(800, 600);
	//_mapTexture.clear();

}
Map::Map(int id, int resCount, std::vector<std::vector<char>>& mapTemplate, int maxX, int maxY/*,
	std::vector<std::shared_ptr<Enemy>> &enemies, std::vector<std::shared_ptr<Enemy>> &deadenemies,
	std::vector<sf::Vector2i> &exitPoints, std::vector<sf::Vector2i> &notPairedExits,
	std::unordered_map<sf::Vector2i, std::shared_ptr<Map>> &mapExits,
	std::unordered_multimap<sf::Vector2i, std::shared_ptr<Item>> &itemsOnMap*/)
:
_mapIdentifier(id),
_respawn_counter(resCount),
_mapTemplate(mapTemplate),
_maxDimensionX(maxX),
_maxDimensionY(maxY)/*,
_enemies(enemies),
_deadenemies(deadenemies),
_exitPoints(exitPoints),
_notPairedExitPoints(notPairedExits),
_mapExits(mapExits),
_itemsOnMap(itemsOnMap)*/

{

}



Map::Map(std::vector<std::vector<char>> mapTemplate, unsigned int mapID, sf::RenderTexture& renderTexture, sf::RenderTexture& renderTextureDisplayed, Hero_Ratings ratings)
	: _mapTemplate(mapTemplate),
	_mapIdentifier(mapID),
	_renderTexture(&renderTexture),
	_renderTextureDisplayed(&renderTextureDisplayed),
	_ratings(ratings)
{
	checkMaxSizes(); 
	findAllExitPoints();


	_wallTile.setTexture(_resHolder->getWallTexture());
	_floorTile.setTexture(_resHolder->getTileTexture());
	_doorTile.setTexture(_resHolder->getDoorTexture());

	if (_mapIdentifier == 0){
		sf::Vector2i position(6, 3);
		std::shared_ptr<Item> item(std::make_shared<Weapon>(_resHolder->getAllWeapons()[0]));
		pushItemToMapStorage(position, item);
	}
}
Map::~Map()
{
}

void Map::restoreMap(sf::RenderTexture& renderTexture, sf::RenderTexture& renderTextureDisplayed)
{
	_renderTexture = &renderTexture;
	_renderTextureDisplayed = &renderTextureDisplayed;

	_wallTile.setTexture(_resHolder->getWallTexture());
	_floorTile.setTexture(_resHolder->getTileTexture());
	_doorTile.setTexture(_resHolder->getDoorTexture());


	checkMaxSizes();
	findAllExitPoints();


	for (auto enemy : _enemies){
		enemy->restoreData();
	}
	for (auto enemy : _deadenemies){
		enemy->restoreData();
	}
	drawMap();

}


void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_mapSpriteToDisplay);

}

void Map::updateMap()
{
	_renderTextureDisplayed->clear();
	_renderTextureDisplayed->draw(_mapSprite);


	for (auto enemy : _enemies){
		if (!enemy->checkIfAlive())
			_renderTextureDisplayed->draw(*enemy);
	}
	for (auto item : _itemsOnMap){
		_renderTextureDisplayed->draw(*(item.second));
	}

	for (auto enemy : _enemies){
		if (enemy->checkIfAlive())
			_renderTextureDisplayed->draw(*enemy);
	}

	_renderTextureDisplayed->display();
	_mapSpriteToDisplay.setTexture(_renderTextureDisplayed->getTexture());
}


///////////////////////////
//Check Map Max Dimension//
///////////////////////////

void Map::checkMaxSizes()
{
	_maxDimensionY = _mapTemplate.size();
	_maxDimensionX = 0;
	for (int i = 0; i < _maxDimensionY; i++){
		if (_mapTemplate[i].size() > (unsigned)_maxDimensionX) _maxDimensionX = _mapTemplate[i].size();
	}
}

///////////
//Setters//
///////////

void Map::setMap(std::vector<std::vector<char>> mapTemplate)
{
	_mapTemplate = mapTemplate;
}

///////////
//Getters//
///////////

std::vector<std::vector<char>>& Map::getMap()
{
	return _mapTemplate;
}

unsigned int Map::getMapId()
{
	return _mapIdentifier;
}

sf::Vector2i Map::getNewPosition(unsigned int previousMapID)
{
	for (auto keyValue : _mapExits){
		if (keyValue.second->getMapId() == previousMapID)
			return keyValue.first;
	}
}

std::vector<sf::Vector2i> Map::getExitPoints()
{
	return _exitPoints;
}

std::unordered_map<sf::Vector2i, std::shared_ptr<Map>>& Map::getMapExitPoints()
{
	return _mapExits;
}

unsigned int Map::getNumberOfFreeExits()
{
	return _notPairedExitPoints.size();
}

///////////////
//Map drawing//
///////////////

void Map::setMapLayer(sf::RenderTexture& mapRenderTexture)
{
	mapRenderTexture.display();
	_mapSprite.setTexture(mapRenderTexture.getTexture(), true);
}

void Map::drawMap()
{
	takeEnemiesFromMap();

	_renderTexture->create((static_cast<unsigned int>(__TILE_SIZE_X__ * _maxDimensionX)), (static_cast<unsigned int>(__TILE_SIZE_Y__ * _maxDimensionY)));
	_renderTextureDisplayed->create((static_cast<unsigned int>(__TILE_SIZE_X__ * _maxDimensionX)), (static_cast<unsigned int>(__TILE_SIZE_Y__ * _maxDimensionY)));
	_renderTexture->clear();
	for (int i = 0, len = _mapTemplate.size(); i < len; i++){
		for (int j = 0, len1 = _mapTemplate[i].size(); j < len1; j++){
			switch (_mapTemplate[i][j]){
			//Entrances/exits, call them as you please.//
			case 'E': drawEntry(*_renderTexture, i, j);		break;

			//Walls, as in name.//
			case 'x': drawWall(*_renderTexture, i, j);		break;

			//Floor, as in name.//
			case '.': drawFloor(*_renderTexture, i, j);		break;

			//Whatever happened, will be fully transparent. Unexpected tiles and spacebars will be treated as those.
			//Note that spacebar will be treated as obstacle.
			default: drawEmpty(*_renderTexture, i, j);
			}
		}
		//std::cout << std::endl;
	}

	setMapLayer(*_renderTexture);
	putEnemiesOnMap();
	updateMap();
}
////////////////////
//Draw map texture//
////////////////////

//Wall//
void Map::drawWall(sf::RenderTexture& mapRenderTexture, int y, int x)
{
	_wallTile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	mapRenderTexture.draw(_wallTile);
}

//Floor//
void Map::drawFloor(sf::RenderTexture& mapRenderTexture, int y, int x)
{
	_floorTile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);

	mapRenderTexture.draw(_floorTile);
}

//Entry/Exit. In short: doorway! Or long, lol.//
void Map::drawEntry(sf::RenderTexture& mapRenderTexture, int y, int x)
{
	_wallTile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	mapRenderTexture.draw(_wallTile);

	_doorTile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	mapRenderTexture.draw(_doorTile);
}

//Empty space//
void Map::drawEmpty(sf::RenderTexture& mapRenderTexture, int y, int x)
{
	sf::RectangleShape tile;
	//std::cout << "2";
	tile.setSize(sf::Vector2f(__TILE_SIZE_X__, __TILE_SIZE_Y__));
	tile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	tile.setFillColor(sf::Color::Transparent);
	mapRenderTexture.draw(tile);
}

//decorations//


void Map::drawDecoration(int number, int type)
{
	sf::RectangleShape tile;
	tile.setFillColor(sf::Color::Green);
	switch (type){
	case MAP_DECORATIONS::SMALL_WALL:
		tile.setSize(sf::Vector2f(16.f, 16.f));
		tile.setPosition(_wallDecorationSmall[number]);
		_renderTexture->draw(tile);
		break;

	case MAP_DECORATIONS::LARGE_WALL:
		tile.setSize(sf::Vector2f(32.f, 32.f));
		tile.setPosition(_wallDecorationLarge[number]);
		_renderTexture->draw(tile);
		break;

	case MAP_DECORATIONS::SMALL_FLOOR:
		tile.setSize(sf::Vector2f(16.f, 16.f));
		tile.setPosition(_floorDecorationSmall[number]);
		_renderTexture->draw(tile);
		break;

	case MAP_DECORATIONS::MEDIUM_FLOOR:
		tile.setSize(sf::Vector2f(32.f, 32.f));
		tile.setPosition(_floorDecorationMedium[number]);
		_renderTexture->draw(tile);
		break;

	case MAP_DECORATIONS::LARGE_FLOOR:
		tile.setSize(sf::Vector2f(48.f, 48.f));
		tile.setPosition(_floorDecorationLarge[number]);
		_renderTexture->draw(tile);
		break;


	default: break;
	}
}

void Map::printConsoleMap()
{
	for (int k = 0, len2 = _mapTemplate.size(); k < len2; k++){
		for (int j = 0, len1 = _mapTemplate[k].size(); j < len1; j++){
			std::cout << _mapTemplate[k][j];
		}
		std::cout << std::endl;
	}
}

//////////////////
//Map traversing//
//////////////////

void Map::findAllExitPoints()
{
	for (int i = 0, len = _mapTemplate.size(); i < len; i++)
	{
		for (int j = 0, len2 = _mapTemplate[i].size(); j < len2; j++)
		{
			if (_mapTemplate[i][j] == 'E'){
				sf::Vector2i exitPoint(i, j);
				_exitPoints.push_back(exitPoint);
				_notPairedExitPoints.push_back(exitPoint);
			}
		}
	}
}

void Map::pairMapAndExitPoint(std::shared_ptr<Map> previousMap)
{
	int number = rand() % _notPairedExitPoints.size();
	//std::cout << number << std::endl;
	_mapExits[_notPairedExitPoints[number]] = previousMap;
	_notPairedExitPoints.erase(_notPairedExitPoints.begin() + number);
}

void Map::pairMapAndExitPoint(std::shared_ptr<Map> destinationMap, sf::Vector2i exitPoint)
{
	for (int i = 0, len = _notPairedExitPoints.size(); i < len; i++)
	{
		if (exitPoint == _notPairedExitPoints[i]){
			_mapExits[exitPoint] = destinationMap;
			_notPairedExitPoints.erase(_notPairedExitPoints.begin() + i);
			break;
		}
	}
}

std::shared_ptr<Map> Map::moveToMap(unsigned int previousMapID)
{
	for (auto keyValue : _mapExits){
		if (keyValue.second->getMapId() == previousMapID)
		return keyValue.second;
	}
}


///////////////
//Map enemies//
///////////////


std::vector<std::shared_ptr<Enemy>>& Map::getEnemies()
{
	return _enemies;
}

void Map::increaseRespawnCounter()
{
	_respawn_counter++;
	if (__MAPS_TILL_RESPAWN__ == _respawn_counter){
		_ratings.overral_rating = (int)(_ratings.overral_rating * 1.4f);
		resurrectAndReinforceEnemies();
		_respawn_counter = 0;
	}
}

void Map::resurrectAndReinforceEnemies()
{

	for (auto enemy : _enemies){
		enemy->resurrectAndReinforce(_ratings.overral_rating);
		changeMapTile(__ENEMY_ON_MAP__, enemy->getEnemyPositionOnGrid().x, enemy->getEnemyPositionOnGrid().y);
	}
}


std::shared_ptr<Enemy> Map::getEnemyAtPosition(int posx, int posy)
{
	for (auto enemy : _enemies){
		if (enemy->getEnemyPositionOnGrid() == sf::Vector2i(posx, posy)){
			return enemy;
		}
	}
}

void Map::killOffEnemy(int enemy_id)
{
	for (auto enemy : _enemies){
		if (enemy->getEnemyId() == enemy_id){
			changeMapTile(__ENEMY_CORPSE_ON_MAP__, enemy->getEnemyPositionOnGrid().x, enemy->getEnemyPositionOnGrid().y);
			for (auto aliveEnemy : _enemies){
				if (aliveEnemy->getEnemyPositionOnGrid() == enemy->getEnemyPositionOnGrid() && aliveEnemy->checkIfAlive()){

				}
			}
			updateMap();
			return;
		}
	}
}

void Map::increaseEnemyTicks(int &amount)
{
	for (auto enemy : _enemies){
		enemy->increaseTicks(amount);
	}
}


void Map::moveEnemy(std::shared_ptr<Enemy> &enemy, sf::Vector2i newPos)
{

	sf::Vector2i position = enemy->getEnemyPositionOnGrid();

	//std::cout << "Move Enemy ID " << enemy->getEnemyId() << std::endl;
	//std::cout << "x,y " << position.x << " " << position.y << std::endl;

	changeMapTile(enemy->getTileUnderneathEnemy(), position.x, position.y);

	if (_mapTemplate[newPos.y][newPos.x] != __ENEMY_CORPSE_ON_MAP__ 
		&& _mapTemplate[newPos.y][newPos.x] != __ENEMY_ON_MAP__){
		enemy->setTileUnderneathEnemy(_mapTemplate[newPos.y][newPos.x]);
	}
	else{
		for (auto otherEnemy : _enemies){
			if (otherEnemy->getEnemyPositionOnGrid() == newPos && otherEnemy != enemy){
				enemy->setTileUnderneathEnemy(otherEnemy->getTileUnderneathEnemy());
				break;
			}
		}
	}
	changeMapTile(__ENEMY_ON_MAP__, newPos.x, newPos.y);

	enemy->moveEnemy(newPos);

}


///////////////////////
//Move around entites//
///////////////////////

void Map::changeMapTile(char newTile, int x, int y)
{
	_mapTemplate[y][x] = newTile;

}



///////////////////////////////
//Setting enemies on load map//
///////////////////////////////

void Map::putEnemiesOnMap()
{
	for (auto enemy : _enemies){
		if (enemy->checkIfAlive()){
			changeMapTile(__ENEMY_ON_MAP__, enemy->getEnemyPositionOnGrid().x, enemy->getEnemyPositionOnGrid().y);
		}
		else{
			changeMapTile(__ENEMY_CORPSE_ON_MAP__, enemy->getEnemyPositionOnGrid().x, enemy->getEnemyPositionOnGrid().y);
		}
	}
}

void Map::takeEnemiesFromMap()
{
	for (auto enemy : _enemies){
		changeMapTile(enemy->getTileUnderneathEnemy(), enemy->getEnemyPositionOnGrid().x, enemy->getEnemyPositionOnGrid().y);
	}
}

//////////////////
//Items and drop//
//////////////////


void Map::generateItemAtPosition(sf::Vector2i position, int enemyRating)
{
	//std::shared_ptr<Item> item(std::make_shared<Weapon>(_resHolder->getAllWeapons()[0], _ratings.hero_rating));
	//std::shared_ptr<Item> item(std::make_shared<Armour>(_resHolder->getAllArmours()[0], enemyRating));
	int itemNumber, size;

	std::uniform_int_distribution<int> item_type_rand(0, 5);
	std::uniform_int_distribution<int> percentage_dice(0, 99);
	std::vector<Consumable_struct> regens, stat_increase;
	int number = item_type_rand(_generator);
	switch (number){
	case 2:
	case 5:
		size = _resHolder->getAllArmours().size();
		{
			std::uniform_int_distribution<int> randomize(0, size - 1);
			itemNumber = randomize(_generator);
			std::shared_ptr<Item> item(std::make_shared<Armour>(_resHolder->getAllArmours()[itemNumber], enemyRating));
			pushItemToMapStorage(position, item);
		}
		break;
	case 1:
	case 4:
		for (auto stat : _resHolder->getAllConsumables()){
			if (stat.effect_type == CONSUMABLE_EFFECT::HP_REGEN ||
				stat.effect_type == CONSUMABLE_EFFECT::SP_REGEN ||
				stat.effect_type == CONSUMABLE_EFFECT::REGENERATE_TICK){
				regens.push_back(stat);
			}
			else{
				stat_increase.push_back(stat);
			}
		}
		if (percentage_dice(_generator) >= 80){
			std::uniform_int_distribution<int> randomize(0, stat_increase.size() - 1);
			itemNumber = randomize(_generator);
			std::shared_ptr<Item> item(std::make_shared<Consumable>(stat_increase[itemNumber]));
			pushItemToMapStorage(position, item);
		}
		else{
			std::uniform_int_distribution<int> randomize(0, regens.size() - 1);
			itemNumber = randomize(_generator);
			std::shared_ptr<Item> item(std::make_shared<Consumable>(regens[itemNumber]));
			pushItemToMapStorage(position, item);
		}

		break;
	case 0:
	case 3:
		std::cout << "Here goes weapon, lol" << std::endl;
		size = _resHolder->getAllWeapons().size();
		{
			std::uniform_int_distribution<int> randomize(0, size - 1);
			itemNumber = randomize(_generator);
			std::shared_ptr<Item> item(std::make_shared<Weapon>(_resHolder->getAllWeapons()[itemNumber], enemyRating));
			pushItemToMapStorage(position, item);
		}
		break;
	}


	updateMap();
}

void Map::pushItemToMapStorage(sf::Vector2i position, std::shared_ptr<Item> item)
{
	item->setImagesPosition(sf::Vector2f(position.x * 32.f, position.y * 32.f));
	_itemsOnMap.insert(std::pair < sf::Vector2i, std::shared_ptr<Item>>(position, item));
}

bool Map::checkForItemsAtTile(sf::Vector2i position)
{
	for (auto item : _itemsOnMap){

		if (item.first == position){
			return true;
		}

	}
	
	return false;
}

std::shared_ptr<Item> Map::returnItemAtTile(sf::Vector2i position)
{
	std::shared_ptr<Item> temp;
	std::unordered_multimap<sf::Vector2i, std::shared_ptr<Item>>::iterator it = _itemsOnMap.find(position);
	
	temp = it->second;
	_itemsOnMap.erase(it);

	return temp;
}