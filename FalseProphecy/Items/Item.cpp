#include "Item.h"


void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_itemShape);
	target.draw(_backgroundShape);
}

void Item::setName()
{
	name = "trolo";
}

std::string Item::getName()
{
	return name;
}