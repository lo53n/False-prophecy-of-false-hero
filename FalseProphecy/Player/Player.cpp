#include "Player.h"

Player::Player()
{

	_playerTexture.loadFromFile("data\\img\\hero.png");
	_playerShape.setTexture(&_playerTexture);
	_playerShape.setSize(sf::Vector2f(__PLAYER_HEIGHT__, __PLAYER_WIDTH__));
	_playerShape.setPosition(0.0f, 0.0f);
	//_playerShape.setFillColor(sf::Color::Red);

	/*_playerTexture.create((unsigned int)__PLAYER_WIDTH__, (unsigned int)__PLAYER_HEIGHT__);
	_playerTexture.clear();
	_playerTexture.draw(player);
	_playerTexture.display();*/

	//_playerSprite.setTexture(_playerTexture.getTexture());


	initializeStartValues();

}
void Player::initializeStartValues()
{
	_backpack.reserve(__BACKPACK_CAPACITY__);

	presetHeroStructure();
	presetProficiences();

	addStatistic(10, HERO_STATS_NAMES::STRENGTH);
	addStatistic(10, HERO_STATS_NAMES::ENDURANCE);
	addStatistic(10, HERO_STATS_NAMES::AGILITY);
	addStatistic(10, HERO_STATS_NAMES::DEXTERITY);
	addStatistic(10, HERO_STATS_NAMES::INTELLIGENCE);
	addStatistic(10, HERO_STATS_NAMES::WILLPOWER);


	setAsUnarmed();
	refreshStatistics();
	changeDeadStatus(false);

	_backpack.clear();
	_mainHand = nullptr;
	_offHand = nullptr;
	_torso = nullptr;
	_head = nullptr;
	_legs = nullptr;

}

