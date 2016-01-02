#include "Weapon.h"


Weapon::Weapon()
{

}

Weapon::Weapon(int item_type, Weapon_struct stats)
	:
	Item(item_type), _stats(stats)
{

}


Weapon::Weapon(Weapon_struct stats) : _stats(stats)
{
	if(!_itemTexture.loadFromFile(_stats.img_path))
		switch (_stats.type){
		case WEAPON_TYPE::SWORD:
			_itemTexture.loadFromFile(__DEFAULT_SWORD_IMAGE__);
			break;
		case WEAPON_TYPE::AXE:
			_itemTexture.loadFromFile(__DEFAULT_AXE_IMAGE__);
			break;
		case WEAPON_TYPE::MACE:
			_itemTexture.loadFromFile(__DEFAULT_MACE_IMAGE__);
			break;
		case WEAPON_TYPE::SPEAR:
			_itemTexture.loadFromFile(__DEFAULT_SPEAR_IMAGE__);
			break;
	}
	_itemShape.setSize(sf::Vector2f(32.f, 32.f));
	_itemShape.setTexture(&_itemTexture);

	_itemType = ITEM_TYPE::WEAPON;


//	std::cout << "Raw Weapon Rating: " << _stats.base_rating << std::endl;
}

Weapon::Weapon(Weapon_struct stats, int hero_rating) : _stats(stats)
{
	if (!_itemTexture.loadFromFile(_stats.img_path))
		switch (_stats.type){
		case WEAPON_TYPE::SWORD:
			_itemTexture.loadFromFile(__DEFAULT_SWORD_IMAGE__);
			break;
		case WEAPON_TYPE::AXE:
			_itemTexture.loadFromFile(__DEFAULT_AXE_IMAGE__);
			break;
		case WEAPON_TYPE::MACE:
			_itemTexture.loadFromFile(__DEFAULT_MACE_IMAGE__);
			break;
		case WEAPON_TYPE::SPEAR:
			_itemTexture.loadFromFile(__DEFAULT_SPEAR_IMAGE__);
			break;
	}
	_itemShape.setSize(sf::Vector2f(32.f, 32.f));
	_itemShape.setTexture(&_itemTexture);

	_itemType = ITEM_TYPE::WEAPON;


	Calculations::calculateNewStats(_stats, hero_rating);
//	std::cout << "Generated Weapon Rating: " << _stats.current_rating << std::endl;

}


Weapon::~Weapon()
{

}

void Weapon::getItemStats()
{
	std::cout << _stats.name << std::endl;
}

Weapon_struct Weapon::getStatsStruct()
{
	return _stats;
}

void Weapon::restoreData()
{
	if (!_itemTexture.loadFromFile(_stats.img_path))
		switch (_stats.type){
		case WEAPON_TYPE::SWORD:
			_itemTexture.loadFromFile(__DEFAULT_SWORD_IMAGE__);
			break;
		case WEAPON_TYPE::AXE:
			_itemTexture.loadFromFile(__DEFAULT_AXE_IMAGE__);
			break;
		case WEAPON_TYPE::MACE:
			_itemTexture.loadFromFile(__DEFAULT_MACE_IMAGE__);
			break;
		case WEAPON_TYPE::SPEAR:
			_itemTexture.loadFromFile(__DEFAULT_SPEAR_IMAGE__);
			break;
	}
	_itemShape.setSize(sf::Vector2f(32.f, 32.f));
	_itemShape.setTexture(&_itemTexture);

}