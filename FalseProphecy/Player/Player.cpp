#include "Player.h"

Player::Player()
{
	_playerShape.setSize(sf::Vector2f(__PLAYER_HEIGHT__, __PLAYER_WIDTH__));
	_playerShape.setPosition(0.0f, 0.0f);
	_playerShape.setFillColor(sf::Color::Red);

	/*_playerTexture.create((unsigned int)__PLAYER_WIDTH__, (unsigned int)__PLAYER_HEIGHT__);
	_playerTexture.clear();
	_playerTexture.draw(player);
	_playerTexture.display();*/

	//_playerSprite.setTexture(_playerTexture.getTexture());


	_stats.attack = 5;
	//0 - 1h, 1 - 2h, 2- 2xwield
	_heroWeaponHandle = 1;
	//3 - shield, 4 - unarmed, 5 - sword, 6 - mace , 7 - spear, 8 - axe,
	_heroWeaponType = 5;

	presetProficiences();
}

Player::~Player()
{

}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(_playerShape);

}

///////////
//Getters//
///////////

sf::Vector2f& Player::getPlayerPositionOnMap()
{
	return _positionOnMap;
}
sf::Vector2i& Player::getPlayerPositionOnGrid()
{
	return _positionOnGrid;
}
std::vector<std::shared_ptr<Item>>& Player::getPlayerBackpack()
{
	return _backpack;
}
Hero_Profile& Player::getPlayerStats()
{
	return _stats;
}
std::vector<Ability_Proficiencies> Player::getPlayerProficiences()
{
	return _proficiences;
}
std::shared_ptr<Weapon> Player::getPlayerWeapon()
{
	return _mainHand;
}
std::shared_ptr<Armour> Player::getPlayerArmour(int type)
{
	switch (type){
	case ARMOUR_TYPE::SHIELD: return _offHand;
	case ARMOUR_TYPE::HELMET: return _head;
	case ARMOUR_TYPE::TORSO: return _torso;
	case ARMOUR_TYPE::GREAVES: return _legs;
	}
}
///////////
//Setters//
///////////

void Player::setPlayerPositionOnMap(sf::Vector2f newPositionOnMap)
{
	_positionOnMap = newPositionOnMap;
	_positionOnGrid = (sf::Vector2i)(_positionOnMap / __PLAYER_HEIGHT__);
	_playerShape.setPosition(_positionOnMap);
}

void Player::setPlayerPositionOnGrid(sf::Vector2i newPositionOnGrid)
{
	_positionOnGrid = newPositionOnGrid;
	_positionOnMap = (sf::Vector2f)(_positionOnGrid * (int)__PLAYER_HEIGHT__);
	_playerShape.setPosition(_positionOnMap);
}
///////////////////
//Player movement//
///////////////////

void Player::movePlayer(int direction)
{
	sf::Vector2i movement;

	switch (direction){
	case 0:
		movement = sf::Vector2i(0, -1);
		break;
	case 1:
		movement = sf::Vector2i(1, 0);
		break;
	case 2:
		movement = sf::Vector2i(0, 1);
		break;
	case 3:
		movement = sf::Vector2i(-1, 0);
		break;

	}
	_positionOnGrid += movement;
	_positionOnMap += (sf::Vector2f)(movement * (int)__PLAYER_HEIGHT__);
	_playerShape.setPosition(_positionOnMap);
	//std::cout << "My position on grid: " << _positionOnGrid.x << " " << _positionOnGrid.y << std::endl;
	//std::cout << "My position on map: " << _positionOnMap.x << " " << _positionOnMap.y << std::endl;
}

//////////////////
//Item managment//
//////////////////

void Player::putItemInBackpack(std::shared_ptr<Item> item)
{
	_backpack.push_back(item);
}

std::shared_ptr<Item> Player::dropSelectedItem(int itemNumber)
{
	std::shared_ptr<Item> temp = _backpack.at(itemNumber);
	_backpack.erase(_backpack.begin() + itemNumber);
	return temp;
}