Player::Player(std::vector<std::shared_ptr<Item>> backpack, std::vector<Ability_Proficiencies> proficiences, Hero_Profile stats,
	std::shared_ptr<Weapon> mainHand, std::shared_ptr<Armour> offHand, std::shared_ptr<Armour> head, std::shared_ptr<Armour> torso, std::shared_ptr<Armour> legs,
	float turnTillRegen, int currentMap)
	:
	_backpack(backpack),
	_proficiences(proficiences),
	_stats(stats),
	_mainHand(mainHand),
	_offHand(offHand),
	_head(head),
	_torso(torso),
	_legs(legs),
	_turnsTillNaturalRegen(turnTillRegen),
	_currentMap(currentMap)
{

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

void Player::restoreData()
{

	setPlayerPositionOnGrid(sf::Vector2i(_stats.posx, _stats.posy));



	if (_mainHand != nullptr){
		_heroWeaponHandle = _mainHand->getStatsStruct().weapon_handle;
		_heroWeaponType = _mainHand->getStatsStruct().type;
		_mainHand->restoreData();
	}
	if (_offHand != nullptr){
		_heroOffhandType = _offHand->getStatsStruct().type;
		_heroOffhandClass = _offHand->getStatsStruct().armour_class;
		_offHand->restoreData();
	}

	if (_head != nullptr){
		_heroHelmetType = _head->getStatsStruct().type;
		_heroHelmetClass = _head->getStatsStruct().armour_class;
		_head->restoreData();
	}

	if (_torso != nullptr){
		_heroTorsoType = _torso->getStatsStruct().type;
		_heroTorsoClass = _torso->getStatsStruct().armour_class;
		_torso->restoreData();
	}

	if (_legs != nullptr){
		_heroLegsType = _legs->getStatsStruct().type;
		_heroLegsClass = _legs->getStatsStruct().armour_class;
		_legs->restoreData();
	}



	for (auto item : _backpack){
		switch (item->getItemType()){
		case ITEM_TYPE::WEAPON:
			std::dynamic_pointer_cast <Weapon>(item)->restoreData();
			break;
		case ITEM_TYPE::ARMOUR:
			std::dynamic_pointer_cast <Armour>(item)->restoreData();
			break;
		case ITEM_TYPE::CONSUMABLE:
			std::dynamic_pointer_cast <Consumable>(item)->restoreData();
			break;
			
		}
	}
	

}



void Player::presetHeroStructure()
{
	_stats.level = 1;

	_stats.exp = 0;
	_stats.max_exp = __BASE_EXPERIENCE__;

	_stats.max_hp = _stats.hp = 0;
	_stats.max_mp = _stats.mp = 0;
	_stats.max_stam = _stats.stam = 0;

	_stats.strenght = 0;
	_stats.endurance = 0;
	_stats.dexterity = 0;
	_stats.agility = 0;
	_stats.intelligence = 0;
	_stats.willpower = 0;


	_stats.defence = 0;
	_stats.damage_reduction = 0.f;
	_stats.max_reduction = 0.90f;

	_stats.max_block = 0.85f;
	_stats.block = 0;
	_stats.block_chance = 0.f;

	_stats.max_dodge = 0.85f;
	_stats.dodge = 0;
	_stats.dodge_chance = 0.f;

	_stats.luck = 10;

	//0 - 1h, 1 - 2h
	_heroWeaponHandle = -1;
	//2 - shield, 3 - unarmed, 4 - sword, 5 - mace , 6 - spear, 7 - axe,
	_heroWeaponType = WEAPON_TYPE::UNARMED;

	int _heroOffHandType = -1;
	int _heroOffhandClass = ARMOUR_CLASS::EMPTYHAND;

	int _heroHelmetType = -1;
	int _heroHelmetClass = ARMOUR_CLASS::NAKED;

	int _heroTorsoType = -1;
	int _heroTorsoClass = ARMOUR_CLASS::NAKED;

	int _heroLegsType = -1;
	int _heroLegsClass = ARMOUR_CLASS::NAKED;

	_ratings.hero_rating = 0;
	_ratings.weapon_rating = 0;
	_ratings.offhand_rating = 0;
	_ratings.head_rating = 0;
	_ratings.torso_rating = 0;
	_ratings.legs_rating = 0;
	_ratings.overral_rating = 0;

}

void Player::presetProficiences()
{
	_proficiences.clear();
	for (int i = 0; i < 10; i++){
		Ability_Proficiencies ability;
		ability.id = i;
		ability.level = 1;
		ability.effectiveness = 0.f;

		if (i < 2)	ability.experience_needed = __BASE_PROFICIENCY_HANDLE_EXP__;
		else if (i > 7) ability.experience_needed = __BASE_PROFICIENCY_BODY_EXP__;
		else ability.experience_needed = __BASE_PROFICIENCY_WEAPON_EXP__;

		ability.experience = 0;

		//After changing this, remember to change it in StatusWindow.cpp in func setProgressBars() & refreshProficiences()
		if (i == 0) ability.name = "Onehanded";
		else if (i == 1) ability.name = "Twohanded";
		else if (i == 2) ability.name = "Shield";
		else if (i == 3) ability.name = "Unarmed";
		else if (i == 4) ability.name = "Sword";
		else if (i == 5) ability.name = "Mace";
		else if (i == 6) ability.name = "Spear";
		else if (i == 7) ability.name = "Axe";
		else if (i == 8) ability.name = "Defence";
		else if (i == 9) ability.name = "Body";

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
sf::Vector2f& Player::getPlayerSpritePosition()
{
	sf::Vector2f position = _playerShape.getPosition();
	return position;
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

Hero_Ratings Player::getPlayerRating()
{
	return _ratings;
}
int Player::getCurrentMap()
{
	return _currentMap;
}
///////////
//Setters//
///////////

void Player::setPlayerPositionOnMap(sf::Vector2f newPositionOnMap)
{
	_positionOnMap = newPositionOnMap;
	_positionOnGrid = (sf::Vector2i)(_positionOnMap / __PLAYER_HEIGHT__);
	_playerShape.setPosition(_positionOnMap);
	_stats.posx = _positionOnGrid.x;
	_stats.posy = _positionOnGrid.y;
}

void Player::setPlayerPositionOnGrid(sf::Vector2i newPositionOnGrid)
{
	_positionOnGrid = newPositionOnGrid;
	_positionOnMap = (sf::Vector2f)(_positionOnGrid * (int)__PLAYER_HEIGHT__);
	_playerShape.setPosition(_positionOnMap);
	_stats.posx = _positionOnGrid.x;
	_stats.posy = _positionOnGrid.y;
}


void Player::setGameWindowInterface(std::shared_ptr<GameWindowInterface> GWI)
{
	_gwi = GWI;
}
void Player::setCurrentMap(int mapID)
{
	_currentMap = mapID;

}
///////////////////
//Player movement//
///////////////////

void Player::movePlayer(int direction)
{
	sf::Vector2i movement;

	if (_positionOnMap != _playerShape.getPosition()){
		_playerShape.setPosition(_positionOnMap);
	}

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
	default:

		break;
	}

	_direction = direction;
	_positionOnGrid += movement;
	_positionOnMap += (sf::Vector2f)(movement * (int)__PLAYER_HEIGHT__);

	_isNeedToMoveSprite = true;

	_stats.posx = _positionOnGrid.x;
	_stats.posy = _positionOnGrid.y;
	//std::cout << "My position on grid: " << _positionOnGrid.x << " " << _positionOnGrid.y << std::endl;
	//std::cout << "My position on map: " << _positionOnMap.x << " " << _positionOnMap.y << std::endl;
}


bool Player::checkIfThereIsNeedToAnimate()
{
	return _isNeedToMoveSprite;
}

void Player::moveSprite(float change)
{
	sf::Vector2f changeToSprite;
	switch (_direction){
	case 0:
		changeToSprite = sf::Vector2f(0, -change);
		break;
	case 1:
		changeToSprite = sf::Vector2f(change, 0);
		break;
	case 2:
		changeToSprite = sf::Vector2f(0, change);
		break;
	case 3:
		changeToSprite = sf::Vector2f(-change, 0);
		break;

	}
	_playerShape.setPosition(_playerShape.getPosition()+changeToSprite);

	//std::cout << "Shape pos: " << _playerShape.getPosition().x << ":" << _playerShape.getPosition().y << " TargetPos: " << _positionOnMap.x << ":" << _positionOnMap.y << std::endl;
	if (_positionOnMap == _playerShape.getPosition()){
		_isNeedToMoveSprite = false;
	}

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
		if (itemNumber >= _backpack.size()) return nullptr;
		temp = _backpack.at(itemNumber);
		_backpack.erase(_backpack.begin() + itemNumber);
		return temp;
	}
	else{
		switch (itemNumber){
		case 0: 
			temp = _mainHand; 
			unequipItem(0, true); 
			break;
		case 1:
			temp = _offHand;
			unequipItem(1, true);
			break;
		case 2:
			temp = _head;
			unequipItem(2, true);
			break;
		case 3:
			temp = _torso;
			unequipItem(3, true);
			break;
		case 4:
			temp = _legs;
			unequipItem(4, true);
			break;
		}

		calculateChallengeRating();
		calculateChances();
		return temp;
	}
}

bool Player::checkRequirements(std::shared_ptr<Weapon> item)
{
	Weapon_struct stats = item->getStatsStruct();
	

	if (stats.str_req > _stats.strenght){ return false; }
	if (stats.end_req > _stats.endurance){ return false; }
	if (stats.dex_req > _stats.dexterity){ return false; }
	if (stats.agi_req > _stats.agility){ return false; }
	if (stats.int_req > _stats.intelligence){ return false; }
	if (stats.wil_req > _stats.willpower){ return false; }

	if (stats.weapon_handle == WEAPON_HANDLE::TWOHANDED && _offHand != nullptr) { return false; }

	return true;
}

bool Player::checkRequirements(std::shared_ptr<Armour> item)
{
	Armour_struct stats = item->getStatsStruct();

	if (stats.str_req > _stats.strenght){ return false; }
	if (stats.end_req > _stats.endurance){ return false; }
	if (stats.dex_req > _stats.dexterity){ return false; }
	if (stats.agi_req > _stats.agility){ return false; }
	if (stats.int_req > _stats.intelligence){ return false; }
	if (stats.wil_req > _stats.willpower){ return false; }

	if (stats.type == ARMOUR_TYPE::SHIELD && _heroWeaponHandle == WEAPON_HANDLE::TWOHANDED) { return false; }

	return true;
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
	_isUnarmed = false;
	_stats.min_dmg = stats.min_dmg;
	_stats.max_dmg = stats.max_dmg;
	_ratings.weapon_rating = stats.current_rating;

	int add_dmg;
	//calculate multipliers//
	add_dmg = (int)((float)(getPlayerAbilityValue(stats.primary_multiplier) * stats.primary_multiplier_value) / 100);
	if (stats.secondary_multiplier > -1){
		add_dmg += (int)((float)(getPlayerAbilityValue(stats.secondary_multiplier) * stats.secondary_multiplier_value) / 100);
	}

	_stats.min_dmg += add_dmg;
	_stats.max_dmg += add_dmg;
	//calculate rating//
	calculateChallengeRating();

	calculateChances();


}

void Player::equipItem(std::shared_ptr<Armour> item)
{
	Armour_struct stats;
	std::shared_ptr<Item> temp = nullptr;
	switch (item->getStatsStruct().type){
	case ARMOUR_TYPE::TORSO:
		if (_torso != nullptr) {
			temp = _torso;
			unequipItem(3, true);
		}

		_torso = item;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();
		_heroTorsoClass = stats.armour_class;
		_ratings.torso_rating = stats.current_rating;

		switch (_heroTorsoClass){

		case ARMOUR_CLASS::CLOTH:
			_stats.dodge += stats.dodge;
			break;

		case ARMOUR_CLASS::LEATHER:
			_stats.defence += stats.defence;
			_stats.dodge += stats.dodge;
			break;

		case ARMOUR_CLASS::METAL:
			_stats.defence += stats.defence;
			break;
		}
		break;


	case ARMOUR_TYPE::HELMET:
		if (_head != nullptr) {
			temp = _head;
			unequipItem(2, true);
		}
		_head = item;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();
		_heroHelmetClass = stats.armour_class;
		_ratings.head_rating = stats.current_rating;

		switch (_heroHelmetClass){

		case ARMOUR_CLASS::CLOTH:
			_stats.dodge += stats.dodge;
			break;

		case ARMOUR_CLASS::LEATHER:
			_stats.defence += stats.defence;
			_stats.dodge += stats.dodge;
			break;

		case ARMOUR_CLASS::METAL:
			_stats.defence += stats.defence;
			break;
		}
		break;


	case ARMOUR_TYPE::GREAVES:
		if (_legs != nullptr) {
			temp = _legs;
			unequipItem(4, true);
		}
		_legs = item;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();
		_heroLegsClass = stats.armour_class;
		_ratings.legs_rating = stats.current_rating;

		switch (_heroLegsClass){

		case ARMOUR_CLASS::CLOTH:
			_stats.dodge += stats.dodge;
			break;

		case ARMOUR_CLASS::LEATHER:
			_stats.defence += stats.defence;
			_stats.dodge += stats.dodge;
			break;

		case ARMOUR_CLASS::METAL:
			_stats.defence += stats.defence;
			break;
		}
		break;


	case ARMOUR_TYPE::SHIELD:
		if (_offHand != nullptr) {
			temp = _offHand;
			unequipItem(1, true);
		}
		_offHand = item;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();
		_heroOffhandClass = stats.armour_class;
		_ratings.offhand_rating = stats.current_rating;

		switch (_heroOffhandClass){

		case ARMOUR_CLASS::LIGHT:
			_stats.dodge += stats.dodge;
			_stats.block += stats.block;
			break;

		case ARMOUR_CLASS::AVERAGE:
			_stats.defence += stats.defence;
			_stats.block += stats.block;
			break;

		case ARMOUR_CLASS::HEAVY:
			_stats.defence += stats.defence;
			_stats.block += stats.block;
			break;
		}
		break;
	}
	//calculate rating
	calculateChallengeRating();
	calculateChances();

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

void Player::unequipItem(int slot, bool drop_item)
{
	Armour_struct stats;
	std::shared_ptr<Item> item = nullptr;

	switch (slot){

	case 0:
		item = _mainHand;
		_mainHand = nullptr;
		_ratings.weapon_rating = 0;
		//Set as unarmed//
		setAsUnarmed();
			break;

	case 1:
		item = _offHand;
		_offHand = nullptr;
		if (item == nullptr) return;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();
		_ratings.offhand_rating = 0;


		switch (_heroOffhandClass){
		case ARMOUR_CLASS::LIGHT:
			_stats.block -= stats.block;
			break;

		case ARMOUR_CLASS::AVERAGE:
			_stats.defence -= stats.defence;
			_stats.block -= stats.block;
			break;

		case ARMOUR_CLASS::HEAVY:
			_stats.defence -= stats.defence;
			_stats.block -= stats.block;
			break;
		}
		_heroOffhandClass = ARMOUR_CLASS::NAKED;
			break;

	case 2:
		item = _head;
		_head = nullptr;
		if (item == nullptr) return;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();
		_ratings.head_rating = 0;

		switch (_heroHelmetClass){
		case ARMOUR_CLASS::CLOTH:
			_stats.dodge -= stats.dodge;
			break;

		case ARMOUR_CLASS::LEATHER:
			_stats.defence -= stats.defence;
			_stats.dodge -= stats.dodge;
			break;

		case ARMOUR_CLASS::METAL:
			_stats.defence -= stats.defence;
			break;
		}

		_heroHelmetClass = ARMOUR_CLASS::NAKED;

		break;

	case 3:
		item = _torso;
		_torso = nullptr;
		if (item == nullptr) return;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();
		_ratings.torso_rating = 0;

		switch (_heroTorsoClass){
		case ARMOUR_CLASS::CLOTH:
			_stats.dodge -= stats.dodge;
			break;

		case ARMOUR_CLASS::LEATHER:
			_stats.defence -= stats.defence;
			_stats.dodge -= stats.dodge;
			break;

		case ARMOUR_CLASS::METAL:
			_stats.defence -= stats.defence;
			break;
		}

		_heroTorsoClass = ARMOUR_CLASS::NAKED;
		break;

	case 4:
		item = _legs;
		_legs = nullptr;
		if (item == nullptr) return;
		stats = std::dynamic_pointer_cast<Armour>(item)->getStatsStruct();
		_ratings.legs_rating = 0;

		switch (_heroLegsClass){
		case ARMOUR_CLASS::CLOTH:
			_stats.dodge -= stats.dodge;
			break;

		case ARMOUR_CLASS::LEATHER:
			_stats.defence -= stats.defence;
			_stats.dodge -= stats.dodge;
			break;

			_stats.defence -= stats.defence;
			break;
		}

		_heroLegsClass = ARMOUR_CLASS::NAKED;
		break;

	}
	if (!drop_item){
		if (item != nullptr) putItemInBackpack(item);
	}
	else{
		return;
	}

	calculateChallengeRating();
	calculateChances();

}

void Player::useItem(std::shared_ptr<Consumable> item)
{

	Consumable_struct stats = item->getStatsStruct();
	int regen;

	switch (stats.effect_type){
		//ONE STAT UP
	case CONSUMABLE_EFFECT::STR_UP:
		addStatistic(stats.effect_strength, HERO_STATS_NAMES::STRENGTH);
		break;
	case CONSUMABLE_EFFECT::END_UP:
		addStatistic(stats.effect_strength, HERO_STATS_NAMES::ENDURANCE);
		break;
	case CONSUMABLE_EFFECT::AGI_UP:
		addStatistic(stats.effect_strength, HERO_STATS_NAMES::AGILITY);
		break;
	case CONSUMABLE_EFFECT::DEX_UP:
		addStatistic(stats.effect_strength, HERO_STATS_NAMES::DEXTERITY);
		break;
	case CONSUMABLE_EFFECT::INT_UP:
		addStatistic(stats.effect_strength, HERO_STATS_NAMES::INTELLIGENCE);
		break;
	case CONSUMABLE_EFFECT::WIL_UP:
		addStatistic(stats.effect_strength, HERO_STATS_NAMES::WILLPOWER);
		break;
		//TWO STATS UP
	case CONSUMABLE_EFFECT::BODY_UP:
		addStatistic(stats.effect_strength, HERO_STATS_NAMES::STRENGTH);
		addStatistic(stats.effect_strength, HERO_STATS_NAMES::ENDURANCE);
		break;
	case CONSUMABLE_EFFECT::REFLEX_UP:
		addStatistic(stats.effect_strength, HERO_STATS_NAMES::AGILITY);
		addStatistic(stats.effect_strength, HERO_STATS_NAMES::DEXTERITY);
		break;
	case CONSUMABLE_EFFECT::MIND_UP:
		addStatistic(stats.effect_strength, HERO_STATS_NAMES::INTELLIGENCE);
		addStatistic(stats.effect_strength, HERO_STATS_NAMES::WILLPOWER);
		break;
		//EXP UP
	case CONSUMABLE_EFFECT::EXP_UP:
		increaseExperience(stats.effect_strength);
		break;
		//REGENERATIONS
	case CONSUMABLE_EFFECT::HP_REGEN:
		regen = (int)((float)_stats.max_hp * ((float)stats.effect_strength / 100));
		increaseHealth(regen);
		break;
	case CONSUMABLE_EFFECT::SP_REGEN:
		regen = (int)((float)_stats.max_stam * ((float)stats.effect_strength / 100));
		increaseHealth(regen);
		break;
	case CONSUMABLE_EFFECT::REGENERATE_TICK:
		regen = (int)((float)_stats.max_hp * ((float)stats.effect_strength / 100));
		increaseHealth(regen);
		regen = (int)((float)_stats.max_stam * ((float)stats.effect_strength / 100));
		increaseStamina(regen);
		break;
	}

	for (int i = 0, len = _backpack.size(); i < len; i++){
		if (std::dynamic_pointer_cast<Item>(item) == _backpack[i]){
			_backpack.erase(_backpack.begin() + i);
			break;
		}
	}

}

void Player::setAsUnarmed()
{
	_heroWeaponType = WEAPON_TYPE::UNARMED;
	_heroWeaponHandle = -1;
	_isUnarmed = true;
	refreshStatistics();
}

void Player::calculateChallengeRating()
{
	int temp_rating = 0;

	temp_rating += _stats.agility;
	temp_rating += _stats.dexterity;
	temp_rating += _stats.strenght;
	temp_rating += _stats.endurance;
	temp_rating += _stats.intelligence;
	temp_rating += _stats.willpower;

	/*
	int dmg = (int)(((float)_stats.min_dmg + (float)_stats.max_dmg) / 2) / 10;
	temp_rating += dmg + _stats.defence / 10;
	temp_rating += _stats.dodge / 10;
	*/

	_ratings.hero_rating = temp_rating;
	_ratings.overral_rating = _ratings.hero_rating;
	_ratings.overral_rating += _ratings.weapon_rating;
	_ratings.overral_rating += _ratings.offhand_rating;
	_ratings.overral_rating += _ratings.head_rating;
	_ratings.overral_rating += _ratings.torso_rating;
	_ratings.overral_rating += _ratings.legs_rating;


	//std::cout << "Challenge rating: " << _ratings.overral_rating << std::endl;

}


///////////
//Battle!//
///////////

int Player::calculateDamage()
{
	int dmg;

	if (hasStaminaToAttack()){
		dmg = rand() % (_stats.max_dmg - _stats.min_dmg) + _stats.min_dmg;
		//increase weapon proficienty after attack//
		if (_heroWeaponHandle != -1) increaseProficiency(_heroWeaponHandle, dmg);
		increaseProficiency(_heroWeaponType, dmg);

		//calculate damage for weapon type based on prificiences
		if (_heroWeaponHandle == -1){
			dmg = (int)((float)dmg * (_proficiences[HERO_ABILITIES_NUMBER::UNARMED_PROFICIENCY].effectiveness + 1));
		}
		else{
			dmg = (int)((float)dmg * (_proficiences[_heroWeaponHandle].effectiveness + _proficiences[_heroWeaponType].effectiveness + 1));
		}
	}

	//if no stamina, attack with penalties
	else{
		if (!_isUnarmed){
			Weapon_struct stats = _mainHand->getStatsStruct();

			dmg = rand() % (stats.max_dmg - stats.min_dmg) + stats.min_dmg;
		}
		else{

			int min_dmg = (int)(((float)_stats.strenght / 2 + (float)_stats.endurance / 2 + (float)_stats.dexterity / 4) * 0.8f);
			int max_dmg = (int)(((float)_stats.strenght / 2 + (float)_stats.endurance / 2 + (float)_stats.dexterity / 4) * 1.2f);

			dmg = rand() % (max_dmg - min_dmg) + min_dmg;
			//dmg /= 2;
		}

	}

	return dmg;
}

void Player::takeDamage(int dmg)
{
	std::uniform_int_distribution<int> percentage_dice(0, 99);
	if (percentage_dice(_generator) < _stats.dodge_chance * 100) {
		//TODO some reaction?
		//std::cout << "Dodged! Chance: " << _stats.dodge_chance << std::endl; 
		return;
	}

	if (_heroOffhandClass == ARMOUR_CLASS::NAKED){
		if (percentage_dice(_generator) < _stats.block_chance * 100) {
			//std::cout << "Blocked! Chance: " << _stats.block_chance << std::endl;
			increaseProficiency(DEFENCE_PROFICIENCY, dmg/2);
			//TODO some reaction?
			return;
		}
	}

	int dmg_taken = (int)((float)dmg * (1.f - _stats.damage_reduction));
	//std::cout << "DMG TAKEN: " << dmg_taken << std::endl;

	increaseProficiency(BODY_ENDURANCE, dmg_taken);
	increaseProficiency(DEFENCE_PROFICIENCY, dmg - dmg_taken);


	_stats.hp -= dmg_taken;



	if (_stats.hp < 0){
		_stats.hp = 0;
		changeDeadStatus(true);
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
		else if (id > 7) _proficiences[id].experience_needed = (int)(__BASE_PROFICIENCY_BODY_EXP__ * pow(__PROFICIENCY_LVL_INCREASE__, _proficiences[id].level));
		else _proficiences[id].experience_needed = (int)(__BASE_PROFICIENCY_WEAPON_EXP__ * pow(__PROFICIENCY_LVL_INCREASE__, _proficiences[id].level));

		calculateProficientyEffectivness(id);

		//std::cout << _proficiences[id].name << " lvl up to " << _proficiences[id].level << " eff: " << _proficiences[id].effectiveness << std::endl;
	}
}

void Player::calculateProficientyEffectivness(int id)
{
	_proficiences[id].effectiveness = 0;
	//handle
	if (id < 2){
		for (int i = 1; i < _proficiences[id].level; i++){
			_proficiences[id].effectiveness += (__PROFICIENCY_HANDLE_EFFICIENCY__ * (1 + (float)(_proficiences[id].level) / 100));
		}
	}
	//weapon
	if (id >= 2 && id < 8){
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
	if (id >= 8){
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
		}
	}
}
//////////////
//Experience//
//////////////

void Player::increaseExperience(int value)
{
	_stats.exp += (int)(value * (1.0f + (float)(_stats.intelligence / 100)));
	while (_stats.exp >= _stats.max_exp){
		advanceToNextLevel();
	}
}

void Player::advanceToNextLevel()
{
	_stats.exp -= _stats.max_exp;
	_stats.max_exp = (int)(__BASE_EXPERIENCE__ * pow(__EXPIERIENCE_LVL_INCREASE__, _stats.level));
	_stats.level++;


	addStatistic(1, HERO_STATS_NAMES::STRENGTH);
	addStatistic(1, HERO_STATS_NAMES::ENDURANCE);
	addStatistic(1, HERO_STATS_NAMES::AGILITY);
	addStatistic(1, HERO_STATS_NAMES::DEXTERITY);
	addStatistic(1, HERO_STATS_NAMES::INTELLIGENCE);
	addStatistic(1, HERO_STATS_NAMES::WILLPOWER);

	addStatsByWeapon();
	addStatsByOffhand();
	addStatsByArmour();


	refreshStatistics();

	_gwi->refreshBars(_stats);
}


/////////
//Stats//
/////////
void Player::addStatistic(int amount, int type)
{
	switch (type){
	case HERO_STATS_NAMES::STRENGTH:
		_stats.strenght += amount;

		_stats.stam += amount * 2;
		_stats.max_stam += amount * 2;

		break;
	case HERO_STATS_NAMES::ENDURANCE:
		_stats.endurance += amount;

		_stats.hp += amount * 10;
		_stats.max_hp += amount * 10;

		_stats.stam += amount;
		_stats.max_stam += amount;

		break;
	case HERO_STATS_NAMES::DEXTERITY:
		_stats.dexterity += amount;

		_stats.dodge += 5 * amount * _stats.level / 2;
		break;
	case HERO_STATS_NAMES::AGILITY:
		_stats.agility += amount;

		_stats.defence += 5 * amount * _stats.level / 2;
		_stats.block += 5 * amount * _stats.level / 2;
		break;
	case HERO_STATS_NAMES::INTELLIGENCE:
		_stats.intelligence += amount;
		break;
	case HERO_STATS_NAMES::WILLPOWER:
		_stats.willpower += amount;

		_stats.mp += amount * 10;
		_stats.max_mp += amount * 10;

		break;
	case HERO_STATS_NAMES::LUCK:
		_stats.luck += amount;
		break;
	}
}

void Player::giveStatistic(int amount, int type)
{
	addStatistic(amount, type);
	calculateChances();
}

void Player::refreshStatistics()
{

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
	calculateChallengeRating();
	calculateChances();

}

void Player::addStatsByWeapon()
{
	//unarmed//
	if (_mainHand == nullptr){
		addStatistic(1, HERO_STATS_NAMES::STRENGTH);
		addStatistic(1, HERO_STATS_NAMES::ENDURANCE);
		addStatistic(1, HERO_STATS_NAMES::AGILITY);
		addStatistic(1, HERO_STATS_NAMES::DEXTERITY);
		return;
	}

	//armed//
	switch (_mainHand->getStatsStruct().size){
	case WEAPON_SIZE::SMALL:
		addStatistic(1, HERO_STATS_NAMES::AGILITY);
		break;
	case WEAPON_SIZE::MEDIUM:
		addStatistic(1, HERO_STATS_NAMES::STRENGTH);
		break;
	case WEAPON_SIZE::LARGE:
		addStatistic(1, HERO_STATS_NAMES::ENDURANCE);
		break;
	}


	switch (_mainHand->getStatsStruct().type){
	case WEAPON_TYPE::AXE:
		addStatistic(1, HERO_STATS_NAMES::STRENGTH);
		break;
	case WEAPON_TYPE::MACE:
		addStatistic(1, HERO_STATS_NAMES::ENDURANCE);
		break;
	case WEAPON_TYPE::SWORD:
		addStatistic(1, HERO_STATS_NAMES::AGILITY);
		break;
	case WEAPON_TYPE::SPEAR:
		addStatistic(1, HERO_STATS_NAMES::DEXTERITY);
		break;
	}

	switch (_mainHand->getStatsStruct().primary_multiplier){
	case HERO_STATS_NAMES::AGILITY:
		addStatistic(1, HERO_STATS_NAMES::AGILITY);
		break;
	case HERO_STATS_NAMES::DEXTERITY:
		addStatistic(1, HERO_STATS_NAMES::DEXTERITY);
		break;
	case HERO_STATS_NAMES::ENDURANCE:
		addStatistic(1, HERO_STATS_NAMES::ENDURANCE);
		break;
	case HERO_STATS_NAMES::INTELLIGENCE:
		addStatistic(1, HERO_STATS_NAMES::INTELLIGENCE);
		break;
	case HERO_STATS_NAMES::STRENGTH:
		addStatistic(1, HERO_STATS_NAMES::STRENGTH);
		break;
	case HERO_STATS_NAMES::WILLPOWER:
		addStatistic(1, HERO_STATS_NAMES::WILLPOWER);
		break;

	}

}

void Player::addStatsByOffhand()
{
	switch (_heroOffhandClass){
	case ARMOUR_CLASS::NAKED:
		switch (_heroWeaponHandle){
		case WEAPON_HANDLE::ONEHANDED:
			addStatistic(1, HERO_STATS_NAMES::AGILITY);
			addStatistic(1, HERO_STATS_NAMES::DEXTERITY);
			break;
		default: break;
		}
		break;
	case ARMOUR_CLASS::LIGHT:
		addStatistic(1, HERO_STATS_NAMES::AGILITY);
		break;
	case ARMOUR_CLASS::AVERAGE:
		addStatistic(1, HERO_STATS_NAMES::STRENGTH);
		break;
	case ARMOUR_CLASS::HEAVY:
		addStatistic(1, HERO_STATS_NAMES::ENDURANCE);
		break;
	}
}

void Player::addStatsByArmour()
{
	switch (_heroHelmetClass){
	case ARMOUR_CLASS::NAKED:
		addStatistic(1, HERO_STATS_NAMES::DEXTERITY);
		break;
	case ARMOUR_CLASS::CLOTH:
		addStatistic(1, HERO_STATS_NAMES::AGILITY);
		break;
	case ARMOUR_CLASS::LEATHER:
		addStatistic(1, HERO_STATS_NAMES::STRENGTH);
		break;
	case ARMOUR_CLASS::METAL:
		addStatistic(1, HERO_STATS_NAMES::ENDURANCE);
		break;
	}
	switch (_heroTorsoClass){
	case ARMOUR_CLASS::NAKED:
		addStatistic(1, HERO_STATS_NAMES::DEXTERITY);
		break;
	case ARMOUR_CLASS::CLOTH:
		addStatistic(1, HERO_STATS_NAMES::AGILITY);
		break;
	case ARMOUR_CLASS::LEATHER:
		addStatistic(1, HERO_STATS_NAMES::STRENGTH);
		break;
	case ARMOUR_CLASS::METAL:
		addStatistic(1, HERO_STATS_NAMES::ENDURANCE);
		break;

	}
	switch (_heroLegsClass){
	case ARMOUR_CLASS::NAKED:
		addStatistic(1, HERO_STATS_NAMES::DEXTERITY);
		break;
	case ARMOUR_CLASS::CLOTH:
		addStatistic(1, HERO_STATS_NAMES::AGILITY);
		break;
	case ARMOUR_CLASS::LEATHER:
		addStatistic(1, HERO_STATS_NAMES::STRENGTH);
		break;
	case ARMOUR_CLASS::METAL:
		addStatistic(1, HERO_STATS_NAMES::ENDURANCE);
		break;

	}

}

void Player::calculateChances()
{
	_stats.damage_reduction = (((float)_stats.defence * (1.f + _proficiences.at(DEFENCE_PROFICIENCY).effectiveness)) * pow(0.85f, _stats.level)) / 100;
	//std::cout << "dmg_Red: " << _stats.damage_reduction << "math " << (float)_stats.defence * pow(0.80f, _stats.level) / 100 << std::endl;
	if (_stats.damage_reduction >= _stats.max_reduction){
		_stats.damage_reduction = _stats.max_reduction;
	} 


	_stats.dodge_chance = (((float)_stats.dodge * (1.f + _proficiences.at(DEFENCE_PROFICIENCY).effectiveness)) * pow(0.85f, _stats.level)) / 100;
	//std::cout << "dodge: " << _stats.dodge_chance << "math " << (float)_stats.dodge * pow(0.80f, _stats.level) / 100 << std::endl;
	if (_stats.dodge_chance >= _stats.max_dodge){
		_stats.dodge_chance = _stats.max_dodge;
	}


	if (_offHand != nullptr){
		_stats.block_chance = (((float)_stats.block * (1.f + _proficiences.at(DEFENCE_PROFICIENCY).effectiveness)) * pow(0.85f, _stats.level)) / 100;
		//std::cout << "dodge: " << _stats.block_chance << "math " << (float)_stats.block * pow(0.80f, _stats.level) / 100 << std::endl;
		if (_stats.block_chance >= _stats.max_block){
			_stats.block_chance = _stats.max_block;
		}
	}
}
/////////
//Other//
/////////

void Player::takeTurn()
{
	_turnsTillNaturalRegen++;
	if (_turnsTillNaturalRegen >= __TURNS_FOR_REGEN__){
		regenHealth(false);
		regenStamina(false);
		_turnsTillNaturalRegen -= __TURNS_FOR_REGEN__;
	}
}

void Player::regenHealth(bool forced)
{
	if (!forced){
		_stats.hp += 15 + _stats.willpower / 5;
	}
	else{
		_stats.hp += 5 + _stats.willpower / 10;
	}
	if (_stats.hp > _stats.max_hp) _stats.hp = _stats.max_hp;

}
void Player::regenStamina(bool forced)
{
	if (!forced){
		_stats.stam += 15 + _stats.willpower / 5;
	}
	else{
		_stats.stam += 6 + _stats.willpower / 10;
	}
	if (_stats.stam > _stats.max_stam) _stats.stam = _stats.max_stam;
}

bool Player::hasStaminaToAttack()
{

	int req_stam = 0;
	if (_isUnarmed){
		req_stam = 5;
	}
	else{
		int handle = _mainHand->getStatsStruct().weapon_handle;
		switch (_mainHand->getStatsStruct().size){
		case WEAPON_SIZE::SMALL:
			if (handle == WEAPON_HANDLE::ONEHANDED){
				req_stam = 3;
			}
			else if (handle == WEAPON_HANDLE::TWOHANDED){
				req_stam = 2;
			}
			break;
		case WEAPON_SIZE::MEDIUM:
			if (handle == WEAPON_HANDLE::ONEHANDED){
				req_stam = 5;
			}
			else if (handle == WEAPON_HANDLE::TWOHANDED){
				req_stam = 4;
			}
			break;
		case WEAPON_SIZE::LARGE:
			if (handle == WEAPON_HANDLE::ONEHANDED){
				req_stam = 7;
			}
			else if (handle == WEAPON_HANDLE::TWOHANDED){
				req_stam = 5;
			}
			break;
		}
	}

	if (req_stam <= _stats.stam){
		drainStaminaAttack(req_stam);
		return true;
	}
	else{
		drainStaminaAttack(_stats.stam);
		return false;
	}

}
void Player::drainStaminaAttack(int amount)
{
	_stats.stam -= amount;
}

void Player::increaseHealth(int amount)
{
	if (amount >= 0){
		_stats.hp += amount;
		if (_stats.hp > _stats.max_hp) _stats.hp = _stats.max_hp;
	}
}
void Player::increaseStamina(int amount)
{
	if (amount >= 0){
		_stats.stam += amount;
		if (_stats.stam > _stats.max_stam) _stats.stam = _stats.max_stam;
	}

}


void Player::changeDeadStatus(bool status)
{
	_isDead = status;
}

bool Player::isPlayerDead()
{
	return _isDead;
}
