#ifndef PLAYER_PLAYER
#define PLAYER_PLAYER

#include <vector>
#include <iostream>
#include <memory>


#include <SFML\Graphics.hpp>

#include "../Items/Item.h"

#include "../Items/Armours/Armour.h"
#include "../Items/Weapons/Weapon.h"

#include "../Interface/GameWindowInterface.h"




class Player : public sf::Drawable{

public:


	Player();
	~Player();

	enum MOVEMENT{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	////////////
	//Movement//
	////////////

	//Move player to specific tile.
	//@param int direction - 0 for north, 1 for east, 2 for south, 3 for west.
	void movePlayer(int direction);


	///////////
	//Getters//
	///////////

	//get player position on map (px)
	sf::Vector2f& getPlayerPositionOnMap();		
	//get player position on map (x,y)
	sf::Vector2i& getPlayerPositionOnGrid();
	//Get player stats
	Hero_Profile& getPlayerStats();
	//Get player abilities
	std::vector<Ability_Proficiencies> getPlayerProficiences();
	//Get player weapon
	std::shared_ptr<Weapon> getPlayerWeapon();
	//Get player piece of gear
	std::shared_ptr<Armour> getPlayerArmour(int type);
	//Get player specific ability
	int getPlayerAbilityValue(int type);
	//Get player weapon handle
	int getPlayerWeaponHandle();
	//Get player weapon type
	int getPlayerWeaponType();
	//get player's backpack
	std::vector<std::shared_ptr<Item>>& getPlayerBackpack();
	//get player's challenge rating
	Hero_Ratings getPlayerRating();

	///////////
	//Setters//
	///////////

	//set player position on map (px)
	void setPlayerPositionOnMap(sf::Vector2f newPositionOnMap);		
	//set player position on map (x,y)
	void setPlayerPositionOnGrid(sf::Vector2i newPositionOnGrid);
	//set game interface to be responsive
	void setGameWindowInterface(std::shared_ptr<GameWindowInterface> GWI);

	/////////////
	//Inventory//
	/////////////

	void putItemInBackpack(std::shared_ptr<Item> item);

	void equipItem(std::shared_ptr<Weapon> item);
	void equipItem(std::shared_ptr<Armour> item);

	void unequipItem(int slot);

	std::shared_ptr<Item> dropSelectedItem(int itemNumber, bool inBag);

	void setAsUnarmed();

	void calculateChallengeRating();

	///////////
	//Battle!//
	///////////

	int calculateDamage();

	void takeDamage(int);

	////////////////
	//Proficiences//
	////////////////
	void presetProficiences();
	void increaseProficiency(int id, int amount);
	void calculateProficientyEffectivness(int id);

	//////////////
	//Experience//
	//////////////
	void increaseExperience(int amount);
	void advanceToNextLevel();


	/////////////////////
	//Preset structures//
	/////////////////////
	void presetHeroStructure();


	/////////
	//Stats//
	/////////
	void refreshStatistics();
	void addStatsByWeapon();
	void addStatsByOffhand();
	void addStatsByArmour();

private:
	sf::Texture _playerTexture;
	sf::RectangleShape _playerShape;
	
	sf::Vector2f _positionOnMap;	//Position in px
	sf::Vector2i _positionOnGrid;	//Position on map

	Hero_Profile _stats;
	std::vector<Ability_Proficiencies> _proficiences;
	
	std::shared_ptr<GameWindowInterface> _gwi;

	Hero_Ratings _ratings;

	/////////////
	//Equipment//
	/////////////

	bool isUnarmed = false;


	std::vector<std::shared_ptr<Item>> _backpack;
	int _heroWeaponType = 0;
	int _heroWeaponHandle = 0;
	
	int _heroOffhandType = 0;
	int _heroOffhandClass = 0;

	int _heroHelmetType = 0;
	int _heroHelmetClass = 0;
	int _heroTorsoType = 0;
	int _heroTorsoClass = 0;
	int _heroLegsType = 0;
	int _heroLegsClass = 0;

	std::shared_ptr<Weapon> _mainHand;
	std::shared_ptr<Armour> _offHand;

	std::shared_ptr<Armour> _head;
	std::shared_ptr<Armour> _torso;
	std::shared_ptr<Armour> _legs;



	/////////////////
	//Magic numbers//
	/////////////////

	//If changed, change in Game.h//
	const int __BACKPACK_CAPACITY__ = 50;

	const float __PLAYER_HEIGHT__ = 32.0f;
	const float __PLAYER_WIDTH__ = 32.0f;

	const int __BASE_PROFICIENCY_WEAPON_EXP__ = 125;
	const int __BASE_PROFICIENCY_HANDLE_EXP__ = 175;
	const int __BASE_PROFICIENCY_BODY_EXP__ = 130;

	const float __PROFICIENCY_LVL_INCREASE__ = 1.25f;

	const float __PROFICIENCY_HANDLE_EFFICIENCY__ = 0.02f;
	const float __PROFICIENCY_WEAPON_EFFICIENCY__ = 0.02f;
	const float __PROFICIENCY_UNARMED_EFFICIENCY__ = 0.02f;

	const float __PROFICIENCY_PAIN_EFFICIENCY__ = 0.01f;
	const float __PROFICIENCY_BODY_EFFICIENCY__ = 0.025f;
	const float __PROFICIENCY_DEFENCE_EFFICIENCY__ = 0.05f;
	const float __PROFICIENCY_DODGE_EFFICIENCY__ = 0.01f;

	const int __BASE_EXPERIENCE__ = 100;
	const float __EXPIERIENCE_LVL_INCREASE__ = 1.20f;


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif //!PLAYER_PLAYER