void Player::equipItem(std::shared_ptr<Weapon> item)
{

	std::shared_ptr<Item> temp = nullptr;

	if (_mainHand != nullptr) temp = _mainHand;

	_mainHand = item;
	std::cout << "Equipped weapon " << _mainHand->getStatsStruct().name << std::endl;

	if (temp != nullptr){
		for (int i = 0, len = _backpack.size(); i < len; i++){
			if (std::dynamic_pointer_cast<Item>(item) == _backpack[i]){
				_backpack[i] = std::dynamic_pointer_cast<Weapon>(temp);
				break;
			}
		}
	}
	else{
		for (int i = 0, len = _backpack.size(); i < len; i++){
			if (std::dynamic_pointer_cast<Item>(item) == _backpack[i]){
				_backpack.erase(_backpack.begin() + i);
				break;
			}
		}
	}
}
void Player::equipItem(std::shared_ptr<Armour> item)
{
	std::shared_ptr<Item> temp = nullptr;
	switch (item->getStatsStruct().type){
	case ARMOUR_TYPE::TORSO:
		if (_torso != nullptr) temp = _torso;
		_torso = item;
		std::cout << "Equipped torso " << _torso->getStatsStruct().name << std::endl;
		break;
	case ARMOUR_TYPE::HELMET:
		if (_head != nullptr) temp = _head;
		_head = item;
		std::cout << "Equipped head " << _head->getStatsStruct().name << std::endl;
		break;
	case ARMOUR_TYPE::GREAVES:
		if (_legs != nullptr) temp = _legs;
		_legs = item;
		std::cout << "Equipped legs " << _legs->getStatsStruct().name << std::endl;
		break;
	case ARMOUR_TYPE::SHIELD:
		if (_offHand != nullptr) temp = _offHand;
		_offHand = item;
		std::cout << "Equipped shield " << _offHand->getStatsStruct().name << std::endl;
	}

	if (temp != nullptr){
		for (int i = 0, len = _backpack.size(); i < len; i++){
			if (std::dynamic_pointer_cast<Item>(item) == _backpack[i]){
				_backpack[i] = std::dynamic_pointer_cast<Armour>(temp);
				break;
			}
		}
	}
	else{
		for (int i = 0, len = _backpack.size(); i < len; i++){
			if (std::dynamic_pointer_cast<Item>(item) == _backpack[i]){
				_backpack.erase(_backpack.begin() + i);
				break;
			}
		}
	}
}

///////////
//Battle!//
///////////

int Player::calculateDamage()
{
	int dmg;
	
	dmg = _stats.attack;

	if(!isUnarmed) increaseProficiency(_heroWeaponHandle, 100);
	increaseProficiency(_heroWeaponType, 100);
	if (isUnarmed){
		dmg = (int)(dmg * _proficiences[HERO_ABILITIES_NUMBER::UNARMED_PROFICIENCY].effectiveness);
	}
	else{
		dmg = (int)(dmg * (_proficiences[_heroWeaponHandle].effectiveness + _proficiences[_heroWeaponType].effectiveness + 1));
	}
	
	//std::cout << dmg << std::endl;

	return dmg;
}

////////////////
//Proficiences//
////////////////
void Player::presetProficiences()
{
	for (int i = 0; i < 14; i++){
		Ability_Proficiencies ability;
		ability.id = i;
		ability.level = 0;
		ability.effectiveness = 0.f;

		if (i < 2)	ability.experience_needed = __BASE_PROFICIENCY_HANDLE_EXP__;
		else if (i > 8) ability.experience_needed = __BASE_PROFICIENCY_BODY_EXP__;
		else ability.experience_needed = __BASE_PROFICIENCY_WEAPON_EXP__;

		ability.experience = 0;
		if (i == 0) ability.name = "Onehanded";
		else if (i == 1) ability.name = "Twohanded";
		else if (i == 2) ability.name = "Dualwield";
		else if (i == 3) ability.name = "Shield";
		else if (i == 4) ability.name = "Unarmed";
		else if (i == 5) ability.name = "Sword";
		else if (i == 6) ability.name = "Mace";
		else if (i == 7) ability.name = "Spear";
		else if (i == 8) ability.name = "Axe";
		else if (i == 9) ability.name = "Magic";
		else if (i == 10) ability.name = "Defence";
		else if (i == 11) ability.name = "Body";
		else if (i == 12) ability.name = "Pain";
		else ability.name = "Dodge";

		_proficiences.push_back(ability);
	}
}

