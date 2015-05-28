#include "Map.h"

Map::Map()
{
	//_mapTexture.create(800, 600);
	//_mapTexture.clear();

}

Map::Map(std::vector<std::vector<char>> mapTemplate, unsigned int mapID) : _mapTemplate(mapTemplate), _mapIdentifier(mapID)
{
	checkMaxSizes(); 
	findAllExitPoints();
	_mapTexture.create((unsigned int)(__TILE_SIZE_X__ * _maxDimensionX), (unsigned int)(__TILE_SIZE_Y__ * _maxDimensionY));
	_mapTexture.clear();
}
Map::~Map()
{
	std::cout << this << std::endl;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(_mapSprite);

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
std::unordered_map<sf::Vector2i, std::shared_ptr<Map>>& Map::getMapExitPoints()
{
	return _mapExits;
}

///////////////
//Map drawing//
///////////////

void Map::clearMap()
{
	_mapTexture.clear();

}

void Map::setMapLayer()
{
	_mapTexture.display();
	_mapSprite.setTexture(_mapTexture.getTexture());
}

void Map::drawMap()
{
	_mapTexture.clear();
	for (int i = 0, len = _mapTemplate.size(); i < len; i++){
		for (int j = 0, len1 = _mapTemplate[i].size(); j < len1; j++){
			switch (_mapTemplate[i][j]){
			//Entrances. Clockwise, where 0 is north and 3 is west//
			case 'E': drawEntry(i, j);		break;

			//Walls, as in name.//
			case 'x': drawWall(i, j);		break;

			//Floor, as in name.//
			case '.': drawFloor(i, j);		break;

			//Whatever happened, will be fully transparent. Unexpected tiles and spacebars will be treated as those.
			//Note that spacebar will be treated as obstacle.
			default: drawEmpty(i, j);
			}
		}
		//std::cout << std::endl;
	}
	setMapLayer();
}
////////////////////
//Draw map texture//
////////////////////

//Wall//
void Map::drawWall(int y, int x)
{
	sf::RectangleShape tile;
	//std::cout << "1";
	tile.setSize(sf::Vector2f(__TILE_SIZE_X__, __TILE_SIZE_Y__));
	tile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	tile.setFillColor(sf::Color::Blue);
	_mapTexture.draw(tile);
}

//Floor//
void Map::drawFloor(int y, int x)
{
	sf::RectangleShape tile;
	//std::cout << "0";
	tile.setSize(sf::Vector2f(__TILE_SIZE_X__, __TILE_SIZE_Y__));
	tile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	tile.setFillColor(sf::Color::Yellow);
	_mapTexture.draw(tile);
}

//Entry/Exit. In short: doorway! Or long, lol.//
void Map::drawEntry(int y, int x)
{
	sf::RectangleShape tile;
	//std::cout << "E";
	tile.setSize(sf::Vector2f(__TILE_SIZE_X__, __TILE_SIZE_Y__));
	tile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	tile.setFillColor(sf::Color::Color(122,100,23,255));
	_mapTexture.draw(tile);
}

//Empty space//
void Map::drawEmpty(int y, int x)
{
	sf::RectangleShape tile;
	//std::cout << "2";
	tile.setSize(sf::Vector2f(__TILE_SIZE_X__, __TILE_SIZE_Y__));
	tile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	tile.setFillColor(sf::Color::Transparent);
	_mapTexture.draw(tile);
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
	for (int i = 0, len = _exitPoints.size(); i < len; i++){
		std::cout << "Exit point found at: (y, x): "<<_exitPoints[i].x << " " << _exitPoints[i].y << std::endl;
	}
}

void Map::pairMapAndExitPoint(std::shared_ptr<Map> previousMap)
{
	int number = rand() % _notPairedExitPoints.size();
	//sf::Vector2f* ptr = _notPairedExitPoints[number];
	//_pairedExitPoints.insert(std::pair<int, sf::Vector2f*>(_pairedExitPoints.size() + 1 ,*_notPairedExitPoints[number]));
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

void Map::setMapExitPoint(int mapDirection, std::shared_ptr<Map> previousMap)
{
	switch (mapDirection){
	case 0:
		_northExit = previousMap;
		break;
	case 1:
		_eastExit = previousMap;
		break;
	case 2:
		_southExit = previousMap;
		break;
	case 3:
		_westExit = previousMap;
		break;
	}
}

bool Map::checkMapExitPoint(int exit)
{
	switch (exit){
	case 0:
		if(_northExit == nullptr) return true;
		else false;
		break;
	case 1:
		if (_eastExit == nullptr) return true;
		else false;
		break;
	case 2:
		if (_southExit == nullptr) return true;
		else false;
		break;
	case 3:
		if (_westExit == nullptr) return true;
		else false;
		break;
	}
}

//std::shared_ptr<Map> Map::moveToMap(int exitTile)
//{
//	switch (exitTile){
//	case 0:
//		return _northExit;
//		break;
//	case 1:
//		return _eastExit;
//		break;
//	case 2:
//		return _southExit;
//		break;
//	case 3:
//		return _westExit;
//		break;
//	}
//
//}


std::shared_ptr<Map> Map::moveToMap(unsigned int previousMapID)
{
	for (auto keyValue : _mapExits){
		if (keyValue.second->getMapId() == previousMapID)
		return keyValue.second;
	}
}