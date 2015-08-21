#ifndef PLAYER_PLAYER
#define PLAYER_PLAYER

#include <vector>
#include <iostream>
#include <memory>


#include <SFML\Graphics.hpp>

#include "../Items/Item.h"
#include "../StructsEnums.h"

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


	//get player's backpack
	std::vector<std::shared_ptr<Item>>& getPlayerBackpack();

	///////////
	//Setters//
	///////////

	//set player position on map (px)
	void setPlayerPositionOnMap(sf::Vector2f newPositionOnMap);		
	//set player position on map (x,y)
	void setPlayerPositionOnGrid(sf::Vector2i newPositionOnGrid);

	/////////////
	//Inventory//
	/////////////

	void putItemInBackpack(std::shared_ptr<Item> item);


	///////////
	//Battle!//
	///////////

	int calculateDamage();


	////////////////
	//Proficiences//
	////////////////
	void presetProficiences();
	void increaseProficiency(int id, int amount);
	void calculateProficientyEffectivness(int id);

private:
	sf::Texture _playerTexture;
	sf::RectangleShape _playerShape;
	
	sf::Vector2f _positionOnMap;	//Position in px
	sf::Vector2i _positionOnGrid;	//Position on map

	Hero_Profile _stats;
	std::vector<Ability_Proficiencies> _proficiences;
	

	/////////////
	//Equipment//
	/////////////

	bool isUnarmed = false;

	std::vector<std::shared_ptr<Item>> _backpack;
	int _heroWeaponType = 0;
	int _heroWeaponHandle = 0;



	/////////////////
	//Magic numbers//
	/////////////////

	const float __PLAYER_HEIGHT__ = 32.0f;
	const float __PLAYER_WIDTH__ = 32.0f;

	const int __BASE_PROFICIENCY_WEAPON_EXP__ = 100;
	const int __BASE_PROFICIENCY_HANDLE_EXP__ = 175;
	const int __BASE_PROFICIENCY_BODY_EXP__ = 130;

	const float __PROFICIENCY_LVL_INCREASE__ = 1.15f;

	const float __PROFICIENCY_HANDLE_EFFICIENCY__ = 0.05f;
	const float __PROFICIENCY_WEAPON_EFFICIENCY__ = 0.05f;
	const float __PROFICIENCY_UNARMED_EFFICIENCY__ = 0.07f;

	const float __PROFICIENCY_PAIN_EFFICIENCY__ = 0.01f;
	const float __PROFICIENCY_BODY_EFFICIENCY__ = 0.025f;
	const float __PROFICIENCY_DEFENCE_EFFICIENCY__ = 0.05f;
	const float __PROFICIENCY_DODGE_EFFICIENCY__ = 0.01f;



private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif //!PLAYER_PLAYER