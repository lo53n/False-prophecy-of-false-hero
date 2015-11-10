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

	_backpack.reserve(__BACKPACK_CAPACITY__);

	presetHeroStructure();
	presetProficiences();


}

Player::~Player()
{

}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(_playerShape);

}

/////////////////////
//Preset structures//
/////////////////////

void Player::presetHeroStructure()
{
	_stats.level = 1;

	_stats.exp = 0;
	_stats.max_exp = __BASE_EXPERIENCE__;


	_stats.strenght = 10;
	_stats.endurance = 10;
	_stats.dexterity = 10;
	_stats.agility = 10;
	_stats.intelligence = 10;
	_stats.willpower = 10;

	_stats.defence = 0;

	_stats.max_block = 75;
	_stats.block = 0;

	_stats.max_dodge = 90;
	_stats.dodge = 0;

	_stats.min_speed = 20;
	_stats.speed = 100;

	_stats.luck = 10;

	//0 - 1h, 1 - 2h, 2- 2xwield
	_heroWeaponHandle = -1;
	//3 - shield, 4 - unarmed, 5 - sword, 6 - mace , 7 - spear, 8 - axe,
	_heroWeaponType = WEAPON_TYPE::UNARMED;

	int _heroOffHandType = -1;
	int _heroOffhandClass = ARMOUR_CLASS::EMPTYHAND;

	int _heroHelmetType = -1;
	int _heroHelmetClass = ARMOUR_CLASS::NAKED;

	int _heroTorsoType = -1;
	int _heroTorsoClass = ARMOUR_CLASS::NAKED;

	int _heroLegsType = -1;
	int _heroLegsClass = ARMOUR_CLASS::NAKED;

	refreshStatistics();

}

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

		//After changing this, remember to change it in StatusWindow.cpp in func setProgressBars() & refreshProficiences()
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

int Player::getPlayerAbilityValue(int type)
{
	switch (type){
	case HERO_STATS_NAMES::STRENGTH: return _stats.strenght;
	case HERO_STATS_NAMES::ENDURANCE: return _stats.endurance;
	case HERO_STATS_NAMES::DEXTERITY: return _stats.dexterity;
	case HERO_STATS_NAMES::AGILITY: return _stats.agility;
	case HERO_STATS_NAMES::INTELLIGENCE: return _stats.intelligence;
	case HERO_STATS_NAMES::WILLPOWER: return _stats.willpower;
	}
}

int Player::getPlayerWeaponHandle()
{
	return _heroWeaponHandle;
}

