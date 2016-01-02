#include "Consumable.h"


Consumable::Consumable()
{

}

Consumable::Consumable(int item_type, Consumable_struct stats)
	:
	Item(item_type), _stats(stats)
{

}

Consumable::Consumable(Consumable_struct stats) : _stats(stats)
{
	if (!_itemTexture.loadFromFile(_stats.img_path));
	switch (_stats.type){
	case CONSUMABLE_TYPE::FOOD_TYPE:
		_itemTexture.loadFromFile(__DEFAULT_FOOD_IMAGE__);
		break;
	case CONSUMABLE_TYPE::PILL_TYPE:
		_itemTexture.loadFromFile(__DEFAULT_PILL_IMAGE__);
		break;
	case CONSUMABLE_TYPE::POTION_TYPE:
		_itemTexture.loadFromFile(__DEFAULT_POTION_IMAGE__);
		break;
	}
	_itemShape.setSize(sf::Vector2f(32.f, 32.f));
	_itemShape.setTexture(&_itemTexture);

	_itemType = ITEM_TYPE::CONSUMABLE;

	//std::cout << "Raw Armour Rating: " << _stats.base_rating << std::endl;
}


Consumable::~Consumable()
{

}


void Consumable::getItemStats()
{
	std::cout << _stats.name << std::endl;
}

Consumable_struct Consumable::getStatsStruct()
{
	return _stats;
}
void Consumable::restoreData()
{
	if (!_itemTexture.loadFromFile(_stats.img_path));
	switch (_stats.type){
	case CONSUMABLE_TYPE::FOOD_TYPE:
		_itemTexture.loadFromFile(__DEFAULT_FOOD_IMAGE__);
		break;
	case CONSUMABLE_TYPE::PILL_TYPE:
		_itemTexture.loadFromFile(__DEFAULT_PILL_IMAGE__);
		break;
	case CONSUMABLE_TYPE::POTION_TYPE:
		_itemTexture.loadFromFile(__DEFAULT_POTION_IMAGE__);
		break;
	}
	_itemShape.setSize(sf::Vector2f(32.f, 32.f));
	_itemShape.setTexture(&_itemTexture);

}