void Player::increaseProficiency(int id, int amount)
{
	_proficiences[id].experience += amount;
	if (_proficiences[id].experience >= _proficiences[id].experience_needed){
		_proficiences[id].level++;
		_proficiences[id].experience -= _proficiences[id].experience_needed; 

		if (id < 2)	_proficiences[id].experience_needed = (int)(__BASE_PROFICIENCY_HANDLE_EXP__ * pow(__PROFICIENCY_LVL_INCREASE__, _proficiences[id].level));
		else if (id > 8) _proficiences[id].experience_needed = (int)(__BASE_PROFICIENCY_BODY_EXP__ * pow(__PROFICIENCY_LVL_INCREASE__, _proficiences[id].level));
		else _proficiences[id].experience_needed = (int)(__BASE_PROFICIENCY_WEAPON_EXP__ * pow(__PROFICIENCY_LVL_INCREASE__, _proficiences[id].level));

		calculateProficientyEffectivness(id);

		std::cout << _proficiences[id].name << " lvl up to " << _proficiences[id].level << " eff: " << _proficiences[id].effectiveness << std::endl;
	}
}

void Player::calculateProficientyEffectivness(int id)
{
	//handle
	if (id < 3){
		for (int i = 1; i < _proficiences[id].level; i++){
			_proficiences[id].effectiveness += (__PROFICIENCY_HANDLE_EFFICIENCY__ * (1 + (float)(_proficiences[id].level) / 100));
		}
	}
	//weapon & magic
	if (id >= 3 && id < 10){
		//unarmed
		if (id == HERO_ABILITIES_NUMBER::UNARMED_PROFICIENCY){
			for (int i = 1; i < _proficiences[id].level; i++){
				_proficiences[id].effectiveness += (__PROFICIENCY_UNARMED_EFFICIENCY__ * (1 + (float)(_proficiences[id].level) / 100));
			}
		}
		//rest
		else{
			for (int i = 1; i < _proficiences[id].level; i++){
				_proficiences[id].effectiveness += (__PROFICIENCY_WEAPON_EFFICIENCY__ * (1 + (float)(_proficiences[id].level) / 100));
			}
		}
	}
	//body 
	if (id >= 10){
		switch (id){
			//defence
		case HERO_ABILITIES_NUMBER::DEFENCE_PROFICIENCY:
			for (int i = 1; i < _proficiences[id].level; i++){
				_proficiences[id].effectiveness += (__PROFICIENCY_DEFENCE_EFFICIENCY__ * (1 + (float)(_proficiences[id].level) / 100));
			}
			break;
			//body
		case HERO_ABILITIES_NUMBER::BODY_ENDURANCE:
			for (int i = 1; i < _proficiences[id].level; i++){
				_proficiences[id].effectiveness += (__PROFICIENCY_BODY_EFFICIENCY__ * (1 + (float)(_proficiences[id].level) / 100));
			}
			break;
			//pain
		case HERO_ABILITIES_NUMBER::PAIN_ENDURANCE:
			for (int i = 1; i < _proficiences[id].level; i++){
				_proficiences[id].effectiveness += (__PROFICIENCY_PAIN_EFFICIENCY__ * (1 + (float)(_proficiences[id].level) / 100));
			}
			break;
			//dodge
		case HERO_ABILITIES_NUMBER::DODGING_PROFICIENCY:
			for (int i = 1; i < _proficiences[id].level; i++){
				_proficiences[id].effectiveness += (__PROFICIENCY_DODGE_EFFICIENCY__ * (1 + (float)(_proficiences[id].level) / 100));
			}
			break;
		}
	}
}
