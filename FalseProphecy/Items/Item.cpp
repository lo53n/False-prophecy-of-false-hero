#include "Item.h"

Item::Item()
{
	/*_backgroundTexture.loadFromFile(__TILE_IMAGE__);
	_backgroundShape.setSize(sf::Vector2f(32.f, 32.f));
	_backgroundShape.setTexture(&_backgroundTexture);
	_isBackgroundVisible = false;*/
	_isItemVisible = false;
}

Item::Item(int item_type)
	:
	_itemType(item_type)
{
	_isItemVisible = false;
}


Item::~Item()
{

}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//target.draw(_backgroundShape);
	target.draw(_itemShape);
}



void Item::setImagesPosition(sf::Vector2f newPosition)
{
	_itemShape.setPosition(newPosition);
	//_backgroundShape.setPosition(newPosition);
}

void Item::getItemStats()
{
	//std::cout << "lol" << std::endl;
}

int Item::getItemType()
{
	return _itemType;
}
void Item::restoreData()
{

}