int Player::getPlayerWeaponType()
{
	return _heroWeaponType;
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

void Player::setGameWindowInterface(std::shared_ptr<GameWindowInterface> GWI)
{
	_gwi = GWI;
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

std::shared_ptr<Item> Player::dropSelectedItem(int itemNumber, bool inBag)
{
	std::shared_ptr<Item> temp;
	if (inBag){
		temp = _backpack.at(itemNumber);
		_backpack.erase(_backpack.begin() + itemNumber);
		return temp;
	}
	else{
		switch (itemNumber){
		case 0: 
			temp = _mainHand;
			_mainHand = nullptr;
			setAsUnarmed();
			break;
		case 1:
			temp = _offHand;
			_offHand = nullptr;
			break;
		case 2:
			temp = _head;
			_head = nullptr;
			break;
		case 3:
			temp = _torso;
			_torso = nullptr;
			break;
		case 4:
			temp = _legs;
			_legs = nullptr;
			break;
		}

		refreshStatistics();
		return temp;
	}
}

void Player::equipItem(std::shared_ptr<Weapon> item)
{

	std::shared_ptr<Item> temp = nullptr;

	if (_mainHand != nullptr) temp = _mainHand;

	_mainHand = item;

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
	Weapon_struct stats = _mainHand->getStatsStruct();


	_heroWeaponHandle = _mainHand->getStatsStruct().weapon_handle;
	_heroWeaponType = _mainHand->getStatsStruct().type;
	_stats.min_dmg = stats.min_dmg;
	_stats.max_dmg = stats.max_dmg;

	int add_dmg;
	//calculate multipliers//
	add_dmg = (int)((float)(getPlayerAbilityValue(stats.primary_multiplier) * stats.primary_multiplier_value) / 100);
	if (stats.secondary_multiplier > -1){
		add_dmg += (int)((float)(getPlayerAbilityValue(stats.secondary_multiplier) * stats.secondary_multiplier_value) / 100);
	}

	_stats.min_dmg += add_dmg;
	_stats.max_dmg += add_dmg;


}

void Player::equipItem(std::shared_ptr<Armour> item)
{
	Armour_struct stats;
	std::shared_ptr<Item> temp = nullptr;
	switch (item->getStatsStruct().type){
	case ARMOUR_TYPE::TORSO:
		if (_torso != nullptr) {
			temp = _torso;
			stats = std::dynamic_pointer_cast<Armour>(temp)->getStatsStruct();

			switch (_heroTorsoClass){
			case ARMOUR_CLASS::CLOTH:
				_stats.speed += stats.speed;
				_stats.dodge -= stats.dodge;
				break;

			case ARMOUR_CLASS::LEATHER:
				_stats.speed -= stats.speed;
				_stats.defence -= stats.defence;
				_stats.dodge -= stats.dodge;
				break;

			case ARMOUR_CLASS::METAL:
				_stats.speed -= stats.speed;
				_stats.defence -= stats.defence;
				break;
			}

			_heroTorsoClass = ARMOUR_CLASS::NAKED;

		}

		_torso = item;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();
		_heroTorsoClass = stats.armour_class;

		switch (_heroTorsoClass){

		case ARMOUR_CLASS::CLOTH:
			_stats.speed -= stats.speed;
			_stats.dodge += stats.dodge;
			break;

		case ARMOUR_CLASS::LEATHER:
			_stats.speed += stats.speed;
			_stats.defence += stats.defence;
			_stats.dodge += stats.dodge;
			break;

		case ARMOUR_CLASS::METAL:
			_stats.speed += stats.speed;
			_stats.defence += stats.defence;
			break;
		}
		break;
	case ARMOUR_TYPE::HELMET:
		if (_head != nullptr) {
			temp = _head;
			stats = std::dynamic_pointer_cast<Armour>(temp)->getStatsStruct();

			switch (_heroHelmetClass){
			case ARMOUR_CLASS::CLOTH:
				_stats.speed += stats.speed;
				_stats.dodge -= stats.dodge;
				break;

			case ARMOUR_CLASS::LEATHER:
				_stats.speed -= stats.speed;
				_stats.defence -= stats.defence;
				_stats.dodge -= stats.dodge;
				break;

			case ARMOUR_CLASS::METAL:
				_stats.speed -= stats.speed;
				_stats.defence -= stats.defence;
				break;
			}

			_heroHelmetClass = ARMOUR_CLASS::NAKED;

		}
		_head = item;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();
		_heroHelmetClass = stats.armour_class;

		switch (_heroHelmetClass){

		case ARMOUR_CLASS::CLOTH:
			_stats.speed -= stats.speed;
			_stats.dodge += stats.dodge;
			break;

		case ARMOUR_CLASS::LEATHER:
			_stats.speed += stats.speed;
			_stats.defence += stats.defence;
			_stats.dodge += stats.dodge;
			break;

		case ARMOUR_CLASS::METAL:
			_stats.speed += stats.speed;
			_stats.defence += stats.defence;
			break;
		}
		break;
	case ARMOUR_TYPE::GREAVES:
		if (_legs != nullptr) {
			temp = _legs;
			stats = std::dynamic_pointer_cast<Armour>(temp)->getStatsStruct();


			switch (_heroLegsClass){
			case ARMOUR_CLASS::CLOTH:
				_stats.speed += stats.speed;
				_stats.dodge -= stats.dodge;
				break;

			case ARMOUR_CLASS::LEATHER:
				_stats.speed -= stats.speed;
				_stats.defence -= stats.defence;
				_stats.dodge -= stats.dodge;
				break;

			case ARMOUR_CLASS::METAL:
				_stats.speed -= stats.speed;
				_stats.defence -= stats.defence;
				break;
			}

			_heroLegsClass = ARMOUR_CLASS::NAKED;
		}
		_legs = item;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();
		_heroLegsClass = stats.armour_class;

		switch (_heroLegsClass){

		case ARMOUR_CLASS::CLOTH:
			_stats.speed -= stats.speed;
			_stats.dodge += stats.dodge;
			break;

		case ARMOUR_CLASS::LEATHER:
			_stats.speed += stats.speed;
			_stats.defence += stats.defence;
			_stats.dodge += stats.dodge;
			break;

		case ARMOUR_CLASS::METAL:
			_stats.speed += stats.speed;
			_stats.defence += stats.defence;
			break;
		}
		break;
	case ARMOUR_TYPE::SHIELD:
		if (_offHand != nullptr) {
			temp = _offHand;

		}
		_offHand = item;
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

void Player::unequipItem(int slot)
{
	Armour_struct stats;
	std::shared_ptr<Item> item = nullptr;

	switch (slot){

	case 0:
		item = _mainHand;
		_mainHand = nullptr;
		//Set as unarmed//
		setAsUnarmed();
			break;

	case 1:
		item = _offHand;
		_offHand = nullptr;
			break;

	case 2:
		item = _head;
		_head = nullptr;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();

		switch (_heroHelmetClass){
		case ARMOUR_CLASS::CLOTH:
			_stats.speed += stats.speed;
			_stats.dodge -= stats.dodge;
			break;

		case ARMOUR_CLASS::LEATHER:
			_stats.speed -= stats.speed;
			_stats.defence -= stats.defence;
			_stats.dodge -= stats.dodge;
			break;

		case ARMOUR_CLASS::METAL:
			_stats.speed -= stats.speed;
			_stats.defence -= stats.defence;
			break;
		}

		_heroHelmetClass = ARMOUR_CLASS::NAKED;

		break;

	case 3:
		item = _torso;
		_torso = nullptr;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();

		switch (_heroTorsoClass){
		case ARMOUR_CLASS::CLOTH:
			_stats.speed += stats.speed;
			_stats.dodge -= stats.dodge;
			break;

		case ARMOUR_CLASS::LEATHER:
			_stats.speed -= stats.speed;
			_stats.defence -= stats.defence;
			_stats.dodge -= stats.dodge;
			break;

		case ARMOUR_CLASS::METAL:
			_stats.speed -= stats.speed;
			_stats.defence -= stats.defence;
			break;
		}

		_heroTorsoClass = ARMOUR_CLASS::NAKED;
		break;

	case 4:
		item = _legs;
		_legs = nullptr;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();

		switch (_heroLegsClass){
		case ARMOUR_CLASS::CLOTH:
			_stats.speed += stats.speed;
			_stats.dodge -= stats.dodge;
			break;

		case ARMOUR_CLASS::LEATHER:
			_stats.speed -= stats.speed;
			_stats.defence -= stats.defence;
			_stats.dodge -= stats.dodge;
			break;

		case ARMOUR_CLASS::METAL:
			_stats.speed -= stats.speed;
			_stats.defence -= stats.defence;
			break;
		}

		_heroLegsClass = ARMOUR_CLASS::NAKED;
		break;

	}

	if(item != nullptr) putItemInBackpack(item);


}

void Player::setAsUnarmed()
{
	_heroWeaponType = WEAPON_TYPE::UNARMED;
	_heroWeaponHandle = -1;
	refreshStatistics();
}

///////////
//Battle!//
///////////

int Player::calculateDamage()
{
	int dmg;
	
	dmg = rand() % (_stats.max_dmg - _stats.min_dmg) + _stats.min_dmg;


	//increase weapon proficienty after attack//
	if(_heroWeaponHandle != -1) increaseProficiency(_heroWeaponHandle, 100);
	increaseProficiency(_heroWeaponType, 100);

	//calculate damage for weapon type based on prificiences
	if (_heroWeaponHandle == -1){
		dmg = (int)(dmg * _proficiences[HERO_ABILITIES_NUMBER::UNARMED_PROFICIENCY].effectiveness);
	}
	else{
		dmg = (int)(dmg * (_proficiences[_heroWeaponHandle].effectiveness + _proficiences[_heroWeaponType].effectiveness + 1));
	}
	

	return dmg;
}

void Player::takeDamage(int dmg)
{
	_stats.hp -= dmg;



	if (_stats.hp < 0){
		_stats.hp = 0;
	}
	_gwi->refreshBars(_stats);
}

////////////////
//Proficiences//
////////////////

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
//////////////
//Experience//
//////////////

void Player::increaseExperience(int value)
{
	_stats.exp += value * (1.0f + (float)(_stats.intelligence / 100));
	while (_stats.exp >= _stats.max_exp){
		advanceToNextLevel();
	}
}

void Player::advanceToNextLevel()
{
	_stats.exp -= _stats.max_exp;
	_stats.max_exp = (int)(__BASE_EXPERIENCE__ * pow(__EXPIERIENCE_LVL_INCREASE__, _stats.level));
	_stats.level++;


	_stats.strenght += 1;
	_stats.endurance += 1;
	_stats.dexterity += 1;
	_stats.agility += 1;
	_stats.intelligence += 1;
	_stats.willpower += 1;

	addStatsByWeapon();

	refreshStatistics();

	_gwi->refreshBars(_stats);
}


/////////
//Stats//
/////////
void Player::refreshStatistics()
{
	_stats.hp = _stats.max_hp = _stats.endurance * 10;
	_stats.mp = _stats.max_mp = _stats.willpower * 10;
	_stats.stam = _stats.max_stam = _stats.strenght * 2 + _stats.endurance * 2;

	if (_heroWeaponType == WEAPON_TYPE::UNARMED){
		_stats.min_dmg = (int)(((float)_stats.strenght / 2 + (float)_stats.endurance / 2 + (float)_stats.dexterity / 4) * 0.8f);
		_stats.max_dmg = (int)(((float)_stats.strenght / 2 + (float)_stats.endurance / 2 + (float)_stats.dexterity / 4) * 1.2f);
	}
	else{

		Weapon_struct stats = _mainHand->getStatsStruct();

		_stats.min_dmg = stats.min_dmg;
		_stats.max_dmg = stats.max_dmg;

		int add_dmg;
		//calculate multipliers//
		add_dmg = (int)((float)(getPlayerAbilityValue(stats.primary_multiplier) * stats.primary_multiplier_value) / 100);
		if (stats.secondary_multiplier > -1){
			add_dmg += (int)((float)(getPlayerAbilityValue(stats.secondary_multiplier) * stats.secondary_multiplier_value) / 100);
		}

		_stats.min_dmg += add_dmg;
		_stats.max_dmg += add_dmg;
	}

}

void Player::addStatsByWeapon()
{
	//unarmed//
	if (_heroWeaponType == 4){
		_stats.strenght += 2;
		_stats.endurance += 2;
		_stats.agility += 2;
		return;
	}

	//armed//
	switch (_mainHand->getStatsStruct().size){
	case WEAPON_SIZE::SMALL:
		_stats.agility += 2;
		break;
	case WEAPON_SIZE::MEDIUM:
		_stats.agility += 1;
		_stats.strenght += 1;
		break;
	case WEAPON_SIZE::LARGE:
		_stats.strenght += 1;
		_stats.endurance += 1;
		break;
	}


	switch (_mainHand->getStatsStruct().type){
	case WEAPON_TYPE::AXE:
		_stats.strenght += 2;
		break;
	case WEAPON_TYPE::MACE:
		_stats.endurance += 1;
		_stats.strenght += 1;
		break;
	case WEAPON_TYPE::SWORD:
		_stats.agility += 1;
		_stats.strenght += 1;
		break;
	case WEAPON_TYPE::SPEAR:
		_stats.endurance += 1;
		_stats.strenght += 1;
		break;
	}

	switch (_mainHand->getStatsStruct().primary_multiplier){
	case HERO_STATS_NAMES::AGILITY:
		_stats.agility += 1;
		break;
	case HERO_STATS_NAMES::DEXTERITY:
		_stats.dexterity += 1;
		break;
	case HERO_STATS_NAMES::ENDURANCE:
		_stats.endurance += 1;
		break;
	case HERO_STATS_NAMES::INTELLIGENCE:
		_stats.intelligence += 1;
		break;
	case HERO_STATS_NAMES::STRENGTH:
		_stats.strenght += 1;
		break;
	case HERO_STATS_NAMES::WILLPOWER:
		_stats.willpower += 1;
		break;

	}

}