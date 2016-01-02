#include "Armour.h"


Armour::Armour()
{

}

Armour::Armour(int item_type, Armour_struct stats)
	:
	Item(item_type), _stats(stats)
{

}

Armour::Armour(Armour_struct stats) : _stats(stats)
{
	if (!_itemTexture.loadFromFile(_stats.img_path));
		switch (_stats.type){
		case ARMOUR_TYPE::HELMET:
			_itemTexture.loadFromFile(__DEFAULT_HELMET_IMAGE__);
			break;
		case ARMOUR_TYPE::TORSO:
			_itemTexture.loadFromFile(__DEFAULT_CHEST_IMAGE__);
			break;
		case ARMOUR_TYPE::GREAVES:
			_itemTexture.loadFromFile(__DEFAULT_LEGS_IMAGE__);
			break;
		case ARMOUR_TYPE::SHIELD:
			_itemTexture.loadFromFile(__DEFAULT_SHIELD_IMAGE__);
			break;
	}
	_itemShape.setSize(sf::Vector2f(32.f, 32.f));
	_itemShape.setTexture(&_itemTexture);

	_itemType = ITEM_TYPE::ARMOUR;

	//std::cout << "Raw Armour Rating: " << _stats.base_rating << std::endl;
}

Armour::Armour(Armour_struct stats, int hero_rating) : _stats(stats)
{
	if (!_itemTexture.loadFromFile(_stats.img_path));
	switch (_stats.type){
	case ARMOUR_TYPE::HELMET:
		_itemTexture.loadFromFile(__DEFAULT_HELMET_IMAGE__);
		break;
	case ARMOUR_TYPE::TORSO:
		_itemTexture.loadFromFile(__DEFAULT_CHEST_IMAGE__);
		break;
	case ARMOUR_TYPE::GREAVES:
		_itemTexture.loadFromFile(__DEFAULT_LEGS_IMAGE__);
		break;
	case ARMOUR_TYPE::SHIELD:
		_itemTexture.loadFromFile(__DEFAULT_SHIELD_IMAGE__);
		break;
	}
	_itemShape.setSize(sf::Vector2f(32.f, 32.f));
	_itemShape.setTexture(&_itemTexture);

	_itemType = ITEM_TYPE::ARMOUR;

	Calculations::calculateNewStats(_stats, hero_rating);
	//std::cout << "Generated Armour Rating: " << _stats.current_rating << std::endl;
}

Armour::~Armour()
{

}


void Armour::getItemStats()
{
	std::cout << _stats.name << std::endl;
}

Armour_struct Armour::getStatsStruct()
{
	return _stats;
}

void Armour::restoreData()
{
	if (!_itemTexture.loadFromFile(_stats.img_path));
	switch (_stats.type){
	case ARMOUR_TYPE::HELMET:
		_itemTexture.loadFromFile(__DEFAULT_HELMET_IMAGE__);
		break;
	case ARMOUR_TYPE::TORSO:
		_itemTexture.loadFromFile(__DEFAULT_CHEST_IMAGE__);
		break;
	case ARMOUR_TYPE::GREAVES:
		_itemTexture.loadFromFile(__DEFAULT_LEGS_IMAGE__);
		break;
	case ARMOUR_TYPE::SHIELD:
		_itemTexture.loadFromFile(__DEFAULT_SHIELD_IMAGE__);
		break;
	}
	_itemShape.setSize(sf::Vector2f(32.f, 32.f));
	_itemShape.setTexture(&_itemTexture);

}