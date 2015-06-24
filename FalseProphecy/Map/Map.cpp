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
}
Map::~Map()
{
	std::cout << this << std::endl;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(_mapSprite);

}

void Map::clearMap()
{
	//STOP USING RENDER TEXTURE IN EVERY MAP. Figure way out, moron.
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

void Map::drawMap(sf::RenderTexture& mapRenderTexture)
{
	mapRenderTexture.create((unsigned int)(__TILE_SIZE_X__ * _maxDimensionX), (unsigned int)(__TILE_SIZE_Y__ * _maxDimensionY));
	mapRenderTexture.clear();
	for (int i = 0, len = _mapTemplate.size(); i < len; i++){
		for (int j = 0, len1 = _mapTemplate[i].size(); j < len1; j++){
			switch (_mapTemplate[i][j]){
			//Entrances/exits, call them as you please.//
			case 'E': drawEntry(mapRenderTexture, i, j);		break;

			//Walls, as in name.//
			case 'x': drawWall(mapRenderTexture, i, j);		break;

			//Floor, as in name.//
			case '.': drawFloor(mapRenderTexture, i, j);		break;

			//Whatever happened, will be fully transparent. Unexpected tiles and spacebars will be treated as those.
			//Note that spacebar will be treated as obstacle.
			default: drawEmpty(mapRenderTexture, i, j);
			}
		}
		//std::cout << std::endl;
	}
	setMapLayer(mapRenderTexture);
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
	std::cout << number << std::endl;
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