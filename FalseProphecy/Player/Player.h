#ifndef PLAYER_PLAYER
#define PLAYER_PLAYER

#include <vector>
#include <iostream>
#include <memory>


#include <SFML\Graphics.hpp>

#include "../Items/Item.h"

class Player : public sf::Drawable{

public:
	std::string name;

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

private:
	sf::Texture _playerTexture;
	sf::RectangleShape _playerShape;
	
	sf::Vector2f _positionOnMap;	//Position in px
	sf::Vector2i _positionOnGrid;	//Position on map


	/////////////
	//Equipment//
	/////////////

	std::vector<std::shared_ptr<Item>> _backpack;



	/////////////////
	//Magic numbers//
	/////////////////

	const float __PLAYER_HEIGHT__ = 32.0f;
	const float __PLAYER_WIDTH__ = 32.0f;



private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif //!PLAYER_PLAYER