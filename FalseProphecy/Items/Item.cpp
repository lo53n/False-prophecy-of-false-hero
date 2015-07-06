#include "Item.h"

Item::Item()
{
	_backgroundTexture.loadFromFile(__TILE_IMAGE__);
	_backgroundShape.setPosition(10.f, 10.f);
	_backgroundShape.setSize(sf::Vector2f(32.f, 32.f));
	_backgroundShape.setTexture(&_backgroundTexture);
}


Item::~Item()
{

}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_backgroundShape);
	target.draw(_itemShape);
}