#include "Map.h"

Map::Map()
{
	//_mapTexture.create(800, 600);
	//_mapTexture.clear();

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
}
Map::~Map()
{
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
	_renderTexture->create((unsigned int)(__TILE_SIZE_X__ * _maxDimensionX), (unsigned int)(__TILE_SIZE_Y__ * _maxDimensionY));
	_renderTextureDisplayed->create((unsigned int)(__TILE_SIZE_X__ * _maxDimensionX), (unsigned int)(__TILE_SIZE_Y__ * _maxDimensionY));
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
	sf::RectangleShape tile;
	//std::cout << "1";
	tile.setSize(sf::Vector2f(__TILE_SIZE_X__, __TILE_SIZE_Y__));
	tile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	tile.setFillColor(sf::Color::Blue);
	mapRenderTexture.draw(tile);
}

//Floor//
void Map::drawFloor(sf::RenderTexture& mapRenderTexture, int y, int x)
{
	sf::RectangleShape tile;
	//std::cout << "0";
	tile.setSize(sf::Vector2f(__TILE_SIZE_X__, __TILE_SIZE_Y__));
	tile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	tile.setFillColor(sf::Color::Yellow);
	mapRenderTexture.draw(tile);
}

//Entry/Exit. In short: doorway! Or long, lol.//
void Map::drawEntry(sf::RenderTexture& mapRenderTexture, int y, int x)
{
	sf::RectangleShape tile;
	//std::cout << "E";
	tile.setSize(sf::Vector2f(__TILE_SIZE_X__, __TILE_SIZE_Y__));
	tile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	tile.setFillColor(sf::Color::Color(122,100,23,255));
	mapRenderTexture.draw(tile);
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
		_ratings.overral_rating = (int)(_ratings.overral_rating * 1.2f);
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
			updateMap();
			return;
		}
	}
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
	std::shared_ptr<Item> item(std::make_shared<Armour>(_resHolder->getAllArmours()[0], enemyRating));
	pushItemToMapStorage(position, item);
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