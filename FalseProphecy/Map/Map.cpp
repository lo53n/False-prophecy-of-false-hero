#include "Map.h"

Map::Map()
{
	_mapTexture.create(800, 600);
	_mapTexture.clear();

}

Map::Map(std::vector<std::vector<char>> mapTemplate) : _mapTemplate(mapTemplate)
{
	_mapTexture.create((unsigned int)(__TILE_SIZE_X__ * _mapTemplate[0].size()), (unsigned int)(__TILE_SIZE_Y__ * _mapTemplate.size()));
	_mapTexture.clear();
}
Map::~Map()
{

}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(_mapSprite);

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

///////////////
//Map drawing//
///////////////

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

			case 'x': drawWall(i, j);		break;
			case 'E': drawEntry(i, j);		break;
			case '.': drawStuff1(i, j);		break;

			default: drawFloor(i, j);
			}
		}
		std::cout << std::endl;
	}
	setMapLayer();
}

void Map::drawWall(int y, int x)
{
	sf::RectangleShape tile;
	std::cout << "1";
	tile.setSize(sf::Vector2f(__TILE_SIZE_X__, __TILE_SIZE_Y__));
	tile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	tile.setFillColor(sf::Color::Blue);
	_mapTexture.draw(tile);
}

void Map::drawFloor(int y, int x)
{
	sf::RectangleShape tile;
	std::cout << "0";
	tile.setSize(sf::Vector2f(__TILE_SIZE_X__, __TILE_SIZE_Y__));
	tile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	tile.setFillColor(sf::Color::Green);
	_mapTexture.draw(tile);
}

void Map::drawStuff1(int y, int x)
{
	sf::RectangleShape tile;
	std::cout << "2";
	tile.setSize(sf::Vector2f(__TILE_SIZE_X__, __TILE_SIZE_Y__));
	tile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	tile.setFillColor(sf::Color::Yellow);
	_mapTexture.draw(tile);
}

void Map::drawEntry(int y, int x)
{
	sf::RectangleShape tile;
	std::cout << "E";
	tile.setSize(sf::Vector2f(__TILE_SIZE_X__, __TILE_SIZE_Y__));
	tile.setPosition(__TILE_SIZE_X__ * x, __TILE_SIZE_Y__ * y);
	tile.setFillColor(sf::Color::Color(122,100,23,255));
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