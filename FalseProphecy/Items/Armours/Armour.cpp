#include "Armour.h"


Armour::Armour()
{

}

Armour::Armour(Armour_struct stats) : _stats(stats)
{
	if (!_itemTexture.loadFromFile(_stats.img_path));
		/*switch (_stats.type){
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
	}*/
	_itemShape.setSize(sf::Vector2f(32.f, 32.f));
	_itemShape.setTexture(&_itemTexture);

	_itemType = ITEM_TYPE::ARMOUR;
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